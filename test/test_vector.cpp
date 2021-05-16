#include "main.hpp"

void vec_constructor()
{
	ft::Vector<int> default_const;
	std::cout << "1) default constructor size: " << default_const.size() << std::endl;

	ft::Vector<int> fill_const ((size_t)4,100);
	std::cout << "2) constructor(4, 100): ";
	for (ft::Vector<int>::iterator it = fill_const.begin(); it != fill_const.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;

	ft::Vector<int> range_const (fill_const.begin(),fill_const.end());
	std::cout << "3) range constructor: ";
	for (ft::Vector<int>::iterator it = range_const.begin(); it != range_const.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;

	int arr[] = {1,2,3,4};
	ft::Vector<int> range_const2 (arr, arr + sizeof(arr) / sizeof(int) );
	std::cout << " ) range_const2(arr, arr+4): ";
	for (ft::Vector<int>::iterator it = range_const2.begin(); it != range_const2.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	ft::Vector<int> copy_const (range_const2);
	std::cout << "4) copy constructor: ";
	for (ft::Vector<int>::iterator it = copy_const.begin(); it != copy_const.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;


	//=operator
	ft::Vector<int> op1 ((size_t)3,0);
	ft::Vector<int> op2 ((size_t)5,0);
	std::cout << "5) op1: ";
	for (ft::Vector<int>::iterator it = op1.begin(); it != op1.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << ", op2: ";
	for (ft::Vector<int>::iterator it = op2.begin(); it != op2.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;

	op2 = op1;
	std::cout << " ) op2=op1: op2 size = " << int(op2.size()) << '\n';
	op1 = ft::Vector<int>();
	std::cout << " ) op1 = ft::Vector<int>(): op1 size = " << int(op1.size()) << '\n';
}

void vec_iterators()
{
	//begin
	ft::Vector<int> bg;
	for (int i=1; i<=5; i++)
		bg.push_back(i);	// 1 2 3 4 5
	std::cout << "1) 1 2 3 4 5 begin: " << *bg.begin() << std::endl;

	//end
	std::cout << " ) 1 2 3 4 5 end: " << *--bg.end() << std::endl;

	//rbegin
	std::cout << " ) 1 2 3 4 5 rbegin: " << *bg.rbegin() << std::endl;

	//rend
	std::cout << " ) 1 2 3 4 5 rend: " << *--bg.rend() << std::endl;

}

void vec_capacity()
{
	//size
	ft::Vector<int> sz;
	std::cout << "1) size 0: " << sz.size() << '\n';
	for (int i=0; i<10; i++)
		sz.push_back(i);
	std::cout << " ) size 10: " << sz.size() << '\n';
	sz.insert (sz.end(),(size_t)10,100);
	std::cout << " ) size 20: " << sz.size() << '\n';
	sz.pop_back();
	std::cout << " ) size 19: " << sz.size() << '\n';

	//max_size
	ft::Vector<int> max;
	for (int i=0; i<100; i++)
		max.push_back(i);
	std::cout << "2) max_size: " << max.max_size() << "\n";

	//resize
	ft::Vector<int> rs;
	for (int i=1;i<10;i++)
		rs.push_back(i);
	std::cout << "3) arr:";
	for (int i=0;i<rs.size();i++)
		std::cout << ' ' << rs[i];
	std::cout << '\n';
	rs.resize(5);
	std::cout << " ) resize(5): ";
	for (int i=0;i<rs.size();i++)
		std::cout << ' ' << rs[i];
	std::cout << '\n';
	rs.resize((size_t)8,100);
	std::cout << " ) resize(8, 100): ";
	for (int i=0;i<rs.size();i++)
		std::cout << ' ' << rs[i];
	std::cout << '\n';
	rs.resize(12);
	std::cout << " ) resize(12): ";
	for (int i=0;i<rs.size();i++)
		std::cout << ' ' << rs[i];
	std::cout << '\n';


	//capacity
	std::cout << "4) capacity 128: " << max.capacity() << '\n';

	//empty
	ft::Vector<int> empt;
	std::cout << "5) empty 1: " << empt.empty() << '\n';
	empt.push_back(1);
	std::cout << " ) empty 0: " << empt.empty() << '\n';

	//reserve
	ft::Vector<int>::size_type s_type;
	ft::Vector<int> rsv1;
	s_type = rsv1.capacity();
	std::cout << "6) reserve test1\n";
	for (int i=0; i<100; ++i) {
		rsv1.push_back(i);
		if (s_type!=rsv1.capacity()) {
			s_type = rsv1.capacity();
			std::cout << " ) capacity changed: " << s_type << '\n';
		}
	}
	ft::Vector<int> rsv2;
	s_type = rsv2.capacity();
	rsv2.reserve(100);   // this is the only difference with rsv1 above
	std::cout << " ) reserv test2\n";
	for (int i=0; i<100; ++i) {
		rsv2.push_back(i);
		if (s_type!=rsv2.capacity()) {
			s_type = rsv2.capacity();
			std::cout << " ) capacity changed: " << s_type << '\n';
		}
	}
}

void vec_element_access()
{
	//[]operator
	ft::Vector<int> op (10);
	ft::Vector<int>::size_type sz = op.size();
	for (unsigned i=0; i<sz; i++)
		op[i]=i;	// 0 1 2 3 4 5 6 7 8 9
	for (unsigned i=0; i<sz/2; i++)
	{	//swap
		int temp;
		temp = op[sz-1-i];
		op[sz-1-i]=op[i];
		op[i]=temp;
	}
	std::cout << "1) [] operator test:";
	for (unsigned i=0; i<sz; i++)
		std::cout << ' ' << op[i];
	std::cout << '\n';

	//at
	ft::Vector<int> at (10);
	for (unsigned i=0; i<at.size(); i++)
		at.at(i)=i;	// 0 1 2 3 4 5 6 7 8 9
	std::cout << "2) at:";
	for (unsigned i=0; i<at.size(); i++)
		std::cout << ' ' << at.at(i);
	std::cout << '\n';

	//front
	ft::Vector<int> frt;
	frt.push_back(78);
	frt.push_back(16);	// frt : 78 16
	frt.front() -= frt.back();
	std::cout << "3) front() is now " << frt.front() << '\n';

	//back
	std::cout << "4) back: " << frt.back() << '\n';
}

void vec_modifiers()
{
	//assign
	ft::Vector<int> ass1;
	ft::Vector<int> ass2;
	ft::Vector<int> ass3;
	ass1.assign ((size_t)7,100);	// ass1: 100 100 100 100 100 100 100
	std::cout << "1) Size of assign1: " << int (ass1.size()) << '\n';

	ft::Vector<int>::iterator it;
	it=ass1.begin()+1;
	ass2.assign (it,ass1.end()-1);	// ass2: 100 100 100 100 100
	std::cout << " ) Size of assign2: " << int (ass2.size()) << '\n';

	int myints[] = {1776,7,4};
	ass3.assign (myints,myints+3);	// ass3: 1776 7 4
	std::cout << " ) Size of assign3: " << int (ass3.size()) << '\n';


	//push_back
	ft::Vector<int> pb;
	pb.push_back(1);
	pb.push_back(2);
	std::cout << "2) puch_back 1,2: ";
	for (ft::Vector<int>::iterator iter=pb.begin(); iter<pb.end(); iter++)
		std::cout << ' ' << *iter;
	std::cout << '\n';

	//pop_back
	pb.pop_back();
	std::cout << "3) pop_back: ";
	for (ft::Vector<int>::iterator iter=pb.begin(); iter<pb.end(); iter++)
		std::cout << ' ' << *iter;
	std::cout << '\n';


	//insert
	ft::Vector<int> in((size_t)3,100);				// in: 100 100 100
	ft::Vector<int>::iterator iter = in.begin();	//		^iter
	iter = in.insert( iter , 200 );					// in: 200 100 100 100
	std::cout << "4) insert(begin, 200):";			//		^iter
	for (ft::Vector<int>::iterator it=in.begin(); it<in.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';


	in.insert (iter,(size_t)2,300);					// in: 300 300 200 100 100 100
	std::cout << " ) insert(begin, 2, 300):";
	for (ft::Vector<int>::iterator it=in.begin(); it<in.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';


	iter = in.begin();
	ft::Vector<int> in2 ((size_t)2,400);			// in2: 400 400
	in.insert (iter+2,in2.begin(),in2.end());		// in: 300 300 400 400 200 100 100 100
	std::cout << " ) insert(begin+2, [400, 400]):";
	for (ft::Vector<int>::iterator it=in.begin(); it<in.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';

	int myarray [] = { 501,502,503 };
	in.insert (in.begin(), myarray, myarray+3);		// in: 501 502 503 300 300 400 400 200 100 100 100
	std::cout << " ) insert(begin, [501, 502, 503]):";
	for (ft::Vector<int>::iterator it=in.begin(); it<in.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';


	//erase
	ft::Vector<int> ers;
	for (int i=1; i<=10; i++)
		ers.push_back(i);					// 1 2 3 4 5 6 7 8 9 10
	ers.erase (ers.begin()+5);				// 1 2 3 4 5 7 8 9 10
	ers.erase (ers.begin(),ers.begin()+3);	// 4 5 7 8 9 10
	std::cout << "5) erase:";
	for (unsigned i=0; i<ers.size(); ++i)
	  std::cout << ' ' << ers[i];
	std::cout << '\n';

	//swap
	ft::Vector<int> sw1 ((size_t)3,100);	// sw1: 100 100 100
	ft::Vector<int> sw2 ((size_t)5,200);	// sw2: 200 200 200 200 200
	sw1.swap(sw2);
	std::cout << "6) swap([100 100 100][200 200 200 200 200])\n";
	std::cout << " ) [";
	for (unsigned i=0; i<sw1.size(); i++)
	  std::cout << ' ' << sw1[i];
	std::cout << " ][";
	for (unsigned i=0; i<sw2.size(); i++)
	  std::cout << ' ' << sw2[i];
	std::cout << " ]\n";

	//clear
	ft::Vector<int> cl;
	cl.push_back (100);
	cl.push_back (200);
	cl.push_back (300);
	cl.clear();
	std::cout << "7) clear size: " << cl.size() << std::endl;


}

void vec_non_member()
{
	//relational operations
	ft::Vector<int> op1 ((size_t)3,100); // 100 100 100
	ft::Vector<int> op2 ((size_t)2,200); // 200 200
	std::cout << "op1:";
	for (unsigned i=0; i<op1.size(); i++)
		std::cout << ' ' << op1[i];
	std::cout << ", op2:";
	for (unsigned i=0; i<op2.size(); i++)
		std::cout << ' ' << op2[i];
	std::cout << " \n";
	if (op1==op2) std::cout << "1) op1==op2\n";
	if (op1!=op2) std::cout << "2) op1!=op2\n";
	if (op1< op2) std::cout << "3) op1< op2\n";
	if (op1> op2) std::cout << "4) op1> op2\n";
	if (op1<=op2) std::cout << "5) op1<=op2\n";
	if (op1>=op2) std::cout << "6) op1>=op2\n";

	//swap
	unsigned int i;
	ft::Vector<int> sw1 ((size_t)3,100);
	ft::Vector<int> sw2 ((size_t)5,200);
	std::cout << "swap) ";
	for (ft::Vector<int>::iterator it = sw1.begin(); it!=sw1.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << ", ";
	for (ft::Vector<int>::iterator it = sw2.begin(); it!=sw2.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	ft::swap(sw1, sw2);
	std::cout << "    ) ";
	for (ft::Vector<int>::iterator it = sw1.begin(); it!=sw1.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << ", ";
	for (ft::Vector<int>::iterator it = sw2.begin(); it!=sw2.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void test_vector()
{
	std::cout << "-------------vec_constructor---------------" << std::endl;
	vec_constructor();
	std::cout << "\n-------------vec_iterators---------------" << std::endl;
	vec_iterators();
	std::cout << "\n-------------vec_capacity---------------" << std::endl;
	vec_capacity();
	std::cout << "\n-------------vec_element_access---------------" << std::endl;
	vec_element_access();
	std::cout << "\n-------------vec_modifiers---------------" << std::endl;
	vec_modifiers();
	std::cout << "\n-------------vec_non_member---------------" << std::endl;
	vec_non_member();
}