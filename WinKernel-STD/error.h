#pragma once
#include "string.h"
struct Error {
	Error() = delete;
	//virtual ~Error(){};
	~Error() = delete;
	virtual kstd::string what() = 0;
};
struct OutOfMemory : Error
{
	~OutOfMemory() = delete;
	static kstd::string what() { return "Out Of Memory During Allocation"; }
};

struct DanglingPointerDereference : Error
{
	~DanglingPointerDereference() = delete;
	static kstd::string what() { return "Tried to derefrence dangling pointer"; }
};

struct OutOfBounds : Error
{
	~OutOfBounds() = delete;
	static kstd::string what() { return "Tried to derefrence dangling pointer"; }
};