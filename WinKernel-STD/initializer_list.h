#pragma once
namespace kstd
{
	template <class T>
	class initializer_list;

	template <class T>
	struct initializer_list
	{
		using value_type = T;
		using reference = const T&;
		using const_reference = const T&;
		using size_type = size_t;
		using iterator = const T*;
		using const_iterator  =  const T*;
		constexpr initializer_list() : m_data(0), m_size(0) { }
		constexpr size_type size() { return m_size; }
		constexpr const_iterator begin() { return m_data; }
		constexpr const_iterator end() { return begin() + m_size; }
	private:
		size_type m_size;
		iterator m_data;

		constexpr initializer_list(const_iterator it, size_type len) : m_data(it), m_size(len) { }

	};

	template<class T>
	constexpr const T* begin(initializer_list<T> init_list) { return init_list.begin(); }
	template<class T>
	constexpr const T* end(initializer_list<T> init_list) { return init_list.end(); }
}
