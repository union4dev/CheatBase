#pragma once
#include "../Option.h"

class BoolOption : Option<bool>
{
public:
	BoolOption(const char* father, const char* name, const char* description, bool value) : Option(father, name, description, value) {}

	BoolOption(const char* father, const char* name, const char* description, bool value, std::function<bool()> booleanSupplier) : Option(father, name, description, value, booleanSupplier) {}
};