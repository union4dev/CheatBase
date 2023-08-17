#pragma once
#include <vector>
#include "../Option.h"

class ComboOption : Option<const char*>
{
public:
	std::vector<const char*> modes;

	ComboOption(const char* father, const char* name, const char* description, std::vector<const char*> modes) : Option(father, name, description, modes[0])
	{
		this->modes = modes;
	}

	ComboOption(const char* father, const char* name, const char* description, std::function<bool()> booleanSupplier, std::vector<const char*> modes) : Option(father, name, description, modes[0], booleanSupplier)
	{
		this->modes = modes;
	}

	bool isMode(const char* mode) noexcept
	{
		return this->value == mode;
	}
};