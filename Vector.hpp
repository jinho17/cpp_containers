#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "Utils.hpp"
# include <memory>

namespace ft
{
	template <class T>
	class Vector;

	template <class T>
	class VectorIterator
	{
	public:
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef T *pointer;
		typedef T &reference;
		typedef random_access_iterator_tag iterator_category;

	public:
		pointer ele;

	public:
		VectorIterator(): ele(NULL) {}
		VectorIterator(pointer ele): ele(ele) {}
		~VectorIterator() {}
		VectorIterator(const VectorIterator<T> &other): ele(other.ele) {}
		VectorIterator<T> &operator=(const VectorIterator<T> &other)
		{
			ele = other.ele;
			return *this;
		}

		reference operator*() const
		{
			return *ele;
		}

		pointer operator->() const
		{
			return ele;
		}

		VectorIterator<T> &operator++()
		{
			++ele;
			return *this;
		}

		VectorIterator<T> operator++(int)
		{
			VectorIterator<T> ori = *this;
			++ele;
			return ori;
		}

		VectorIterator<T> &operator--()
		{
			--ele;
			return *this;
		}

		VectorIterator<T> operator--(int)
		{
			VectorIterator<T> ori = *this;
			--ele;
			return ori;
		}

		VectorIterator<T> &operator+=(size_t n)
		{
			ele += n;
			return *this;
		}

		VectorIterator<T> &operator-=(size_t n)
		{
			ele -= n;
			return *this;
		}

		reference operator[](difference_type n) const
		{
			return *(*this + n);
		}

		template <typename T_>
		friend bool operator==(const VectorIterator<T_> &lhs, const VectorIterator<T_> &rhs);

		template <typename T_>
		friend VectorIterator<T_> operator+(const VectorIterator<T_> &iter, size_t n);

		template <typename T_>
		friend VectorIterator<T_> operator-(const VectorIterator<T_> &iter, size_t n);

		template <typename T_>
		friend ptrdiff_t operator-(const VectorIterator<T_> &lhs, const VectorIterator<T_> &rhs);

		template <typename T_>
		friend bool operator<(const VectorIterator<T_> &lhs, const VectorIterator<T_> &rhs);
	};

	template <typename T>
	bool operator==(const VectorIterator<T> &lhs, const VectorIterator<T> &rhs)
	{
		return lhs.ele == rhs.ele;
	}

	template <typename T>
	bool operator!=(const VectorIterator<T> &lhs, const VectorIterator<T> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T>
	VectorIterator<T> operator+(const VectorIterator<T> &iter, size_t n)
	{
		return (iter.ele + n);
	}

	template <typename T>
	VectorIterator<T> operator+(size_t n, const VectorIterator<T> &iter)
	{
		return iter + n;
	}

	template <typename T>
	VectorIterator<T> operator-(const VectorIterator<T> &iter, size_t n)
	{
		return (iter.ele - n);
	}

	template <typename T>
	ptrdiff_t operator-(const VectorIterator<T> &lhs, const VectorIterator<T> &rhs)
	{
		return lhs.ele - rhs.ele;
	}

	template <typename T>
	bool operator<(const VectorIterator<T> &lhs, const VectorIterator<T> &rhs)
	{
		return lhs.ele < rhs.ele;
	}

	template <typename T>
	bool operator>(const VectorIterator<T> &lhs, const VectorIterator<T> &rhs)
	{
		return rhs < lhs;
	}

	template <typename T>
	bool operator<=(const VectorIterator<T> &lhs, const VectorIterator<T> &rhs)
	{
		return !(lhs > rhs);
	}

	template <typename T>
	bool operator>=(const VectorIterator<T> &lhs, const VectorIterator<T> &rhs)
	{
		return !(lhs < rhs);
	}


	//////////////////////vector//////////////////////
	template <class T>
	class Vector
	{
	public:
		typedef T value_type;
		typedef T &reference;
		typedef const T &const_reference;
		typedef T *pointer;
		typedef const T *const_pointer;
		typedef VectorIterator<T> iterator;
		typedef VectorIterator<const T> const_iterator;
		typedef ReverseIterator<iterator> reverse_iterator;
		typedef ReverseIterator<const_iterator> const_reverse_iterator;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;

	public:
		pointer arr;
		size_type len;
		size_type _capacity;

	public:
		explicit Vector(): arr(NULL), len(0), _capacity(0) {}

		explicit Vector(size_type n, const value_type& val = value_type()): arr(NULL), len(0), _capacity(0)
		{
			insert(begin(), n, val);
		}

		template <class InputIterator>
		Vector (InputIterator first, InputIterator last): arr(NULL), len(0), _capacity(0)
		{
			insert(begin(), first, last);
		}

		Vector (const Vector& other): arr(NULL), len(0), _capacity(0)
		{
			insert(begin(), other.begin(), other.end());
		}

		~Vector()
		{
			std::allocator<T> alloc;

			for(size_type i = 0; i < len; i++)
				alloc.destroy(&arr[i]);
			alloc.deallocate(arr, _capacity);
		}

		Vector<T> &operator=(const Vector<T> &other)
		{
			clear();
			insert(begin(), other.begin(), other.end());
			return *this;
		}


		////////////////////iterators//////////////////
		iterator begin()
		{
			return arr;
		}

		const_iterator begin() const
		{
			return arr;
		}

		iterator end()
		{
			return arr + len;
		}

		const_iterator end() const
		{
			return arr + len;
		}

		reverse_iterator rbegin()
		{
			return ReverseIterator<VectorIterator<T> >(end());
		}

		const_reverse_iterator rbegin() const
		{
			return ReverseIterator<VectorIterator<T> >(end());
		}

		reverse_iterator rend()
		{
			return ReverseIterator<VectorIterator<T> >(begin());
		}

		const_reverse_iterator rend() const
		{
			return ReverseIterator<VectorIterator<T> >(begin());
		}


		////////////////////_capacity////////////////////
		size_type size() const
		{
			return len;
		}

		size_type max_size() const
		{
			return std::numeric_limits<difference_type>::max() / sizeof(T);
		}

		void resize (size_type n, value_type val = value_type())
		{
			if (n >= len)
				insert(end(), n - len, val);
			else
				erase(begin() + n, end());
		}

		size_type capacity() const
		{
			return _capacity;
		}

		bool empty() const
		{
			return len == 0;
		}

		void reserve (size_type new_capacity)
		{
			if (new_capacity <= _capacity || new_capacity == 0)
				return ;

			if (new_capacity < _capacity * 2)
				new_capacity = _capacity * 2;

			std::allocator<T> alloc;
			T *new_arr = alloc.allocate(new_capacity);
			for(size_type i = 0; i < len; i++)
			{
				alloc.construct(&new_arr[i], arr[i]);
				alloc.destroy(&arr[i]);
			}
			alloc.deallocate(arr, _capacity);
			arr = new_arr;
			_capacity = new_capacity;
		}


		////////////////////element access///////////////
		reference operator[] (size_type n)
		{
			return arr[n];
		}

		const_reference operator[] (size_type n) const
		{
			return arr[n];
		}

		reference at (size_type n)
		{
			if (n >= len)
				throw std::out_of_range("Vector.at: out of range");
			return arr[n];
		}

		const_reference at (size_type n) const
		{
			if (n >= len)
				throw std::out_of_range("Vector.at: out of range");
			return arr[n];
		}

		reference front()
		{
			return arr[0];
		}

		const_reference front() const
		{
			return arr[0];
		}

		reference back()
		{
			return (arr[len - 1]);
		}

		const_reference back() const
		{
			return (arr[len - 1]);
		}


		////////////////////modifiers////////////////////
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last)
		{
			clear();
			insert(begin(), first, last);
		}

		void assign (size_type n, const value_type& val)
		{
			clear();
			insert(begin(), n, val);
		}

		void push_back (const value_type& val)
		{
			insert(end(), val);
		}

		void pop_back()
		{
			erase(end() - 1);
		}

		iterator insert (iterator position, const value_type& val)
		{
			size_type idx = position.ele - arr;
			insert(position, (size_t)1, val);
			return arr + idx;
		}

		void insert (iterator position, size_type n, const value_type& val)
		{
			if (n == 0)
				return ;

			std::allocator<T> alloc;
			size_type idx = position.ele - arr;

			reserve(len + n);
			for(ptrdiff_t i = len - 1; i >= (ptrdiff_t)idx; i--)
			{
				alloc.construct(&arr[i + n], arr[i]);
				alloc.destroy(&arr[i]);
			}
			for(size_type i = idx; i < idx + n; i++)
				alloc.construct(&arr[i], val);
			len += n;
		}

		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last)
		{
			std::allocator<T> alloc;
			size_type idx = position.ele - arr;
			size_type n = 0;
			InputIterator it;
			for(it = first; it != last; it++)
				n++;
			if (n == 0)
				return ;

			reserve(len + n);
			for(ptrdiff_t i = len - 1; i >= (ptrdiff_t)idx; i--)
			{
				alloc.construct(&arr[i + n], arr[i]);
				alloc.destroy(&arr[i]);
			}
			size_type i = idx;
			for(it = first; it != last; it++)
				alloc.construct(&arr[i++], *it);
			len += n;
		}

		iterator erase (iterator position)
		{
			return erase(position, position + 1);
		}

		iterator erase (iterator first, iterator last)
		{
			std::allocator<T> alloc;
			size_type n = last - first;
			if (n <= 0)
				return last;

			size_type idx = first.ele - arr;
			for(size_type i = idx; i < idx + n; i++)
				alloc.destroy(&arr[i]);
			for(size_type i = idx + n; i < len; i++)
			{
				alloc.construct(&arr[i - n], arr[i]);
				alloc.destroy(&arr[i]);
			}
			len -= n;
			return first;
		}

		void swap (Vector<int> &other)
		{
			std::swap(arr, other.arr);
			std::swap(len, other.len);
			std::swap(_capacity, other._capacity);
		}

		void clear()
		{
			erase(begin(), end());
		}
	};

	template <class T>
	bool operator== (const Vector<T>& lhs, const Vector<T>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		for(size_t i = 0; i < lhs.size(); i++)
			if (lhs.arr[i] != rhs.arr[i])
				return false;
		return true;
	}

	template <class T>
	bool operator!= (const Vector<T>& lhs, const Vector<T>& rhs)
	{
		return !(lhs==rhs);
	}

	template <class T>
	bool operator<  (const Vector<T>& lhs, const Vector<T>& rhs)
	{
		int equal = 0;

		for(size_t i = 0; lhs.arr[i] && rhs.arr[i]; i++)
		{
			if (lhs.arr[i] < rhs.arr[i])
				return true;
			if (lhs.arr[i] == rhs.arr[i])
				equal++;
		}
		if (lhs.size() < rhs.size() && equal != 0 )
			return true;
		return false;
	}

	template <class T>
	bool operator<= (const Vector<T>& lhs, const Vector<T>& rhs)
	{
		return !(lhs > rhs);
	}

	template <class T>
	bool operator>  (const Vector<T>& lhs, const Vector<T>& rhs)
	{
		return rhs < lhs;
	}

	template <class T>
	bool operator>= (const Vector<T>& lhs, const Vector<T>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class T>
	void swap (Vector<T>& x, Vector<T>& y)
	{
		x.swap(y);
	}
}

#endif