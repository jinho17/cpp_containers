#include "main.hpp"

void list_constructor()
{
	ft::List<int> first;
	std::cout << "1) default constructor size: " << first.size() << std::endl;

	ft::List<int> second((size_t)4, 100);
	std::cout << "2) size=4, value=100 constructor: ";
	for (ft::List<int>::iterator it = second.begin(); it != second.end(); it++)
		std::cout << *it << ' ';
	std::cout << '\n';

	ft::List<int> third(second.begin(), second.end());
	std::cout << "3) iterator constructor:\t";
	for (ft::List<int>::iterator it = third.begin(); it != third.end(); it++)
		std::cout << *it << ' ';
	std::cout << '\n';

	ft::List<int> fourth(third);
	std::cout << "4) copy constructor:\t\t";
	for (ft::List<int>::iterator it = fourth.begin(); it != fourth.end(); it++)
		std::cout << *it << ' ';
	std::cout << '\n';

	int myints[] = {1,2,3,4,5};
	ft::List<int> fifth(myints, myints + sizeof(myints) / sizeof(int));
	std::cout << "5) iterator constructor from array: ";
	for (ft::List<int>::iterator it = fifth.begin(); it != fifth.end(); it++)
		std::cout << *it << ' ';
	std::cout << '\n';

	ft::List<int> sixth(3);	// 0 0 0
	sixth = fifth;
	fifth = ft::List<int>();
	std::cout << "6) = operator:\t";
	for (ft::List<int>::iterator it = sixth.begin(); it != sixth.end(); it++)
		std::cout << *it << ' ';
	std::cout << '\n';
}

void list_iterators()
{
	int myints[] = {1, 2, 3, 4};
	ft::List<int> list(myints, myints + 4);

	std::cout << "iterator: ";
	for (ft::List<int>::iterator iter=list.begin(); iter != list.end(); iter++)
		std::cout << ' ' << *iter;
	std::cout << '\n';
	//begin
	std::cout << "1) begin: " << *list.begin() << std::endl;
	//end
	std::cout << "2) end: " << *--list.end() << std::endl;

	std::cout << "reverse: ";
	for (ft::List<int>::reverse_iterator rit=list.rbegin(); rit!=list.rend(); ++rit)
		std::cout << ' ' << *rit;
	std::cout << '\n';
	//rbegin
	std::cout << "3) rbegin: " << *list.rbegin() << std::endl;

	//rend
	std::cout << "4) rend: " << *--list.rend() << std::endl;
}

void list_capacity()
{
	//empty
	ft::List<int> empty;
	ft::List<int> non_empty(4);
	std::cout << "1) empty: " << empty.empty() << ", non_empty: " << non_empty.empty() << std::endl;

	//size
	std::cout << "2) size: " << non_empty.size() << std::endl;

	//max_size
	std::cout << "3) max_size: " << non_empty.max_size() << std::endl;
}

void list_element_access()
{
	ft::List<int> list;
	list.push_back(42);
	list.push_back(2);			// 42 2
	list.front() -= list.back();// 40 2
	//front
	std::cout << "1) front: " << list.front() << std::endl;
	//back
	std::cout << "2) back: " << list.back() << std::endl;

	const ft::List<int> test(list);
	//const front
	std::cout << "3) const front: " << test.front() << std::endl;
	//const back
	std::cout << "4) const back: " << test.back() << std::endl;
}

void list_modifiers()
{
	//assign
	ft::List<int> first;
	ft::List<int> second;
	int myints[]={1776,7,4};

	first.assign ((size_t)7,100);
	second.assign (first.begin(),first.end());
	std::cout << "1) Size of first: " << int (first.size()) << '\n';
	std::cout << " ) second(assign copy of first): " << int (second.size()) << '\n';

	first.assign (myints,myints+3);
	std::cout << " ) reassign first: " << int (first.size()) << '\n';


	//push_front
	ft::List<int> pf((size_t)2, 100);
	pf.push_front(200);
	pf.push_front(300);		// 300 200 100 100
	std::cout << "2) push_front:\t";
	for (ft::List<int>::iterator it=pf.begin(); it!=pf.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	//pop_front
	pf.pop_front();
	std::cout << "3) pop_front:\t";
	for (ft::List<int>::iterator it=pf.begin(); it!=pf.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	//push_back
	pf.push_back(42);
	std::cout << "4) push_back:\t";
	for (ft::List<int>::iterator it=pf.begin(); it!=pf.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	//pop_back
	pf.pop_back();
	std::cout << "5) pop_back:\t";
	for (ft::List<int>::iterator it=pf.begin(); it!=pf.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';


	//insert
	ft::List<int> insert;
	ft::List<int>::iterator it;

	for (int i=1; i<=5; ++i)
		insert.push_back(i);							// 1 2 3 4 5
	it = insert.begin();
	++it;												//*it = 2
	insert.insert (it,10);								// 1 10 2 3 4 5
	std::cout << "6) insert(10):\t ";
	for (ft::List<int>::iterator iter=insert.begin(); iter!=insert.end(); ++iter)
		std::cout << ' ' << *iter;
	std::cout << '\n';

	insert.insert (it,(size_t)2,20);					// 1 10 20 20 2 3 4 5
	--it;												//		   ^it
	std::cout << " ) insert(2, 20):";
	for (ft::List<int>::iterator iter=insert.begin(); iter!=insert.end(); ++iter)
		std::cout << ' ' << *iter;
	std::cout << '\n';

	ft::List<int> insert2((size_t)2,30);				// 30 30
	insert.insert (it,insert2.begin(),insert2.end());	// 1 10 20 30 30 20 2 3 4 5
	std::cout << " ) insert(iter): ";
	for (it=insert.begin(); it!=insert.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';


	//erase
	ft::List<int> erase;
	for(int i = 1; i < 10; ++i)
		erase.push_back(i * 10); // 10 20 30 40 50 60 70 80 90
	std::cout << "7) before erase:\t";
	for (ft::List<int>::iterator iter=erase.begin(); iter!=erase.end(); ++iter)
		std::cout << ' ' << *iter;
	std::cout << '\n';

	ft::List<int>::iterator it1, it2;
	it1 = it2 = erase.begin();
	for(int i = 0; i < 6; i++)
		it2++;					// *it2 = 70
	++it1;						// *it1 = 20
	it1 = erase.erase(it1);		// 10 30 40 50 60 70 80 90	// it1 = 30
	it2 = erase.erase(it2);		// 10 30 40 50 60 80 90		// it2 = 80
	std::cout << " ) erase 20 & 70:\t";
	for (ft::List<int>::iterator iter=erase.begin(); iter!=erase.end(); ++iter)
		std::cout << ' ' << *iter;
	std::cout << '\n';

	++it1;						// *it1 = 40
	--it2;						// *it2 = 60
	erase.erase(it1, it2);		// 10 30 60 80 90
	std::cout << " ) erase (40,60):\t";
	for (it1=erase.begin(); it1!=erase.end(); ++it1)
		std::cout << ' ' << *it1;
	std::cout << '\n';


	//swap
	ft::List<int> a ((size_t)3,100); // 100 100 100
	ft::List<int> b ((size_t)5,200);  // 200 200 200 200 200

	std::cout << "8) before swap:\t";
	for (ft::List<int>::iterator it=a.begin(); it!=a.end(); it++)
		std::cout << ' ' << *it;
	std::cout << ", ";
	for (ft::List<int>::iterator it=b.begin(); it!=b.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';

	a.swap(b);
	std::cout << " ) after swap\t";
	for (ft::List<int>::iterator it=a.begin(); it!=a.end(); it++)
		std::cout << ' ' << *it;
	std::cout << ", ";
	for (ft::List<int>::iterator it=b.begin(); it!=b.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';


	//resize
	ft::List<int> rs;
	for (int i=1; i<10; ++i)
		rs.push_back(i);	// 1 2 3 4 5 6 7 8 9

	rs.resize(5);
	std::cout << "9) resize(5):\t ";
	for (ft::List<int>::iterator it=rs.begin(); it!=rs.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	rs.resize(8,100);
	std::cout << " ) resize(8,100):";
	for (ft::List<int>::iterator it=rs.begin(); it!=rs.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	rs.resize(12);
	std::cout << " ) resize(12):\t ";
	for (ft::List<int>::iterator it=rs.begin(); it!=rs.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';


	//clear
	ft::List<int> cl;
	ft::List<int>::iterator cl_it;
	cl.push_back (100);
	cl.push_back (200);
	cl.push_back (300); // 100 200 300
	std::cout << "10) before clear:";
	for (cl_it=cl.begin(); cl_it!=cl.end(); ++cl_it)
		std::cout << ' ' << *cl_it;
	std::cout << '\n';
	cl.clear();
	cl.push_back (1101);
	cl.push_back (2202); // 1101 2202
	std::cout << "  ) after clear: ";
	for (cl_it=cl.begin(); cl_it!=cl.end(); ++cl_it)
		std::cout << ' ' << *cl_it;
	std::cout << '\n';
}

// test for remove_if
bool single_digit (const int& value)
{
	return (value<10);
}
struct is_odd
{
	bool operator() (const int& value)
	{
		return (value%2)==1;
	}
};

// test for unique
bool same_integral_part (double first, double second)
{
	return ( int(first)==int(second) );
}
struct is_near {
	bool operator() (double first, double second)
	{
		if (first > second)
			return (first-second < 5.0);
		else
			return (second - first < 5.0);
	}
};

// test for merge
bool mycomparison (double first, double second)
{
	return ( int(first)<int(second) );
}

//test for sort
bool compare_nocase (const std::string& first, const std::string& second)
{
	unsigned int i=0;
	while ( (i<first.length()) && (i<second.length()) )
	{
		if (std::tolower(first[i]) < std::tolower(second[i]))
			return true;
		else if (std::tolower(first[i]) > std::tolower(second[i]))
			return false;
		++i;
	}
	return ( first.length() < second.length() );
}

void list_operations()
{
	//splice
	ft::List<int> sp1, sp2;
	ft::List<int>::iterator it;
	for (int i=1; i<=4; ++i)
		sp1.push_back(i);		// sp1: 1 2 3 4
	for (int i=1; i<=3; ++i)
		sp2.push_back(i*10);	// sp2: 10 20 30
	it = sp1.begin();
	++it;						// *it = 2
	sp1.splice (it, sp2); 		// sp1: 1 10 20 30 2 3 4
								// sp2: (empty)
	std::cout << "1) sp1: ";
	for (ft::List<int>::iterator iter=sp1.begin(); iter!=sp1.end(); ++iter)
		std::cout << ' ' << *iter;
	std::cout << "\t,sp2: ";
	for (ft::List<int>::iterator iter=sp2.begin(); iter!=sp2.end(); ++iter)
		std::cout << ' ' << *iter;
	std::cout << std::endl;

	sp2.splice (sp2.begin(),sp1, it);	// sp1: 1 10 20 30 3 4
										// sp2: 2
										// "it" is now invalid.
	std::cout << " ) sp1: ";
	for (ft::List<int>::iterator iter=sp1.begin(); iter!=sp1.end(); ++iter)
		std::cout << ' ' << *iter;
	std::cout << " \t,sp2: ";
	for (ft::List<int>::iterator iter=sp2.begin(); iter!=sp2.end(); ++iter)
		std::cout << ' ' << *iter;
	std::cout << std::endl;

	it = sp1.begin();
	it++; it++; it++;								//it = 30
	sp1.splice ( sp1.begin(), sp1, it, sp1.end());	// sp1: 30 3 4 1 10 20
	std::cout << " ) sp1: ";
	for (ft::List<int>::iterator iter=sp1.begin(); iter!=sp1.end(); ++iter)
		std::cout << ' ' << *iter;
	std::cout << " \t,sp2: ";
	for (ft::List<int>::iterator iter=sp2.begin(); iter!=sp2.end(); ++iter)
		std::cout << ' ' << *iter;
	std::cout << std::endl;


	//remove
	int myints[]= {1,2,3,2,5,2};
	ft::List<int> mylist (myints,myints+6);
	std::cout << "2) before remove:  ";
	for (ft::List<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	mylist.remove(2);
	std::cout << " ) after remove(2):";
	for (ft::List<int>::iterator it=mylist.begin(); it!=mylist.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';


	//remove_if
	int myints2[]= {15,36,7,17,20,39,4,1};
	ft::List<int> rmif (myints2,myints2+8);	// 15 36 7 17 20 39 4 1
	std::cout << "3) before remove_if:\t\t";
	for (ft::List<int>::iterator it=rmif.begin(); it!=rmif.end(); ++it)
	  std::cout << ' ' << *it;
	std::cout << '\n';
	rmif.remove_if (single_digit);			// 15 36 17 20 39
	std::cout << " ) single_digit remove_if:\t";
	for (ft::List<int>::iterator it=rmif.begin(); it!=rmif.end(); ++it)
	  std::cout << ' ' << *it;
	std::cout << '\n';
	rmif.remove_if (is_odd());				// 36 20
	std::cout << " ) is_odd remove_if:\t\t";
	for (ft::List<int>::iterator it=rmif.begin(); it!=rmif.end(); ++it)
	  std::cout << ' ' << *it;
	std::cout << '\n';


	//unique
	double mydoubles[]={12.15, 2.72, 73.0, 12.77, 3.14,
						12.77, 73.35, 72.25, 15.3, 72.25 };
	ft::List<double> uq (mydoubles,mydoubles+10);
	uq.sort();		// 2.72, 3.14, 12.15, 12.77, 12.77, 15.3, 72.25, 72.25, 73.0, 73.35
	std::cout << "4) before unique: ";
	for (ft::List<double>::iterator it=uq.begin(); it!=uq.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	uq.unique();	// 2.72, 3.14, 12.15, 12.77 15.3, 72.25, 73.0, 73.35
	std::cout << " ) unique():      ";
	for (ft::List<double>::iterator it=uq.begin(); it!=uq.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	uq.unique (same_integral_part);	// 2.72, 3.14, 12.15 15.3, 72.25, 73.0
	std::cout << " ) unique(same_integral_part):";
	for (ft::List<double>::iterator it=uq.begin(); it!=uq.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	uq.unique (is_near());			//  2.72, 12.15, 72.25
	std::cout << " ) unique(is_near()):";
	for (ft::List<double>::iterator it=uq.begin(); it!=uq.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';


	//merge
	ft::List<double> first, second;

	first.push_back (3.1);	// first: 3.1 2.2 2.9
	first.push_back (2.2);
	first.push_back (2.9);
	second.push_back (3.7);	// second: 3.7 7.1 1.4
	second.push_back (7.1);
	second.push_back (1.4);
	first.sort();			// first: 2.2 2.9 3.1
	second.sort();			// second: 1.4 3.7 7.1
	first.merge(second);	// first: 1.4 2.2 2.9 3.1 3.7 7.1 (second is now empty)
	std::cout << "5) [3.1 2.2 2.9] + [3.7 7.1 1.4]:";
	for (ft::List<double>::iterator it=first.begin(); it!=first.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	second.push_back (2.1);	// second: 2.1
	first.merge(second,mycomparison); //first: 1.4 2.2 2.9 2.1 3.1 3.7 7.1
	std::cout << " ) first merge + [2.1]:";
	for (ft::List<double>::iterator it=first.begin(); it!=first.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';


	//sort
	ft::List<std::string> s;
	s.push_back ("one");
	s.push_back ("two");
	s.push_back ("Three");
	s.sort();
	std::cout << "6) sort:";
	for (ft::List<std::string>::iterator it_s=s.begin(); it_s!=s.end(); ++it_s)
		std::cout << ' ' << *it_s;
	std::cout << '\n';
	s.sort(compare_nocase);
	std::cout << " ) sort(compare_nocase):";
	for (ft::List<std::string>::iterator it_s=s.begin(); it_s!=s.end(); ++it_s)
		std::cout << ' ' << *it_s;
	std::cout << '\n';


	//reverse
	ft::List<int> rvs;
	for (int i=1; i<10; ++i) rvs.push_back(i);
	rvs.reverse();
	std::cout << "7) reverse: ";
	for (ft::List<int>::iterator it=rvs.begin(); it!=rvs.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void list_non_member()
{
	//relational operations
	int a_int[] = {10, 20, 30};
	int b_int[] = {10, 20, 30};
	int c_int[] = {30, 20, 10};
	ft::List<int> a(a_int, a_int + 3);
	ft::List<int> b(b_int, b_int + 3);
	ft::List<int> c(c_int, c_int + 3);
	std::cout << "a:";
	for(ft::List<int>::iterator iter = a.begin(); iter != a.end(); iter++)
		std::cout << " " << *iter;
	std::cout << " | b:";
	for(ft::List<int>::iterator iter = b.begin(); iter != b.end(); iter++)
		std::cout << " " << *iter;
	std::cout << " | c:";
	for(ft::List<int>::iterator iter = c.begin(); iter != c.end(); iter++)
		std::cout << " " << *iter;
	std::cout << std::endl;
	if (a==b) std::cout << "1) a==b: a and b are equal\n";
	if (b!=c) std::cout << "2) b!=c: b and c are not equal\n";
	if (b<c) std::cout << "3) b<c: b is less than c\n";
	if (c>b) std::cout << "4) c>b: c is greater than b\n";
	if (a<=b) std::cout << "5) a<=b: a is less than or equal to b\n";
	if (a>=b) std::cout << "6) a>=b: a is greater than or equal to b\n";

	std::cout << std::endl;
	//swap
	ft::List<int> foo ((size_t)3,100);
	ft::List<int> bar ((size_t)5,200);
	std::cout << "swap) ";
	for (ft::List<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
	  std::cout << ' ' << *it;
	std::cout << ", ";
	for (ft::List<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
	  std::cout << ' ' << *it;
	std::cout << '\n';
	ft::swap(foo,bar);
	std::cout << "    ) ";
	for (ft::List<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
	  std::cout << ' ' << *it;
	std::cout << ", ";
	for (ft::List<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
	  std::cout << ' ' << *it;
	std::cout << '\n';
}

void test_list()
{
	std::cout << "-------list_constructor---------" << std::endl;
	list_constructor();

	std::cout << std::endl << "-------list_iterators---------" << std::endl;
	list_iterators();

	std::cout << std::endl << "-------list_capacity---------" << std::endl;
	list_capacity();

	std::cout << std::endl << "-------list_element_access---------" << std::endl;
	list_element_access();

	std::cout << std::endl << "-------list_modifiers---------" << std::endl;
	list_modifiers();

	std::cout << std::endl << "-------list_operations---------" << std::endl;
	list_operations();

	std::cout << std::endl << "-------list_non_member---------" << std::endl;
	list_non_member();
}