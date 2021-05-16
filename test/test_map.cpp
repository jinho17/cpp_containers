#include "main.hpp"

// constructor test
bool fncomp (char lhs, char rhs)
{
	return lhs>rhs;
}
struct classcomp {
	bool operator() (const char& lhs, const char& rhs) const
	{
		return lhs>rhs;
	}
};

void map_constructor()
{
	ft::Map<char,int> cons;
	std::cout << "1) default consructor size: " << cons.size() << std::endl;

	cons['a']=10;
	cons['b']=30;
	cons['c']=50;
	cons['d']=70;
	ft::Map<char,int> range_cons (cons.begin(),cons.end());
	std::cout << "2) range constructor: ";
	for(ft::Map<char, int>::iterator iter = range_cons.begin(); iter != range_cons.end(); iter++)
		std::cout << " " << iter->first;
	std::cout << std::endl;

	ft::Map<char,int> copy_cons (range_cons);
	std::cout << "3) copy constructor: ";
	for(ft::Map<char, int>::iterator iter = range_cons.begin(); iter != range_cons.end(); iter++)
		std::cout << " " << iter->first;
	std::cout << std::endl;

	ft::Map<char,int,classcomp> cmp_cons;
	cmp_cons['a']=10;
	cmp_cons['b']=30;
	cmp_cons['c']=50;
	cmp_cons['d']=70;
	std::cout << "4) class as Compare: ";
	for(ft::Map<char, int>::iterator iter = cmp_cons.begin(); iter != cmp_cons.end(); iter++)
		std::cout << " " << iter->first;
	std::cout << std::endl;

	bool(*fn_pt)(char,char) = fncomp;
	ft::Map<char,int,bool(*)(char,char)> fp_cmp_cons (fn_pt);
	fp_cmp_cons['a']=10;
	fp_cmp_cons['b']=30;
	fp_cmp_cons['c']=50;
	fp_cmp_cons['d']=70;
	std::cout << "5) function pointer as Compare: ";
	for(ft::Map<char, int>::iterator iter = fp_cmp_cons.begin(); iter != fp_cmp_cons.end(); iter++)
		std::cout << " " << iter->first;
	std::cout << std::endl;


	//= operator
	ft::Map<char,int> op1;
	ft::Map<char,int> op2;
	op1['x']=8;
	op1['y']=16;
	op1['z']=32;
	op2=op1;
	std::cout << "6) op2=op1:\top1 size:" <<op1.size();
	std::cout << ", op2.size: " <<op2.size() << std::endl;
	op1=ft::Map<char,int>();
	std::cout << " ) op1=ft::Map<char,int>() size: " << op1.size() << '\n';
}

void map_iterators()
{
	//begin, end
	ft::Map<char,int> bg;
	bg['b'] = 100;
	bg['a'] = 200;
	bg['c'] = 300;
	std::cout << "1) begin, end test: ";
	for (ft::Map<char,int>::iterator it=bg.begin(); it!=bg.end(); ++it)
		std::cout << it->first << ":" << it->second << " ";
	std::cout << std::endl;

	//rbegin, rend
	ft::Map<char,int>::reverse_iterator rit;
	std::cout << "2) rbegin, rend test: ";
	for (rit=bg.rbegin(); rit!=bg.rend(); ++rit)
		std::cout << rit->first << ":" << rit->second << ' ';
	std::cout << std::endl;

	//empty, size
	ft::Map<char,int> emp;
	std::cout << "3) is empty true: " << emp.empty() << "(size:" << emp.size() << ")";

	emp['a']=10;
	emp['b']=20;
	emp['c']=30;
	std::cout << ", false: " << emp.empty() << "(size:" << emp.size() << ")" << std::endl;

	//max size
	int i;
	ft::Map<int,int> max;
	std::cout << "4) max_size test: ";
	if (max.max_size()>1000)
	{
		for (i=0; i<1000; i++) max[i]=0;
		std::cout << "The map contains 1000 elements.\n";
	}
	else std::cout << "The map could not hold 1000 elements.\n";
}

void map_element_access()
{
	// [] operator
	ft::Map<char,std::string> op;
	op['a']="an element";
	op['b']="another element";
	op['c']=op['b'];
	std::cout << "1) op['a']: " << op['a'] << '\n';
	std::cout << " ) op['b']: " << op['b'] << '\n';
	std::cout << " ) op['c']: " << op['c'] << '\n';
	std::cout << " ) op['d']: " << op['d'] << '\n';
	std::cout << " ) op.size(): " << op.size() << "\n";

}

void map_modifiers()
{
	//insert
	ft::Map<int, int> in;
	in.insert(std::make_pair(3, 3));
	in.insert(std::make_pair(5, 5));
	in.insert(std::make_pair(6, 6));
	in.insert(std::make_pair(11, 11));
	in.insert(std::make_pair(12, 12));
	in.insert(std::make_pair(20, 20));
	in.insert(std::make_pair(15, 15));
	in.insert(std::make_pair(40, 40));
	in.insert(std::make_pair(25, 25));

	std::cout << "1) insert :";
	for(ft::Map<int, int>::iterator iter = in.begin(); iter != in.end(); iter++)
		std::cout << " " << (*iter).first;
	std::cout << std::endl;
/*
	in.insert(std::make_pair(20, 20));
	in.insert(std::make_pair(15, 15));
	in.insert(std::make_pair(3, 3));
	in.insert(std::make_pair(12, 12));
	in.insert(std::make_pair(5, 5));
	in.insert(std::make_pair(11, 11));
	in.insert(std::make_pair(6, 6));
	in.insert(std::make_pair(40, 40));
	in.insert(std::make_pair(25, 25));
	in.insert(std::make_pair(18, 18));

	std::cout << "final :";
	for(ft::Map<int, int>::iterator iter = in.begin(); iter != in.end(); iter++)
		std::cout << " " << (*iter).first;
	std::cout << std::endl;

	in.erase(40);
	//in.erase(3);
	std::cout << "final :";
	for(ft::Map<int, int>::iterator iter = in.begin(); iter != in.end(); iter++)
		std::cout << " " << (*iter).first;
	std::cout << std::endl << std::endl;
*/

	ft::Map<char,int> in2;
	in2.insert ( std::pair<char,int>('a',100) );
	in2.insert ( std::pair<char,int>('z',200) );

	std::pair<ft::Map<char,int>::iterator,bool> ret;
	ret = in2.insert ( std::pair<char,int>('z',500) );
	if (ret.second==false) {
		std::cout << " ) insert failed! element 'z' already existed with a value of " << ret.first->second << '\n';
	}

	ft::Map<char,int>::iterator it = in2.begin();
	in2.insert (it, std::pair<char,int>('b',300));
	in2.insert (it, std::pair<char,int>('c',400));
	std::cout << " ) in2 contains:\t";
	for (it=in2.begin(); it!=in2.end(); ++it)
		std::cout << it->first << ":" << it->second << ' ';
	std::cout << std::endl;

	ft::Map<char,int> anothermap;
	anothermap.insert(in2.begin(),in2.find('c'));
	std::cout << " ) insert(in2.begin, in2.find(c)):\t";
	for (it=anothermap.begin(); it!=anothermap.end(); ++it)
		std::cout << it->first << ":" << it->second << ' ';
	std::cout << std::endl;



	//erase
	ft::Map<char,int> ers;
	ft::Map<char,int>::iterator it_ers;
	ers['a']=10;
	ers['b']=20;
	ers['c']=30;
	ers['d']=40;
	ers['e']=50;
	ers['f']=60;			// ers: 10 20 30 40 50 60

	it_ers=ers.find('b');
	ers.erase (it_ers);		// ers: 10 30 40 50 60
	ers.erase ('c');		// ers: 10 40 50 60
	it_ers=ers.find ('e');
	ers.erase ( it_ers, ers.end() ); // ers: 10 40

	std::cout << "2) erase result: ";
	for (it_ers=ers.begin(); it_ers!=ers.end(); ++it_ers)
	std::cout << it_ers->first << ":" << it_ers->second << ' ';
	std::cout << std::endl;


	//swap
	ft::Map<char,int> sw1,sw2;

	sw1['x']=100;
	sw1['y']=200;
	sw2['a']=11;
	sw2['b']=22;
	sw2['c']=33;
	std::cout << "3) befor swap:\tsw1: ";
	for (ft::Map<char,int>::iterator it=sw1.begin(); it!=sw1.end(); ++it)
		std::cout << it->first << ":" << it->second << ' ';
	std::cout << "\tsw2: ";
	for (ft::Map<char,int>::iterator it=sw2.begin(); it!=sw2.end(); ++it)
		std::cout << it->first << ":" << it->second << ' ';
	std::cout << std::endl;

	sw1.swap(sw2);
	std::cout << " ) after swap:\tsw1: ";
	for (ft::Map<char,int>::iterator it=sw1.begin(); it!=sw1.end(); ++it)
		std::cout << it->first << ":" << it->second << ' ';
	std::cout << "\tsw2: ";
	for (ft::Map<char,int>::iterator it=sw2.begin(); it!=sw2.end(); ++it)
		std::cout << it->first << ":" << it->second << ' ';
	std::cout << std::endl;


	//clear
	ft::Map<char,int> cl;

	cl['x']=100;
	cl['y']=200;
	cl['z']=300;
	std::cout << "4) bef clear: ";
	for (ft::Map<char,int>::iterator it=cl.begin(); it!=cl.end(); ++it)
		std::cout << it->first << ":" << it->second << ' ';
	std::cout << std::endl;

	cl.clear();
	cl['a']=1101;
	cl['b']=2202;
	std::cout << " ) aft clear: ";
	for (ft::Map<char,int>::iterator it=cl.begin(); it!=cl.end(); ++it)
		std::cout << it->first << ":" << it->second << ' ';
	std::cout << std::endl;

}

void map_observers()
{
	//key comp
	ft::Map<char,int> key_c;
	ft::Map<char,int>::key_compare mycomp = key_c.key_comp();
	key_c['a']=100;
	key_c['b']=200;
	key_c['c']=300;
	char highest = key_c.rbegin()->first;	//highest = c

	std::cout << "1) key_comp: ";
	ft::Map<char,int>::iterator it = key_c.begin();
	do {
		std::cout << it->first << ":" << it->second << ' ';
	} while ( mycomp((*it++).first, highest) );
	std::cout << '\n';
	std::cout << " ) c < a ? result: " << mycomp(highest, 'a') << std::endl;


	//val_comp
	ft::Map<char,int> val_c;
	val_c['x']=1001;
	val_c['y']=2002;
	val_c['z']=3003;
	std::pair<char,int> highest2 = *val_c.rbegin();	//highest = (z, 3003)
	ft::Map<char,int>::iterator it2 = val_c.begin();
	std::cout << "2) value contains: ";
	do {
		std::cout << it2->first << ":" << it2->second << ' ';
	} while ( val_c.value_comp()(*it2++, highest2) );
	std::cout << '\n';
	ft::Map<char, int>::value_compare mycomp2 = val_c.value_comp();
	std::cout << " ) 5 < 7 ? result: " << mycomp2(std::make_pair<int, int>(5, 9), std::make_pair<int, int>(7, 1)) << std::endl;
}

void map_operations()
{
	//find
	ft::Map<char,int> find1;
	ft::Map<char,int>::iterator it;
	find1['a']=50;
	find1['b']=100;
	find1['c']=150;
	find1['d']=200;
	it = find1.find('b');
	if (it != find1.end())
		find1.erase (it);
	std::cout << "1) find: ";
	std::cout << "a:" << find1.find('a')->second << ' ';
	std::cout << "c:" << find1.find('c')->second << ' ';
	std::cout << "d:" << find1.find('d')->second << '\n';


	//count
	ft::Map<char,int> cnt;
	char c;
	cnt ['a']=101;
	cnt ['c']=202;
	cnt ['f']=303;
	std::cout << "2) count: ";
	for (c='a'; c<'h'; c++)
		std::cout << " " << c << ":" << cnt.count(c);
	std::cout << std::endl;


	//lower_bound
	ft::Map<char,int> lb;
	ft::Map<char,int>::iterator itlow,itup;
	lb['a']=20;
	lb['b']=40;
	lb['c']=60;
	lb['d']=80;
	lb['e']=100;
	itlow=lb.lower_bound ('b');
	std::cout << "3) lower_bound: " << (*itlow).first << std::endl;
	itup=lb.upper_bound ('d');
	std::cout << "4) upper_bound: " << (*itup).first << std::endl;
	lb.erase(itlow,itup);
	std::cout << " ) ";
	for (ft::Map<char,int>::iterator it=lb.begin(); it!=lb.end(); ++it)
		std::cout << it->first << ":" << it->second << ' ';
	std::cout << std::endl;

	//equal_range
	ft::Map<char,int> eq_b;
	eq_b['a']=10;
	eq_b['b']=20;
	eq_b['c']=30;
	std::pair<ft::Map<char,int>::iterator,ft::Map<char,int>::iterator> ret;
	ret = eq_b.equal_range('b');
	std::cout << "5) equal range(lower: ";
	std::cout << ret.first->first << ":" << ret.first->second << ' ';
	std::cout << ", upper: ";
	std::cout << ret.second->first << ":" << ret.second->second << ' ';
	std::cout << ")" << std::endl;

}

void test_map()
{
	std::cout << "-------------map_constructor---------------" << std::endl;
	map_constructor();
	std::cout << "\n-------------map_iterators---------------" << std::endl;
	map_iterators();
	std::cout << "\n-------------map_element_access---------------" << std::endl;
	map_element_access();
	std::cout << "\n-------------map_modifiers---------------" << std::endl;
	map_modifiers();
	std::cout << "\n-------------map_observers---------------" << std::endl;
	map_observers();
	std::cout << "\n-------------map_operations---------------" << std::endl;
	map_operations();
}