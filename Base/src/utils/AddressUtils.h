#pragma once
#include <cstdint>

namespace AddressUtils
{
	template <typename T = uintptr_t>
	constexpr T RelativeToAbsolute(const T address) noexcept
	{
		return static_cast<T>(address + 4 + *reinterpret_cast<uint32_t*>(address));
	}

	constexpr void* Get(void* thisptr, const size_t index) noexcept
	{
		return (*static_cast<void***>(thisptr))[index];
	}

	template <typename T, typename ... U>
	constexpr T Call(void* thisptr, const size_t index, U ... params) noexcept
	{
		using Fn = T(__thiscall*)(void*, decltype(params)...);
		return (*static_cast<Fn**>(thisptr))[index](thisptr, params...);
	}
};