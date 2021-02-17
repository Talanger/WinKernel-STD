#pragma once
//Msvsc has someproblems with conforming to the cpp preproccesor standards,
//therefore, we can't recognize the standard easily. so this library is c++20 exclusive

//TODO: ADD CONCEPTS
#include "cstddef.h"
namespace kstd
{
	template<class T, typename Distance = ptrdiff_t,
		typename Pointer = T*, typename Reference = T&>
		struct iterator
	{
		using  value_type = T;
		using  difference_type = Distance;
		using 	pointer = Pointer;
		using	reference = Reference;
	};

	template<class T, class _it = iterator<T>>
	struct LegacyIterator {
		using iterator_category = LegacyIterator;
		using value_type = typename _it::value_type;
		using difference_type = typename _it::difference_type;
		using pointer = typename _it::pointer;
		using reference = typename _it::reference;
	protected:
		pointer val;
	public:
		//Creating iterator to nullptr, DO NOT DEREFERENCE BEFORE INITIALIZATION!
		constexpr  LegacyIterator() noexcept : val{ nullptr } { }
		constexpr LegacyIterator(LegacyIterator& it) noexcept : val{ it.val } { }
		constexpr operator=(LegacyIterator& it) noexcept { val = it.val; }
		constexpr LegacyIterator(LegacyIterator&& it) noexcept : val{ it.val } { it.val = nullptr; }
		constexpr operator=(LegacyIterator&& it) noexcept { val = it.val; it.val = nullptr; }
		~LegacyIterator() { delete val; }
		reference operator*() const {
			return *val;
		}
		pointer operator->() const {
			return val;
		}
		iterator_category& operator++() {
			++val;
			return *this;
		}

		iterator_category& operator++(int) {
			iterator_category tmp = *this;
			++* this;
			return tmp;
		}
	};

	template<class T, class _it = iterator<T>>
	struct LegacyInputIterator : public LegacyIterator<_it> {
		using iterator_category = LegacyInputIterator;
		using super = LegacyIterator<_it>;
		using super::super;
		using value_type = typename _it::value_type;
		using difference_type = typename _it::difference_type;
		using pointer = typename _it::pointer;
		using reference = typename _it::reference;
	protected:
		using super::val;
	public:

		bool operator!=(const iterator_category& rhs)
		{
			return !(val == rhs);
		}
		bool operator==(const iterator_category& rhs)
		{
			return val == rhs.val;
		}

		operator void* () const { return static_cast<void>(val); }
	};
	template<class T, class _it = iterator<T>>
	struct LegacyForwardIterator : public LegacyInputIterator<_it> {
		using super = LegacyInputIterator<_it>;
		using super::super;
		using value_type = typename _it::value_type;
		using difference_type = typename _it::difference_type;
		using pointer = typename _it::pointer;
		using reference = typename _it::reference;
	protected:
		using super::val;
	public:
		using iterator_category = LegacyForwardIterator;
	};
	template<class T, class _it = iterator<T>>
	struct LegacyBidirectionalIterator : public LegacyForwardIterator<_it> {
		using super = LegacyForwardIterator<_it>;
		using super::super;
		using value_type = typename _it::value_type;
		using difference_type = typename _it::difference_type;
		using pointer = typename _it::pointer;
		using reference = typename _it::reference;
	protected:
		using super::val;
	public:
		using iterator_category = LegacyBidirectionalIterator;

		iterator_category& operator--() {
			--* this.val;
			return *this;
		}
		iterator_category& operator--(int) {
			iterator_category tmp = *this;
			--* this;
			return tmp;
		}
	};
	template<class T, class _it = iterator<T>>
	struct LegacyRandomAccessIterator : public LegacyBidirectionalIterator<_it> {
		using super = LegacyBidirectionalIterator<_it>;
		using super::super;
		using value_type = typename _it::value_type;
		using difference_type = typename _it::difference_type;
		using pointer = typename _it::pointer;
		using reference = typename _it::reference;
	protected:
		using super::val;
	public:
		using iterator_category = LegacyRandomAccessIterator;
		iterator_category& operator-=(const difference_type diff) {
			while (--diff > 0)
				++* this;
			return *this;
		}
		iterator_category& operator+=(const difference_type diff) {
			while (--diff > 0)
				++* this;
			return *this;
		}
		iterator_category& operator-(const difference_type diff) {
			iterator_category tmp = *this;
			while (--diff > 0)
				--tmp;
			return tmp;
		}
		iterator_category& operator+(const difference_type diff) {
			iterator_category tmp = *this;
			while (--diff > 0)
				++tmp;
			return tmp;
		}
	};

	template<class T, class _it = iterator<T>>
	struct LegacyContiguousIterator : public LegacyRandomAccessIterator<_it> {
		using super = LegacyBidirectionalIterator<_it>;
		using super::super;
		using value_type = typename _it::value_type;
		using difference_type = typename _it::difference_type;
		using pointer = typename _it::pointer;
		using reference = typename _it::reference;
	protected:
		using super::val;
	public:
		using iterator_category = LegacyContiguousIterator;
	};
}
