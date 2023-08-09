#pragma once
#include "../Option.h"

class TextOption : Option<const char*>
{
public:
	TextOption(const char* father, const char* name, const char* description, const char* value) : Option(father, name, description, value) {}

	TextOption(const char* father, const char* name, const char* description, const char* value, std::function<bool()> booleanSupplier) : Option(father, name, description, value, booleanSupplier) {}
};