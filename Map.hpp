#ifndef MAP_HPP
# define MAP_HPP

# include "Utils.hpp"

namespace ft
{
	template<class Key, class T>
	class MapIterator;

	template<class Key, class T, class value_compare>
	class AVLtree
	{
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef std::pair<const Key, T> value_type;
		typedef typename MapIterator<Key, T>::node node;
		typedef MapIterator<key_type, mapped_type> iterator;
		typedef size_t size_type;
		value_compare cmp;

	public:
		AVLtree(const value_compare &cmp = value_compare()): cmp(cmp) {}
		~AVLtree() {}

		node *rotate_LL(node *parent)		//	 / L
		{									//	/  L
			node *child = parent->left;
			parent->left = child->right;	//NULL
			if (child->right)
				child->right->parent = parent;
			child->right = parent;
			child->parent = parent->parent;
			parent->parent = child;
			return child;
		}

		node *rotate_RR(node *parent)		// \  R
		{									//	\ R
			node *child = parent->right;
			parent->right = child->left;	//NULL
			if (child->left)
				child->left->parent = parent;
			child->left = parent;
			child->parent = parent->parent;
			parent->parent = child;
			return child;
		}

		node *rotate_RL(node *parent)		//	\ R
		{									//	/ L
			node *child = parent->right;
			parent->right = rotate_LL(child);
			return (rotate_RR(parent));
		}

		node *rotate_LR(node *parent)		//	/ L
		{									//	\ R
			node *child = parent->left;
			parent->left = rotate_RR(child);
			return (rotate_LL(parent));
		}

		int get_height(node *n, node *_last)
		{
			int height = 0;
			if (n != NULL && n != _last)
			{
				height = 1 + ((get_height(n->left, _last) > get_height(n->right, _last)) ? get_height(n->left, _last):get_height(n->right, _last));
			}
			return height;
		}

		int get_balance(node *n, node *_last)
		{	//height diff
			if (n == NULL)
				return 0;
			return get_height(n->left, _last) - get_height(n->right, _last);
		}

		node *make_balance(node *n, node *_last)
		{
			int height_diff = get_balance(n, _last);
			if (height_diff > 1)						//	/ L
			{
				if (get_balance((n)->left, _last) > 0)	//	/ L
					n = rotate_LL(n);
				else									//	\ R
					n = rotate_LR(n);
			}
			else if (height_diff < -1)					//	\ R
			{
				if (get_balance(n->right, _last) < 0)	//	\ R
					n = rotate_RR(n);
				else									//	/ L
					n = rotate_RL(n);
			}
			return n;
		}

		bool compare_node(value_type const v1, value_type const v2) const
		{
			return cmp(v1, v2);
		}

		std::pair<node *, bool>add_node(node *root, value_type v, node *parent, node *_last)
		{
			if (root == NULL)
			{
				root = new node(v, NULL, NULL, parent);
				return std::make_pair(root, true);
			}
			else if (compare_node(v, root->data))
			{
				// v < root
				std::pair<node *, bool> rtn = add_node(root->left, v, root, _last);
				root->left = rtn.first;
				root = make_balance(root, _last);
				if (rtn.second)
					return std::make_pair(root, true);
			}
			else if (compare_node(root->data, v))
			{
				// root < v
				if (root->right && root->right == _last)
				{
					node *new_node = new node(v, NULL, NULL, root);
					root->right = new_node;
					return std::make_pair(root, true);
				}

				std::pair<node *, bool> rtn = add_node(root->right, v, root, _last);
				root->right = rtn.first;
				root = make_balance(root, _last);
				if (rtn.second)
					return std::make_pair(root, true);
			}
			return std::make_pair(root, false);
		}

		node *search_node(node *n, Key k) const
		{
			if (n == NULL)
				return NULL;
			if (k == n->data.first)
				return n;
			else if (compare_node(std::pair<Key, T>(k, T()), n->data))
			{
				// k < n
				return search_node(n->left, k);
			}
			else
			{
				// n < k
				return search_node(n->right, k);
			}
			return NULL;
		}

		node *find_last(node *root, node *last)
		{
			if (root == NULL)
				return NULL;
			while (root->right && root->right != last)
				root = root->right;
			return root;
		}

		value_compare const &key_comp() const
		{
			return cmp;
		}

		iterator lower_bound (const iterator &first, const iterator &last, const key_type& k) const
		{
			for(iterator iter = first; iter != last; iter++)
			{
				if (!cmp(*iter, std::make_pair(k, mapped_type())))
					return iter;
			}
			return last;
		}

		iterator upper_bound (const iterator &first, const iterator &last, const key_type& k) const
		{
			for(iterator iter = first; iter != last; iter++)
			{
				if (cmp(std::make_pair(k, mapped_type()), *iter))
					return iter;
			}
			return last;
		}

	};




	/////////////////////Iterator////////////////////////////
	template<class Key, class T>
	class MapIterator
	{
	public:
		typedef std::pair<const Key, T> value_type;
		typedef std::ptrdiff_t difference_type;
		typedef value_type *pointer;
		typedef value_type &reference;
		typedef bidirectional_iterator_tag iterator_category;
		typedef size_t size_type;

		struct node
		{
			value_type data;
			node *left;
			node *right;
			node *parent;

			node(const value_type &data, node *left, node *right, node *parent): data(data), left(left), right(right), parent(parent) {}
		};
		node *_node;

	public:
		MapIterator() {}
		MapIterator(node *n): _node(n) {}
		~MapIterator() {}
		MapIterator(const MapIterator &other): _node(other._node) {}

		MapIterator &operator=(const MapIterator &other)
		{
			_node = other._node;
			return *this;
		}

		reference operator*() const
		{
			return _node->data;
		}

		pointer operator->() const
		{
			return &_node->data;
		}

		MapIterator<Key, T> &operator++()
		{
			if (_node->right)
			{
				_node = _node->right;
				while(_node->left)
					_node = _node->left;
			}
			else
			{
				node *tmp;
				do
				{
					tmp = _node;
					_node = _node->parent;
				} while (_node && tmp == _node->right);
			}
			return *this;
		}

		MapIterator<Key, T> operator++(int)
		{
			MapIterator<Key, T> tmp = *this;
			++(*this);
			return tmp;
		}

		MapIterator<Key, T> &operator--()
		{
			if (_node->left)
			{
				_node = _node->left;
				while (_node->left)
					_node = _node->right;
			}
			else
			{
				node *tmp;
				do
				{
					tmp = _node;
					_node = _node->parent;
				} while(_node && _node->left == tmp);
			}
			return *this;
		}

		MapIterator<Key, T> operator--(int)
		{
			MapIterator<Key, T> tmp = *this;
			--(*this);
			return tmp;
		}

		template<class _Key, class _T>
		friend bool operator==(const MapIterator<_Key, _T> &lhs, const MapIterator<_Key, _T> &rhs);

	};
	template<class Key, class T>
	bool operator==(const MapIterator<Key, T> &lhs, const MapIterator<Key, T> &rhs)
	{
		return (lhs._node == rhs._node);
	}

	template<class Key, class T>
	bool operator!=(const MapIterator<Key, T> &lhs, const MapIterator<Key, T> &rhs)
	{
		return !(lhs == rhs);
	}




	/////////////////////Map////////////////////////////////////
	template<class Key, class T, class Compare = std::less<Key> >
	class Map
	{
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef std::pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef value_type *pointer;
		typedef const value_type *const_pointer;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;

		class value_compare
		{
		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;

		private:
			value_compare() {}

		public:
			Compare comp;
			value_compare (Compare c) : comp(c) {}
			value_compare &operator=(const value_compare &other) {}
			value_compare(const value_compare &other): comp(other.comp) {}
			~value_compare() {}
			bool operator() (const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
		};
		typedef MapIterator<key_type, mapped_type> iterator;
		typedef MapIterator<key_type, mapped_type> const_iterator;
		typedef ReverseIterator<iterator> reverse_iterator;
		typedef ReverseIterator<const_iterator> const_reverse_iterator;

	private:
		typedef AVLtree<key_type, mapped_type, value_compare> avl_tree;
		avl_tree avl;
		typedef typename MapIterator<Key, T>::node node;

	public:
		node *root;
		node *_last;
		size_t len;

	public:
		explicit Map (const key_compare& comp = key_compare()): avl(value_compare(comp)), len(0)
		{
			_last = new node(value_type(), NULL, NULL, NULL);
			root = NULL;
		}

		template <class InputIterator>
		Map (InputIterator first, InputIterator last, const key_compare& comp = key_compare()): avl(value_compare(comp)), len(0)
		{
			_last = new node(value_type(), NULL, NULL, NULL);
			root = NULL;
			insert(first, last);
		}

		Map (const Map<Key, T, Compare> &other): avl(other.avl), len(0)
		{
			_last = new node(value_type(), NULL, NULL, NULL);
			root = NULL;
			insert(other.begin(), other.end());
		}

		~Map()
		{
			clear();
			delete _last;
		}

		//=operator
		Map<Key, T, Compare> &operator=(const Map<Key, T, Compare>& other)
		{
			clear();
			if (other.root)
				insert(other.begin(), other.end());
			return *this;
		}

		///////////////////////iterators////////////////////////////////
		iterator begin()
		{
			node *n = root;
			while (n && n->left)
				n = n->left;
			return iterator(n);
		}

		const_iterator begin() const
		{
			node *n = root;
			while (n && n->left)
				n = n->left;
			return const_iterator(n);
		}

		iterator end()
		{
			return iterator(_last);
		}

		const_iterator end() const
		{
			return const_iterator(_last);
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

		///////////////////////capacity///////////////////////////////
		bool empty() const
		{
			return len == 0;
		}

		size_type size() const
		{
			return len;
		}

		size_type max_size() const
		{
			return std::numeric_limits<difference_type>::max() / sizeof(value_type);
		}


		///////////////////////Element access//////////////////////////
		mapped_type& operator[] (const key_type& k)
		{
			return (*((this->insert(std::make_pair(k,mapped_type()))).first)).second;
		}


		///////////////////////Modifiers////////////////////////////////
		std::pair<iterator,bool> insert (const value_type& val)
		{
			std::pair<node *, bool> in = avl.add_node(root, val, NULL, _last);
			root = in.first;
			_last->parent = avl.find_last(root, _last);
			_last->parent->right = _last;
			node *search_n = avl.search_node(root, val.first);
			std::pair<iterator, bool> rtn(iterator(search_n), in.second);
			if (in.second)
				len++;
			return (rtn);
		}

		iterator insert (iterator position, const value_type& val)
		{
			std::pair<node *, bool> in = avl.add_node(root, val, NULL, _last);
			root = in.first;
			_last->parent = avl.find_last(root, _last);
			_last->parent->right = _last;
			node *search_n = avl.search_node(root, val.first);
			std::pair<iterator, bool> rtn(iterator(search_n), in.second);
			if (in.second)
				len++;
			return (rtn.first);
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			for(InputIterator iter = first; iter != last; iter++)
				insert(*iter);
		}

		void erase (iterator position)
		{
			if (position == iterator(_last))
				return ;
			node *n = position._node;
			node **x;
			if (!n->parent)
				x = &root;
			else
				x = n == n->parent->left ? &n->parent->left : &n->parent->right;

			if (n->right == _last)
			{
				if (n->left)
				{
					*x = n->left;
					n->left->parent = n->parent;
					n->right = _last;
					_last->parent = n->left;
				}
				else
				{
					*x = n->right;
					_last->parent = n->parent;
				}
			}
			else if (!n->left && !n->right)
				*x = NULL;
			else if ((n->left || n->right) && !(n->left && n->right))
			{
				*x = n->left ? n->left : n->right;
				(*x)->parent = n->parent;
			}
			else
			{
				node *ele = n->left;
				while (ele->right)
					ele = ele->right;
				if (ele->left)
				{
					node *l = ele->left;
					node *p = ele->parent;
					p->right = l;
					l->right = ele->left = ele->right = NULL;
					l->left = ele;
					ele->parent = l;
					l->parent = p;
				}
				if (n->left != ele)
				{
					ele->parent->left == ele ? ele->parent->left = NULL : ele->parent->right = NULL;
					ele->left = n->left;
					ele->right = n->right;
					ele->parent = n->parent;
					n->left->parent = ele;
					n->right->parent = ele;
				}
				else
				{
					ele->parent = n->parent;
					if (n->parent)
						n->parent->left == n ? n->parent->left = ele : n->parent->right = ele;
					ele->right = n->right;
					n->right->parent = ele;
				}
				*x = ele;
			}
			delete n;
			len--;
			root = avl.make_balance(root, _last);
			_last->parent = avl.find_last(root, _last);
			_last->parent->right = _last;
			if (len == 0)
				root = NULL;
		}

		size_type erase (const key_type& k)
		{
			if (root == NULL)
				return 0;
			iterator e = find(k);
			if (e == iterator(_last))
				return 0;
			erase(e);
			return 1;
		}

		void erase (iterator first, iterator last)
		{
			for(iterator iter = first; iter != last;)
			{
				iterator aft = ++iter;
				iter--;
				erase(iter);
				iter = aft;
			}
		}

		void swap (Map<Key, T, Compare> &other)
		{
			std::swap(other.root, root);
			std::swap(other._last, _last);
			std::swap(other.len, len);
		}

		void clear()
		{
			if (root)
			{
				erase(begin(), end());
				root = NULL;
			}
		}

		/////////////////////////observers//////////////////////////////
		key_compare key_comp() const
		{
			return avl.key_comp().comp;
		}

		value_compare value_comp() const
		{
			return avl.key_comp();
		}



		////////////////////////operations///////////////////////////////
		iterator find (const key_type& k)
		{
			node *rtn = avl.search_node(root, k);
			if (rtn == NULL)
				rtn = _last;
			return iterator(rtn);
		}

		const_iterator find (const key_type& k) const
		{
			node *rtn = avl.search_node(root, k);
			if (rtn == NULL)
				rtn = _last;
			return const_iterator(rtn);
		}

		size_type count (const key_type& k) const
		{
			node *rtn = avl.search_node(root, k);
			if (rtn == NULL)
				return 0;
			return 1;
		}

		iterator lower_bound (const key_type& k)
		{
			return avl.lower_bound(begin(), end(), k);
		}

		const_iterator lower_bound (const key_type& k) const
		{
			return avl.lower_bound(begin(), end(), k);
		}

		iterator upper_bound (const key_type& k)
		{
			return avl.upper_bound(begin(), end(), k);
		}

		const_iterator upper_bound (const key_type& k) const
		{
			return avl.upper_bound(begin(), end(), k);
		}

		std::pair<const_iterator,const_iterator> equal_range (const key_type& k) const
		{
			return std::make_pair(lower_bound(k), upper_bound(k));
		}

		std::pair<iterator,iterator> equal_range (const key_type& k)
		{
			return std::make_pair(lower_bound(k), upper_bound(k));
		}
	};
}

#endif