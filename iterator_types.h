#pragma once
//Msvsc has someproblems with conforming to the cpp preproccesor standards,
//therefore, we can't recognize the standard easily. so this library is c++20 exclusive
#include "cstddef.h"
namespace kstd
{

	template<class T, T val, typename Distance = ptrdiff_t,
		typename Pointer = T*, typename Reference = T&>
		struct iterator
	{
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		pointer val;

	};

	template<iterator _it>
	struct LegacyIterator {
		using iterator_category = LegacyIterator;
		using value_type		= _it::value_type;
		using difference_type   = _it::difference_type;
		using pointer		    = _it::pointer;
		using reference			= _it::reference;

		//Creating iterator to nullptr, DO NOT DEREFERENCE BEFORE INITIALIZATION!
		constexpr  LegacyIterator() noexcept : val{nullptr} { }
		constexpr LegacyIterator(LegacyIterator& it) noexcept: val{ it.val; }{ }
		constexpr operator=(LegacyIterator& it) noexcept:  val{ it.val; }{ }
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

		iterator_category& operator++(int){
			iterator_category tmp = *this;
			++*this;
			return tmp;
		}

	};

	template<iterator _it>
	struct LegacyInputIterator : public LegacyIterator {
		using super = LegacyIterator;
		using super::super; // calling base constructor as there is no need for us to re implement
		using iterator_category = LegacyInputIterator;


	};
	template<iterator _it>
	struct LegacyForwardIterator : public LegacyInputIterator {
		using super = LegacyInputIterator;
		using super::super; // calling base constructor as there is no need for us to re implement
		using iterator_category = LegacyForwardIterator;
	};
	template<iterator _it>
	struct LegacyBidirectionalIterator : public LegacyForwardIterator {
		using super = LegacyForwardIterator;
		using super::super; // calling base constructor as there is no need for us to re implement
		using iterator_category = LegacyBidirectionalIterator;
	};
	template<iterator _it>
	struct LegacyRandomAccessIterator : public LegacyBidirectionalIterator {
		using super = LegacyBidirectionalIterator;
		using super::super; // calling base constructor as there is no need for us to re implement
		using iterator_category = LegacyRandomAccessIterator;
	};
	template<iterator _it>
	struct LegacyContiguousIterator : public LegacyRandomAccessIterator {
		using super = LegacyBidirectionalIterator;
		using super::super; // calling base constructor as there is no need for us to re implement
		using iterator_category = LegacyContiguousIterator;
	};

}
