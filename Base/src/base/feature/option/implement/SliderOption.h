#pragma once
#include "../Option.h"

constexpr auto NULLSTR = "";

class SliderOption : Option<double>
{
public:
	double maximum;
	double minimum;
	double increment;
	const char* suffix;

	SliderOption(const char* father, const char* name, const char* description, double value, double _maximum_, double _minimum_, double _increment_) : Option(father, name, description, value)
	{
		this->maximum = _maximum_;
		this->minimum = _minimum_;
		this->increment = _increment_;
		this->suffix = NULLSTR;
	}

	SliderOption(const char* father, const char* name, const char* description, double value, double _maximum_, double _minimum_, double _increment_, std::function<bool()> booleanSupplier) : Option(father, name, description, value, booleanSupplier)
	{
		this->maximum = _maximum_;
		this->minimum = _minimum_;
		this->increment = _increment_;
		this->suffix = NULLSTR;
	}

	SliderOption(const char* father, const char* name, const char* description, double value, double _maximum_, double _minimum_, double _increment_, const char* suffix) : Option(father, name, description, value)
	{
		this->maximum = _maximum_;
		this->minimum = _minimum_;
		this->increment = _increment_;
		this->suffix = suffix;
	}

	SliderOption(const char* father, const char* name, const char* description, double value, double _maximum_, double _minimum_, double _increment_, const char* suffix, std::function<bool()> booleanSupplier) : Option(father, name, description, value, booleanSupplier)
	{
		this->maximum = _maximum_;
		this->minimum = _minimum_;
		this->increment = _increment_;
		this->suffix = suffix;
	}
};