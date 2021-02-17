#pragma once
#include "cstddef.h"
#include <ntddk.h>
#include "error.h"

#ifndef _TAG_
#define _TAG_
constexpr ULONG TAG = 'KSTD';
#endif // !_TAG_

namespace kstd
{
	using Tag = ULONG;

	template<class T, Tag tag = TAG, POOL_TYPE poolType = NonPagedPool>
	struct K_TYPE
	{
		using value_type = T;
		using ktype = K_TYPE;
		static const POOL_TYPE m_poolType = poolType;
		static const Tag m_Tag = tag;
	};

	/*template <class T >
	concept K_VALID = requires(T t) {
		typename T::value_type; // required nested member name
		typename T::m_poolType; // required nested member name
		typename T::m_Tag; // required nested member name
	};
	template<K_VALID T> struct Allocator;*/

	template<class U, class K = K_TYPE<U>>
	struct Allocator
	{
		using info = K;
		static U* Allocate(size_t _amount)
		{
			auto arr = (ExAllocatePoolWithTag(info::m_poolType, sizeof(info::value_type) * _amount, info::m_Tag));
			if (!arr) throw 1;//OutOfMemory;
			RtlZeroMemory(arr, sizeof(U) * _amount);
			return static_cast<U*>(arr);
		}
		static void Deallocate(void* ptr)
		{
			ExFreePoolWithTag(ptr, info::tag);
		}

		Allocator() = delete;
		~Allocator() = delete;
	};
}

template<class U>
constexpr void* _cdecl operator new(size_t size, kstd::Tag tag = TAG, POOL_TYPE pt = NonPagedPool) {
	return Allocator<kstd::K_TYPE<U, tag, pt>>::value_type > ::Allocate(size);
}

template<class U>
constexpr void* _cdecl operator new[](size_t size, kstd::Tag tag = TAG, POOL_TYPE pt = NonPagedPool) {
	return Allocator<kstd::K_TYPE<U, tag, pt>>::Allocate(size);
}

template<class U, class K>
void _cdecl operator delete(void* ptr, kstd::Allocator<U, K> A) {
	decltype(A)::Deallocate(ptr);
}

template<class U, class K>
void _cdecl operator delete[](void* ptr, kstd::Allocator<U, K> A) {
	decltype(A)::Deallocate(ptr);
}