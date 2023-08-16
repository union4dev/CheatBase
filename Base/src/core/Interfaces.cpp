#include "Interfaces.h"

#include "../sdk/InterfaceReg.h"
#include "../utils/AddressUtils.h"

#include <Windows.h>
#include <string_view>
#include <stdexcept>
#include <format>

template<typename T>
static T* GetInterface(const char* module, const std::string_view name)
{
	const auto handle = GetModuleHandle(module);

	if (!handle)
	{
		throw std::runtime_error(std::format("Failed to get \"{}\" module handle.", module));
	}

	const auto createInterface = reinterpret_cast<uintptr_t>(GetProcAddress(handle, "CreateInterface"));

	if (!createInterface)
	{
		throw std::runtime_error(std::format("Failed to get CreateInterface in \"{}\".", module));
	}

	const auto relative = createInterface + 5;
	const auto address = AddressUtils::RelativeToAbsolute(relative);
	const auto interfaces = **reinterpret_cast<InterfaceReg***>(address + 6);

	if (!interfaces)
	{
		throw std::runtime_error(std::format("Failed to get s_pInterfaceRegs in \"{}\".", module));
	}

	for (auto item = interfaces; item; item = item->m_pNext)
	{
		if ((!std::string_view(item->m_pName).compare(0U, name.length(), name) &&
			std::atoi(item->m_pName + name.length()) > 0) ||
			!name.compare(item->m_pName))
		{
			const auto pointer = item->m_CreateFn();

			if (!pointer)
			{
				throw std::runtime_error(std::format("Failed to create \"{}\"", item->m_pName));
			}

			return static_cast<T*>(pointer);
		}
	}

	throw std::runtime_error(std::format("Failed to find {} in {}", name, module));
}

void Interfaces::Initialize() noexcept
{
	client = GetInterface<IBaseClientDLL>("client", "VClient");
}
