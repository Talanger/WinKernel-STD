#pragma once
namespace kstd
{
	

	template<class T> using __with_reference = T&;
	template<class T> concept is_referenceable
		= requires { typename __with_reference<T>; };
	template<class T> concept is_dereferenceable
		= requires(T & t) {
			{ *t } -> is_referenceable;
	};



}