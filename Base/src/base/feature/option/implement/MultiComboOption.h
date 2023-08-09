#pragma once
#include <vector>
#include "../Option.h"
#include "BoolOption.h"

class MultiComboOption : Option<std::vector<BoolOption>>
{
public:
	std::vector<BoolOption> booleans;

	MultiComboOption(const char* father, const char* name, const char* description, std::vector<BoolOption> _booleans_) : Option(father, name, description, _booleans_)
	{
		this->booleans = _booleans_;
	}

	MultiComboOption(const char* father, const char* name, const char* description, std::vector<BoolOption> _booleans_, std::function<bool()> booleanSupplier) : Option(father, name, description, _booleans_, booleanSupplier)
	{
		this->booleans = _booleans_;
	}
};