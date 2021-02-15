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
	static kstd::string what() { return "Out Of Memory During Allocation"; }
};

struct DanglingPointerDereference : Error
{
	static kstd::string what() { return "Tried to derefrence dangling pointer"; }
};

struct OutOfBounds : Error
{
	static kstd::string what() { return "Tried to derefrence dangling pointer"; }
};