#ifndef QUEUE_HPP
# define QUEUE_HPP

#include "List.hpp"

namespace ft
{
	template <class T, class Container = List<T> >
	class Queue
	{
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;

	public:
		container_type ctnr;

	public:
		explicit Queue (const container_type& ctnr = container_type()): ctnr(ctnr) {}

		~Queue() {}

		Queue<T, Container>(const Queue<T, Container> &other): ctnr(other.ctnr) {}

		Queue<T, Container> &operator=(const Queue<T, Container> &other)
		{
			ctnr = other.ctnr;
			return *this;
		}


		bool empty() const
		{
			return ctnr.empty();
		}

		size_type size() const
		{
			return ctnr.size();
		}

		value_type& front()
		{
			return ctnr.front();
		}

		const value_type& front() const
		{
			return ctnr.front();
		}

		value_type& back()
		{
			return ctnr.back();
		}

		const value_type& back() const
		{
			return ctnr.back();
		}

		void push (const value_type& val)
		{
			ctnr.push_back(val);
		}

		void pop()
		{
			ctnr.pop_front();
		}


		template <class T_, class Container_>
		friend bool operator== (const Queue<T,Container_>& lhs, const Queue<T,Container_>& rhs);

		template <class T_, class Container_>
		friend bool operator<  (const Queue<T,Container_>& lhs, const Queue<T,Container_>& rhs);

		template< class T_, class Container_ >
		friend void swap(Queue<T_,Container_>& lhs, Queue<T_,Container_>& rhs);
	};

	template <class T, class Container>
	bool operator== (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs)
	{
		return lhs.ctnr == rhs.ctnr;
	}

	template <class T, class Container>
	bool operator!= (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Container>
	bool operator<  (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs)
	{
		return lhs.ctnr < rhs.ctnr;
	}

	template <class T, class Container>
	bool operator<= (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs)
	{
		return !(lhs > rhs);
	}

	template <class T, class Container>
	bool operator>  (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs)
	{
		return rhs < lhs;
	}

	template <class T, class Container>
	bool operator>= (const Queue<T,Container>& lhs, const Queue<T,Container>& rhs)
	{
		return !(lhs < rhs);
	}

	template< class T, class Container >
	void swap( Queue<T,Container>& lhs, Queue<T,Container>& rhs )
	{
		ft::swap(lhs.ctnr, rhs.ctnr);
	}

} // namespace ft


#endif