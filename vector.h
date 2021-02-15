#pragma once
#include "memory.h"
#include "initializer_list.h"
namespace kstd {
	template< K_VALID T, class Allocator = Allocator<T>>
	class vector {
		using value_type = T::value_type;
		using allocator_type = Allocator;
		using size_typeype = sizet
		using iterator = LegacyRandomAccessIterator<value_type>;
		using const_iterator = const kstd::LegacyRandomAccessIterator<value_type>;
		using reverse_iterator = kstd::reverse_iterator<iterator>;
		using const_reverse_iterator = kstd::reverse_iterator<const_iterator>;
		using reference = value_type&;
		using const_reference = const value_type&;
		value_type* m_data = nullptr;
		size_type m_size = 0;
		size_type m_capacity = 0;
	public:

		//element access
		constexpr const value_type* data() const noexcept { return _data };
		constexpr value_type front() const { if (_data) return *_data; throw(DanglingPointerDereference); }
		constexpr value_type back() const { if (_data) return *_data[m_size - 1]; throw(DanglingPointerDereference); }
		constexpr const value_type front() const { if (_data) return *_data; throw(DanglingPointerDereference); }
		constexpr const value_type back() const { if (_data) return *_data[m_size - 1]; throw(DanglingPointerDereference); }
		constexpr const allocator_type get_allocator() const noexcept { return allocator_type; }
		POOL_TYPE getPoolType{ return allocator_type::m_poolType; }
		TAG getTag{ return allocator_type::m_tag; }
		value_type* operator[](size_type pos) { return m_data[pos]; }
		value_type* at(size_type pos) { if (pos <= m_size and pos >= 0) return m_data[pos]; throw(OutOfBounds); }
		//iterators
		constexpr iterator begin() noexcept;
		constexpr const_iterator begin() const noexcept;
		constexpr const_iterator cbegin() const noexcept;

		// capacity
		bool empty() { return m_capacity; }
		size_type size() { return m_size; }
		size_type capacity() { return m_capacity; }
		const void reserve(size_type size) {
			if (size > m_capacity)
			{
				m_capacity = size;
				value_type* new_data{ allocator_type::Allocate(m_capacity); };
				for (size_type i = 0; i < m_size; ++i)
				{
					new_data = m_data[i];
					delete m_data[i];

				}
				m_data = new_data;
			}
		}
		void shrink() { m_capacity = m_size };
		//constructors/destructors

		~vector() { destroy(); }

		vector() {};



		void vector(const vector& cpy) {
			if (m_data) if (m_data) destroy();
			m_capacity{ cpy.m_capacity };
			m_size{ cpy.m_size };
			m_data = cpy.m_data;
		}

		constexpr vector(vector&& other) noexcept :m_capacity{ other.m_capacity },
			m_size{other.m_size},
			m_data{other.m_data}
		{other.m_data = nullptr;}

		constexpr vector(initializer_list<T> init)
		{
			if (m_data) destroy();
			m_capacity = init.size();
			m_data = allocator_type::Allocate();
			for (m_size{ 0 }; m_size < m_capacity; ++m_size)
			{
				m_data[*(init.begin() + m_size)];
			}
		}

		void operator=(const vector& cpy) {
			if (m_data) if (m_data) destroy();
			m_capacity{ cpy.m_capacity };
			m_size{ cpy.m_size };
			m_data = cpy.m_data;
		}
		constexpr vector& operator=(vector&& other) noexcept
		{
			m_capacity{ other.m_capacity };
			m_size{ other.m_size };
			m_data{ other.m_data };
			other.m_data = nullptr;
		}
		//modifiers
		void destroy() {
			for (m_size -= 1; m_size >= 0; --i) delete m_data[m_size];
			m_capacity = m_size;
			m_data = nullptr;
		}

		void clear() { m_size = 0; }
		void insert(value_type& val) {
			if (m_size < m_capacity) _data[m_size++] = val;
			else
			{
				m_capacity += 10;
				value_type* new_data{ allocator_type::Allocate(m_capacity); };
				for (size_type i = 0; i < m_size; ++i)
				{
					new_data = m_data[i];
					delete m_data[i];
				}
				m_data = new_data;
				m_data[m_size++] = val;
			}
		}
		void insert(value_type& val, value_type& ... vals, bool checked = false)
		{
			if (checked or m_size + sizeof ...(vals) < m_capacity)
			{
				m_data[m_size++] = val;
			}
			else
			{
				reserve(m_size + sizeof ...(vals) + 1);
			}
			insert(...vals, true);
		}

		constexpr void resize(size_type count)
		{

		}
	};
}
