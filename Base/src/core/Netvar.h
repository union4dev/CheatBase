#pragma once
#include "../sdk/data/Fnv.h"
#include "Common.h"

#include <map>
#include <memory>
#include <type_traits>

#define NETVAR(name, var, ...) \
std::add_lvalue_reference_t<__VA_ARGS__> name() \
{ \
	static const auto offset = netvar->GetOffset(Fnv::HashConst(var)); \
	return *reinterpret_cast<std::add_pointer_t<__VA_ARGS__>>(std::uintptr_t(this) + offset); \
}

#define NETPROP(name, var) \
static RecvProp* name() \
{ \
	static auto prop = netvar->GetPropN(Fnv::HashConst(var)); \
	return prop; \
}

class Netvar
{
public:
	Netvar()
	{
		this->Initialize();
	}

	std::uint32_t GetOffset(const std::uint32_t hash);
	RecvProp* GetPropN(const std::uint32_t hash);

	struct NetvarData
	{
		RecvProp* prop = { };
		std::uint32_t  offset = { };
	};
private:
	void Initialize() noexcept;

	void Dump(const char* baseClass, RecvTable* table, const std::uint32_t offset);

	std::map<uint32_t, NetvarData> data = { };
};

inline std::unique_ptr<Netvar> netvar;