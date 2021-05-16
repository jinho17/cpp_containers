#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>

namespace ft
{
	//iterator의 category를 구별하는데 사용되는 빈 구조체
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};
	struct contiguous_iterator_tag: public random_access_iterator_tag {};


	//iterator의 속성에 대한 균일한 인터페이스를 제공하는 type trait class.
	template <typename Iter>
	struct iterator_traits
	{
		typedef typename Iter::difference_type difference_type;
		typedef typename Iter::value_type value_type;
		typedef typename Iter::pointer pointer;
		typedef typename Iter::reference reference;
		typedef typename Iter::iterator_category iterator_category;
	};
	template <typename T>
	struct iterator_traits<T*>
	{
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef random_access_iterator_tag iterator_category;
	};
	template<typename T>
	struct iterator_traits<const T*>
	{
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T *pointer;
		typedef const T &reference;
		typedef random_access_iterator_tag iterator_category;
	};


	////////////////////Reverse Iterator/////////////////
	template <typename Iter>
	class ReverseIterator
	{
	private:
		Iter curr;

	public:
		typedef Iter iterator_type;
		typedef typename iterator_traits<Iter>::iterator_category iterator_category;
		typedef typename iterator_traits<Iter>::value_type value_type;
		typedef typename iterator_traits<Iter>::difference_type difference_type;
		typedef typename iterator_traits<Iter>::pointer pointer;
		typedef typename iterator_traits<Iter>::reference reference;

		ReverseIterator() {}
		explicit ReverseIterator(iterator_type curr): curr(curr) {}
		ReverseIterator(const ReverseIterator<Iter> &other): curr(other.curr) {}
		~ReverseIterator() {}

		ReverseIterator<Iter> &operator=(const ReverseIterator<Iter> &other)
		{
			curr = other.curr;
			return (*this);
		}

		iterator_type base() const
		{
			return (curr);
		}

		reference operator*() const
		{
			Iter rtn(curr);
			return (*--rtn);
		}

		pointer operator->() const
		{
			Iter rtn(curr);
			--rtn;
			return rtn.operator->();
		}

		ReverseIterator<Iter> &operator++()
		{
			--curr;
			return (*this);
		}

		ReverseIterator<Iter> &operator++(int)
		{
			ReverseIterator<Iter> rtn(curr--);
			return (rtn);
		}

		ReverseIterator<Iter> &operator--()
		{
			++curr;
			return (*this);
		}

		ReverseIterator<Iter> &operator--(int)
		{
			ReverseIterator<Iter> rtn(curr++);
			return (rtn);
		}

		ReverseIterator<Iter> &operator+=(difference_type n)
		{
			curr -= n;
			return (*this);
		}

		ReverseIterator<Iter> &operator-=(difference_type n)
		{
			curr += n;
			return (*this);
		}

		ReverseIterator<Iter> &operator+(difference_type n) const
		{
			return (ReverseIterator<Iter>(curr - n));
		}

		ReverseIterator<Iter> &operator-(difference_type n) const
		{
			return (ReverseIterator<Iter>(curr + n));
		}

		reference operator[](difference_type n) const
		{
			base()[-n-1];
		}
	};

	template <typename Iter>
	bool operator==(const ReverseIterator<Iter> &lhs, const ReverseIterator<Iter> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <typename Iter>
	bool operator!=(const ReverseIterator<Iter>& lhs, const ReverseIterator<Iter>& rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <typename Iter>
	bool operator<(const ReverseIterator<Iter>& lhs, const ReverseIterator<Iter>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <typename Iter>
	bool operator>(const ReverseIterator<Iter>& lhs, const ReverseIterator<Iter>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <typename Iter>
	bool operator<=(const ReverseIterator<Iter>& lhs, const ReverseIterator<Iter>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <typename Iter>
	bool operator>=(const ReverseIterator<Iter>& lhs, const ReverseIterator<Iter>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <typename Iter>
	ReverseIterator<Iter> operator+(typename ReverseIterator<Iter>::difference_type n, const ReverseIterator<Iter>& rev_it)
	{
		return (ReverseIterator<Iter>(rev_it.base() - n));
	}

	template <typename Iter>
	typename ReverseIterator<Iter>::difference_type operator-(const ReverseIterator<Iter>& lhs, const ReverseIterator<Iter>& rhs)
	{
		return (rhs.base() - lhs.base());
	}
}

#endif
