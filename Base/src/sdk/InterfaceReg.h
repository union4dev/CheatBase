#pragma once

using InstantiateInterfaceFn = void* (__cdecl*) ();

struct InterfaceReg
{
	InstantiateInterfaceFn m_CreateFn;
	const char* m_pName;
	InterfaceReg* m_pNext;
};