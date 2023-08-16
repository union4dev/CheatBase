#pragma once
#include "../sdk/Sdk.h"
#include <cstdint>

class Memory
{
public:
	Memory()
	{
		this->Initialize();
	}

	std::uintptr_t present;
	std::uintptr_t reset;

	bool* disablePostProcessing;

	std::add_pointer_t<void __fastcall(const char*, const char*)> setClanTag;

	CGlobalVarsBase* globalVars = nullptr;
private:
	void Initialize();

	uint8_t* Scan(const char* module, const char* pattern);
};

inline std::unique_ptr<const Memory> memory;