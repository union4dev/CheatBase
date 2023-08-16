#pragma once
/*
This file aims to fast initial the header of sdk's classes
*/

struct bf_read;
struct bf_write;

struct RecvTable;
struct RecvProxyData;
struct RecvProp;

class ClientNetworkable;
class HandleEntity;
class ClientEntity;
class ClientRenderable;
class Collideable;
class ClientThinkable;
class ClientUnknown;
class ClientAlphaProperty;

class BaseEntity;

using CreateInterfaceFn = void* (__cdecl*)(const char*, int*);
using CreateClientClassFn = ClientNetworkable * (__cdecl*)(int, int);
using CreateEventFn = ClientNetworkable * (__cdecl*)();

using RecvVarProxyFn = void(__cdecl*)(const RecvProxyData*, void*, void*);
using ArrayLengthProxyFn = void(__cdecl*)(void*, int, int);
using DataTableProxyFn = void(__cdecl*)(const RecvProp*, void**, void*, int);

struct Rect
{
	int x, y, width, height;
};