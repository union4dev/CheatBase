#pragma once
#include <functional>

template<typename T>
class Option
{
public:
	const char* father;
	const char* name; // option name
	const char* description; // option description
	T value; // option value
	std::function<bool()> booleanSupplier; // visible condition

	Option(const char* father, const char* name, const char* description, T value) noexcept
	{
		this->father = father;
		this->name = name;
		this->description = description;
		this->value = value;
		this->booleanSupplier = []() -> bool { return true; };
	}

	Option(const char* father, const char* name, const char* description, T value, std::function<bool()> booleanSupplier) noexcept
	{
		this->father = father;
		this->name = name;
		this->description = description;
		this->value = value;
		this->booleanSupplier = booleanSupplier;
	}

	bool isVisible() noexcept
	{
		return booleanSupplier();
	}
};