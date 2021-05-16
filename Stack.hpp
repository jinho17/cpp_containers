#ifndef STACK_HPP
# define STACK_HPP

# include "Vector.hpp"

namespace ft
{
	template <class T, class Container = Vector<T> >
	class Stack
	{
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;

	public:
		container_type ctnr;

	public:
		explicit Stack (const container_type& ctnr = container_type()): ctnr(ctnr) {}

		~Stack() {}

		Stack(const Stack<T, Container> &other): ctnr(other.ctnr) {}

		Stack<T, Container> &operator=(const Stack<T, Container> &other)
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

		value_type& top()
		{
			return ctnr.back();
		}

		const value_type& top() const
		{
			return ctnr.back();
		}

		void push (const value_type& val)
		{
			return ctnr.push_back(val);
		}

		void pop()
		{
			ctnr.pop_back();
		}

		template <class T_, class Container_>
		friend bool operator== (const Stack<T_,Container_>& lhs, const Stack<T_,Container_>& rhs);

		template <class T_, class Container_>
		friend bool operator<  (const Stack<T_,Container_>& lhs, const Stack<T_,Container_>& rhs);

		template<class T_, class Container_>
		friend void swap(Stack<T_,Container_>& lhs, Stack<T_,Container_>& rhs );
	};

	template <class T, class Container>
	bool operator== (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
	{
		return lhs.ctnr == rhs.ctnr;
	}

	template <class T, class Container>
	bool operator!= (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Container>
	bool operator<  (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
	{
		return lhs.ctnr < rhs.ctnr;
	}

	template <class T, class Container>
	bool operator<= (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
	{
		return !(lhs > rhs);
	}

	template <class T, class Container>
	bool operator>  (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
	{
		return rhs.ctnr < lhs.ctnr;
	}

	template <class T, class Container>
	bool operator>= (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs)
	{
		return !(lhs < rhs);
	}

	template<class T, class Container>
	void swap(Stack<T,Container>& lhs, Stack<T,Container>& rhs )
	{
		ft::swap(lhs.ctnr, rhs.ctnr);
	}

}

#endif