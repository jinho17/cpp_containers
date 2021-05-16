#include "main.hpp"

void stack_constructor()
{
	ft::Vector<int> v1 ((size_t)3,100);
	ft::Stack<int> s1;
	std::cout << "1) default constructor: " << s1.size() << '\n';
	ft::Stack<int> s2(v1);
	std::cout << " ) s2(v1): " << s2.size() << '\n';

	ft::Stack<int> s4(s2);
	std::cout << "2) copy constructor: " << s2.size() << '\n';

	ft::Stack<int,ft::Vector<int> > s3;
	s3 = s2;
	std::cout << "3) = operator: " << s3.size() << '\n';
}

void stack_mem_func()
{
	//empty
	ft::Stack<int> emp;
	int sum (0);
	for (int i=1;i<=10;i++)
		emp.push(i);	// 1 2 3 4 5 6 7 8 9 10
	while (!emp.empty())
	{
		sum += emp.top();
		emp.pop();
	}
	std::cout << "1) empty test: " << sum << '\n';

	//size
	ft::Stack<int> sz;
	std::cout << "2) size 0: " << sz.size() << '\n';
	for (int i=0; i<5; i++)
		sz.push(i);
	std::cout << " ) size 5: " << sz.size() << '\n';
	sz.pop();
	std::cout << " ) size 4: " << sz.size() << '\n';

	//top
	ft::Stack<int> tp;
	tp.push(10);
	tp.push(20);	//top = 20
	tp.top() -= 5;	//top = 15
	std::cout << "3) top: " << tp.top() << '\n';

	//push, pop
	ft::Stack<int> psh;
	for (int i=0; i<5; ++i)
		psh.push(i);
	std::cout << "4) push: ";
	while (!psh.empty())
	{
		std::cout << ' ' << psh.top();
		psh.pop();
	}
	std::cout << '\n';
	std::cout << "5) after pop: size: " << psh.size() << std::endl;

}

void stack_non_mem()
{
	//relational operations
	ft::Vector<int> op1 ((size_t)3,100); // 100 100 100
	ft::Vector<int> op2 ((size_t)2,200); // 200 200
	ft::Stack<int> s1(op1);
	ft::Stack<int> s2(op2);
	std::cout << "op1:";
	for (unsigned i=0; i<op1.size(); i++)
		std::cout << ' ' << op1[i];
	std::cout << ", op2:";
	for (unsigned i=0; i<op2.size(); i++)
		std::cout << ' ' << op2[i];
	std::cout << " \n";
	if (s1==s2) std::cout << "1) s1==s2\n";
	if (s1!=s2) std::cout << "2) s1!=s2\n";
	if (s1< s2) std::cout << "3) s1< s2\n";
	if (s1> s2) std::cout << "4) s1> s2\n";
	if (s1<=s2) std::cout << "5) s1<=s2\n";
	if (s1>=s2) std::cout << "6) s1>=s2\n";

	//swap
	unsigned int i;
	ft::Vector<int> sw1 ((size_t)3,100);
	ft::Vector<int> sw2 ((size_t)5,200);
	ft::Stack<int> sw_s1(sw1);
	ft::Stack<int> sw_s2(sw2);
	std::cout << "swap) ";
	for (ft::Vector<int>::iterator it = sw1.begin(); it!=sw1.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << ", ";
	for (ft::Vector<int>::iterator it = sw2.begin(); it!=sw2.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	ft::swap(sw_s1, sw_s2);
	std::cout << "    ) ";
	while (!sw_s1.empty())
	{
		std::cout << ' ' << sw_s1.top();
		sw_s1.pop();
	}
	std::cout << ", ";
	while (!sw_s2.empty())
	{
		std::cout << ' ' << sw_s2.top();
		sw_s2.pop();
	}
	std::cout << '\n';
}

void test_stack()
{
	std::cout << "-------------stack_constructor---------------" << std::endl;
	stack_constructor();
	std::cout << "-------------stack_mem_func---------------" << std::endl;
	stack_mem_func();
	std::cout << "-------------stack_non_mem---------------" << std::endl;
	stack_non_mem();
}