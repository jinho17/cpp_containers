#ifndef LIST_HPP
# define LIST_HPP

# include "Utils.hpp"
# include <iostream>

namespace ft
{
	template <typename T>
	class List;

	template <typename T>
	class ListIterator
	{
	public:
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef T *pointer;
		typedef T &reference;
		typedef bidirectional_iterator_tag iterator_category;

	public:
		typedef typename List<T>::node node;
		node *n;


	public:
		ListIterator(): n(NULL) {}
		ListIterator(node *node): n(node) {}
		ListIterator(const ListIterator<T> &other): n(other.n) {}
		~ListIterator() {}

		ListIterator<T> &operator=(const ListIterator<T> &other)
		{
			n = other.n;
			return (*this);
		}

		ListIterator<T> &operator++()
		{
			n = n->next;
			return (*this);
		}

		ListIterator<T> operator++(int)
		{
			ListIterator<T> tmp = *this;
			++(*this);
			return (tmp);
		}

		ListIterator<T> &operator--()
		{
			n = n->prev;
			return (*this);
		}

		ListIterator<T> operator--(int)
		{
			ListIterator<T> tmp = *this;
			--(*this);
			return (tmp);
		}

		reference operator*() const
		{
			return (n->value);
		}

		pointer operator->() const
		{
			return  (&n->value);
		}

		template <typename T_>
		friend bool operator==(const ListIterator<T_> &lhs, const ListIterator<T_> &rhs);
	};

	template <typename T>
	bool operator==(const ListIterator<T> &lhs, const ListIterator<T> &rhs)
	{
		return (lhs.n == rhs.n);
	}

	template <typename T>
	bool operator!=(const ListIterator<T> &lhs, const ListIterator<T> &rhs)
	{
		return !(lhs == rhs);
	}


	template <typename T>
	class List
	{
	public:
		typedef T value_type;
		typedef T &reference;
		typedef const T &const_reference;
		typedef T *pointer;
		typedef const T *const_pointer;
		typedef ListIterator<T> iterator;
		typedef ListIterator<const T> const_iterator;
		typedef ReverseIterator<iterator> reverse_iterator;
		typedef ReverseIterator<const_iterator> const_reverse_iterator;
		typedef std::ptrdiff_t difference_type;
		typedef size_t size_type;

	public:
		struct node
		{
			node *prev;
			node *next;
			T value;

			node(node *prev, node *next): prev(prev), next(next) {}
		};
		node *head;
		node *tail;
		size_type len;


	public:
		List(): len(0)
		{
			head = new node(NULL, NULL);
			tail = head;
		}

		explicit List (size_type n, const value_type& val = value_type()): len(0)
		{
			head = new node(NULL, NULL);
			tail = head;
			insert(iterator(head), n, val);
		}

		template <class InputIterator>
		List (InputIterator first, InputIterator last): len(0)
		{
			head = new node(NULL, NULL);
			tail = head;
			insert(iterator(head), first, last);
		}

		explicit List (const List<T> &other): len(0)
		{
			head = new node(NULL, NULL);
			tail = head;
			insert(iterator(head), other.begin(), other.end());
		}

		List<T> &operator=(const List<T> &other)
		{
			clear();
			insert(begin(), other.begin(), other.end());
			return *this;
		}

		~List()
		{
			erase(begin(), end());
			delete(tail);
		}


		//////////////////////Iterators///////////////
		iterator begin()
		{
			return iterator(head);
		}

		const_iterator begin() const
		{
			return const_iterator(reinterpret_cast<typename List<const T>::node *>(head));
		}

		iterator end()
		{
			return iterator(tail);
		}

		const_iterator end() const
		{
			return const_iterator(reinterpret_cast<typename List<const T>::node *>(tail));
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}

		//////////////Capacity///////////////////////
		bool empty() const
		{
			if (len == 0)
				return true;
			return false;
		}

		size_type size() const
		{
			return len;
		}

		size_type max_size() const
		{
			return (std::numeric_limits<difference_type>::max() / sizeof(value_type));
		}

		///////////////Element Access//////////////////
		reference front()
		{
			return head->value;
		}

		const_reference front() const
		{
			return head->value;
		}

		reference back()
		{
			return tail->prev->value;
		}

		const_reference back() const
		{
			return tail->prev->value;
		}

		///////////////Modifies//////////////////////
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

		void push_front (const value_type& val)
		{
			insert(begin(), val);
		}

		void pop_front()
		{
			erase(begin());
		}

		void push_back (const value_type& val)
		{
			insert(end(), val);
		}

		void pop_back()
		{
			iterator last = end();
			last--;
			erase(last);
		}

		iterator insert (iterator position, const value_type& val)
		{
			node *currrr = new node(position.n->prev, position.n);
			currrr->value = val;
			if (currrr->prev)
				currrr->prev->next = currrr;
			else
				head = currrr;
			currrr->next->prev = currrr;
			len++;
			return iterator(currrr);
		}

		void insert (iterator position, size_type n, const value_type& val)
		{
			node *prev = position.n->prev;
			node *next = position.n;
			node *p = prev;

			for(size_type i = 0; i < n; i++)
			{
				node *new_node = new node(p, NULL);
				new_node->value = val;
				if (new_node->prev)
					new_node->prev->next = new_node;
				else
					head = new_node;
				len++;
				p = new_node;
			}
			if (p)
				p->next = next;
			next->prev = p;
		}

		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last)
		{
			node *prev = position.n->prev;
			node *next = position.n;
			node *p = prev;

			for(InputIterator iter = first; iter != last; iter++)
			{
				node *new_node = new node(p, NULL);
				new_node->value = *iter;
				if (new_node->prev)
					new_node->prev->next = new_node;
				else
					head = new_node;
				len++;
				p = new_node;
			}
			if (p)
				p->next = next;
			next->prev = p;
		}

		iterator erase (iterator position)
		{
			iterator tmp;

			if (position.n->prev)
				position.n->prev->next = position.n->next;
			else
				head = position.n->next;
			if (position.n->next)
				position.n->next->prev = position.n->prev;
			if (position.n)
			{
				tmp = position;
				delete position.n;
				len--;
			}
			return ++tmp;
		}

		iterator erase (iterator first, iterator last)
		{
			iterator iter;

			for(iter = first; iter != last;)
				iter = erase(iter);
			return iter;
		}

		void swap (List& other)
		{
			std::swap(head, other.head);
			std::swap(tail, other.tail);
			std::swap(len, other.len);
		}

		void resize (size_type n, value_type val = value_type())
		{
			if (n >= len)
				insert(end(), n - len, val);
			else
			{
				iterator iter = begin();
				for(size_type i = 0; i < n; i++)
					iter++;
				erase(iter, end());
			}
		}

		void clear()
		{
			erase(begin(), end());
		}

		/////////////operations/////////////////
		void splice (iterator position, List<T> &other)
		{
			splice(position, other, other.begin(), other.end());
		}

		void splice (iterator position, List<T> &other, iterator i)
		{
			iterator next = i;
			next++;
			splice(position, other, i, next);
		}

		void splice (iterator position, List<T> &other, iterator first, iterator last)
		{
			node *to_left = position.n->prev;
			node *to_right = position.n;
			node *from_left = first.n->prev;
			node *from_right = last.n;

			int o_len = 0;
			for(iterator it = first; it != last; it++)
				o_len++;

			if (to_left)
				to_left->next = first.n;
			else
				head = first.n;
			first.n->prev = to_left;

			to_right->prev = last.n->prev;
			last.n->prev->next = to_right;

			if (from_left)
				from_left->next = from_right;
			else
				other.head = from_right;
			from_right->prev = from_left;

			len += o_len;
			other.len -= o_len;
		}

		void remove (const value_type& val)
		{
			for(iterator iter = begin(); iter != end();)
			{
				if (iter.n->value == val)
					iter = erase(iter);
				else
					iter++;
			}
		}

		template <class Predicate>
		void remove_if (Predicate pred)
		{
			for(iterator iter = begin(); iter != end();)
			{
				if (pred(*iter))
					iter = erase(iter);
				else
					iter++;
			}
		}

		void unique()
		{
			if (begin() == end())
				return;

			iterator currr = begin();
			iterator next = ++begin();

			while (next != end())
			{
				if (*currr == *next)
					next = erase(next);
				else
				{
					currr = next;
					next++;
				}
			}
		}

		template <class BinaryPredicate>
		void unique (BinaryPredicate binary_pred)
		{
			if (begin() == end())
				return;

			iterator currr = begin();
			iterator next = ++begin();

			while (next != end())
			{
				if (binary_pred(*currr, *next))
					next = erase(next);
				else
				{
					currr = next;
					next++;
				}
			}
		}

		void merge (List<T>& other)
		{
			splice (begin(), other);
			sort();
		}

		template <class Compare>
		void merge (List<T>& other, Compare comp)
		{
			splice (begin(), other);
			sort(comp);
		}

		void sort()
		{
			if (begin() == end())
				return;

			for (size_type i = 0; i < len; ++i)
			{
				iterator curr = begin();
				iterator next = begin();
				++next;
				while (next != end())
				{
					if (*curr > *next)
					{
						node *left = curr.n->prev;
						node *right = next.n->next;

						curr.n->prev = next.n;
						next.n->next = curr.n;
						if (left)
							left->next = next.n;
						else
							head = next.n;
						next.n->prev = left;
						right->prev = curr.n;
						curr.n->next = right;

						next = curr;
						++next;
					}
					else
					{
						curr = next;
						++next;
					}
				}
			}
		}

		template <class Compare>
		void sort (Compare comp)
		{
			if (begin() == end())
				return;

			for (size_type i = 0; i < len; ++i)
			{
				iterator curr = begin();
				iterator next = begin();
				++next;
				while (next != end())
				{
					if (!comp(*curr, *next))
					{
						node *left = curr.n->prev;
						node *right = next.n->next;

						curr.n->prev = next.n;
						next.n->next = curr.n;
						if (left)
							left->next = next.n;
						else
							head = next.n;
						next.n->prev = left;
						right->prev = curr.n;
						curr.n->next = right;

						next = curr;
						++next;
					}
					else
					{
						curr = next;
						++next;
					}
				}
			}
		}

		void reverse()
		{
			iterator iter = begin();
			iterator begin = iter;
			while (1)
			{
				iterator tmp = iter;
				++iter;
				if (tmp.n->next == tail)
				{
					tmp.n->next = tmp.n->prev;
					tmp.n->prev = NULL;
					head = tmp.n;
					break;
				}
				else
					std::swap(tmp.n->prev, tmp.n->next);
			}
			tail->prev = begin.n;
			begin.n->next = tail;
		}
	};

	template <class T>
	bool operator== (const List<T>& lhs, const List<T>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		ListIterator<const T> iter2 = rhs.begin();
		for(ListIterator<const T> iter = lhs.begin(); iter != lhs.end(); iter++, iter2++)
		{
			if (*iter != *iter2)
				return false;
		}
		return true;
	}

	template <class T>
	bool operator!= (const List<T>& lhs, const List<T>& rhs)
	{
		return !(lhs==rhs);
	}

	template <class T>
	bool operator< (const List<T>& lhs, const List<T>& rhs)
	{
		int equal = 0;

		ListIterator<const T> iter2 = rhs.begin();
		for(ListIterator<const T> iter = lhs.begin(); iter != lhs.end() && iter2 != rhs.end(); iter++, iter2++)
		{
			if (*iter < *iter2)
				return true;
			if (*iter == *iter2)
				equal++;
		}
		if (lhs.size() < rhs.size() && equal != 0)
			return true;
		return false;
	}

	template <class T>
	bool operator<= (const List<T>& lhs, const List<T>& rhs)
	{
		return !(lhs > rhs);
	}

	template <class T>
	bool operator>  (const List<T>& lhs, const List<T>& rhs)
	{
		return rhs < lhs;
	}

	template <class T>
	bool operator>= (const List<T>& lhs, const List<T>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class T>
	void swap (List<T>& x, List<T>& y)
	{
		x.swap(y);
	}
}

#endif