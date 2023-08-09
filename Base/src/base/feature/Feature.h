#pragma once

enum Category
{
	RAGEBOT,
	ANTIAIM,
	LEGITBOT,
	VISUALS,
	MISC,
	INVENTORY,
};

class Feature
{
public:
	const char* name; // feature name
	const char* description; // feature description
	Category category; // category of this feature

	Feature(const char* name, const char* description, Category category) noexcept
	{
		this->name = name;
		this->description = description;
		this->category = category;
	}
};