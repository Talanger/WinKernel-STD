#pragma once
#include "cstddef.h"
#include <ntddk.h>
#include "error.h"
namespace kstd
{
	using TAG = ULONG ;

	template<class T, POOL_TYPE poolType, TAG tag>
	struct K_TYPE
	{
		using value_type = T;
		static const POOL_TYPE m_poolType = poolType;
		static const TAG m_tag = tag;
	};

	template <class T >
	concept K_VALID = requires(T t) {
		typename T::value_type; // required nested member name
		typename T::m_poolType; // required nested member name
		typename T::m_tag; // required nested member name
	};
	template<K_VALID T> struct Allocator;

	template<K_VALID T>
	struct Allocator
	{
		static T* Allocate(size_t _amount)
		{
			try {
				auto arr = (ExAllocatePool(T::m_poolType, sizeof(T::value_type) * _amount));
				if (!arr) throw OutOfMemory;
				RtlZeroMemory(arr, sizeof(T) * size);
				return arr;
			}
		}
		static T* Allocate(size_t _amount)
		{
			try {
				auto arr = (ExAllocatePoolWithTag(T::m_poolType, sizeof(T::value_type) * _amount, T::m_tag));
				if (!arr) throw OutOfMemory;
				RtlZeroMemory(arr, sizeof(T) * size);
				return arr;
			}
		}
		
		Allocator() = delete;
		~Allocator() = delete;
		
	};
	template<K_VALID T>
	constexpr void* _cdecl operator new(size_t size, T) {
		return Allocator<T>::Allocate(size);
	}

	template<K_VALID T>
	constexpr void* _cdecl operator new[](size_t size, T) {
		return Allocator<T>::Allocate(size);
	}


	static void Deallocate(void* ptr, TAG tag)
	{
		ExFreePoolWithTag(ptr, tag);
	}

	static void Deallocate(void* ptr)
	{
		ExFreePool(ptr);
	} 

	constexpr void _cdecl operator delete(void* ptr) {
		Deallocate(ptr);
	}

	constexpr void _cdecl operator delete[](void* ptr) {
		Deallocate(ptr);
	}
		constexpr void _cdecl operator delete(void* ptr, TAG tag) {
		Deallocate(ptr,tag);
	}

	constexpr void _cdecl operator delete[](void* ptr, TAG tag) {
		Deallocate(ptr,tag);
	}

}