#pragma once
#include "../sdk/Sdk.h"

class Interfaces
{
public:
	Interfaces()
	{
		this->Initialize();
	}

	IBaseClientDLL* client = nullptr;
private:
	void Initialize() noexcept;
};

inline std::unique_ptr<const Interfaces> interfaces;