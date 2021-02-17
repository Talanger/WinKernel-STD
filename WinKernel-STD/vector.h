#pragma once
#include "memory.h"
#include "Iterator_types.h"
#include "initializer_list.h"
namespace kstd {
	template< class U, class Allocator = Allocator<U>>
	class vector {
		using value_type = U;
		using allocator_type = Allocator;
		using size_type = size_t;
		using Iterator = typename LegacyRandomAccessIterator<value_type>;
		using Const_Iterator = typename const LegacyRandomAccessIterator<value_type>;

		typedef value_type& reference;
		typedef const value_type& const_reference;
		value_type* m_data = nullptr;
		size_type m_size = 0;
		size_type m_capacity = 0;
	public:
		//element access
		constexpr const value_type* data() const noexcept { return m_data; }
		constexpr value_type front() const { if (m_data) return *m_data; throw 1; }//(DanglingPointerDereference); }
		constexpr value_type back() const { if (m_data) return *m_data[m_size - 1];  throw 1; }//(DanglingPointerDereference); }
		constexpr const value_type cfront() const { if (m_data) return *m_data; throw 1; }//(DanglingPointerDereference); }
		constexpr const value_type cback() const { if (m_data) return *m_data[m_size - 1];  throw 1; }//(DanglingPointerDereference); }
		constexpr const allocator_type get_allocator() const noexcept { return allocator_type; }
		constexpr POOL_TYPE getPoolType() const noexcept { return allocator_type::m_poolType; }
		Tag getTag() { return allocator_type::m_tag; }
		value_type* operator[](size_type pos) { return m_data[pos]; }
		value_type* at(size_type pos) {
			if (pos <= m_size and pos >= 0) return m_data[pos];  throw 1;
		}//(OutOfBounds); }
		//Iterators
		constexpr Iterator begin() noexcept;
		constexpr Const_Iterator begin() const noexcept;
		constexpr Const_Iterator cbegin() const noexcept;

		// capacity
		bool empty() { return m_capacity; }
		size_type size() { return m_size; }
		size_type capacity() { return m_capacity; }
		const void reserve(size_type size) {
			if (size > m_capacity)
			{
				m_capacity = size;
				value_type* new_data{ allocator_type::Allocate(m_capacity) };
				for (size_type i = 0; i < m_size; ++i)
				{
					new_data = m_data[i];
					delete m_data[i];
				}
				m_data = new_data;
			}
		}
		void shrink() { m_capacity = m_size; }
		//constructors/destructors

		~vector() { destroy(); }

		vector() {};

		constexpr vector(const vector& other) noexcept
			:m_capacity{ other.m_capacity },
			m_size{ other.m_size },
			m_data{ other.m_data } {}

		constexpr vector(vector&& other) noexcept :m_capacity{ other.m_capacity },
			m_size{ other.m_size },
			m_data{ other.m_data }
		{other.m_data = nullptr;}

		constexpr vector(initializer_list<value_type> init)
		{
			if (m_data) destroy();
			m_capacity = init.size();
			m_data = allocator_type::Allocate();
			for (m_size = 0; m_size < m_capacity; ++m_size)
			{
				m_data[*(init.begin() + m_size)];
			}
		}

		void operator=(const vector& cpy) {
			if (m_data) if (m_data) destroy();
			m_capacity = cpy.m_capacity;
			m_size = cpy.m_size;
			m_data = cpy.m_data;
		}
		constexpr vector& operator=(vector&& other) noexcept
		{
			m_capacity = other.m_capacity;
			m_size = other.m_size;
			m_data = other.m_data;
			other.m_data = nullptr;
		}
		//modifiers
		void destroy() {
			for (m_size -= 1; m_size >= 0; --m_size) delete m_data[m_size];
			m_capacity = m_size;
			m_data = nullptr;
		}

		void clear() { m_size = 0; }
		void insert(value_type& val) {
			if (m_size < m_capacity) m_data[m_size++] = val;
			else
			{
				m_capacity += 10;
				value_type* new_data{ allocator_type::Allocate(m_capacity) };
				for (size_type i = 0; i < m_size; ++i)
				{
					new_data = &m_data[i];
					delete m_data[i];
				}
				m_data = new_data;
				m_data[m_size++] = val;
			}
		}

		template<class ... Vals>
		void insert(value_type& val, Vals ... vals, bool checked = false)
		{
			if (checked or m_size + sizeof ...(vals) < m_capacity)
			{
				m_data[m_size++] = val;
			}
			else
			{
				reserve(m_size + sizeof ...(vals) + 1);
			}
			insert(vals..., true);
		}

		constexpr void resize(size_type count)
		{
		}
	};
}
