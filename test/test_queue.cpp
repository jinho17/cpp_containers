#include "main.hpp"

void queue_constructor()
{
	ft::List<int> l1 ((size_t)3,100);

	ft::Queue<int> q1;
	std::cout << "1) default constructor: " << q1.size() << '\n';
	ft::Queue<int> q2 (l1);
	std::cout << " ) q2(l1): " << q2.size() << '\n';

	ft::Queue<int> q4(q2);
	std::cout << "2) copy constructor: " << q2.size() << '\n';

	ft::Queue<int,ft::List<int> > q3 = q2;
	std::cout << "3) = operator: " << q3.size() << '\n';
}

void queue_mem_func()
{
	//empty
	ft::Queue<int> emp;
	int sum (0);
	for (int i=1;i<=10;i++)
		emp.push(i);
	while (!emp.empty())
	{
		sum += emp.front();
		emp.pop();
	}
	std::cout << "1) empty test: " << sum << '\n';

	//size
	ft::Queue<int> sz;
	std::cout << "2) size 0: " << sz.size() << '\n';
	for (int i=0; i<5; i++) sz.push(i);
	std::cout << " ) size 5: " << sz.size() << '\n';
	sz.pop();
	std::cout << " ) size 4: " << sz.size() << '\n';

	//front
	ft::Queue<int> frnt;
	frnt.push(77);
	frnt.push(16);
	frnt.front() -= frnt.back();	// 77-16=61
	std::cout << "3) front: " << frnt.front() << '\n';

	//back
	ft::Queue<int> bck;

	bck.push(12);
	bck.push(75);				// this is now the back
	bck.back() -= bck.front();	//75-12= 63
	std::cout << "4) back: " << bck.back() << '\n';

	//push, pop
	ft::Queue<int> psh;
	int myint;
	for(int i = 0; i < 10; i++)
		psh.push (i);

	std::cout << "5) push: ";
	while (!psh.empty())
	{
		std::cout << ' ' << psh.front();
		psh.pop();
	}
	std::cout << '\n';
	std::cout << "6) after pop size: " << psh.size() << std::endl;
}

void queue_non_mem()
{
	//relational operations
	int a_int[] = {10, 20, 30};
	int b_int[] = {10, 20, 30};
	int c_int[] = {30, 20, 10};
	ft::List<int> a(a_int, a_int + 3);
	ft::List<int> b(b_int, b_int + 3);
	ft::List<int> c(c_int, c_int + 3);
	ft::Queue<int> q1(a);
	ft::Queue<int> q2(b);
	ft::Queue<int> q3(c);
	std::cout << "q1:";
	for(ft::List<int>::iterator iter = a.begin(); iter != a.end(); iter++)
		std::cout << " " << *iter;
	std::cout << " | q2:";
	for(ft::List<int>::iterator iter = b.begin(); iter != b.end(); iter++)
		std::cout << " " << *iter;
	std::cout << " | q3:";
	for(ft::List<int>::iterator iter = c.begin(); iter != c.end(); iter++)
		std::cout << " " << *iter;
	std::cout << std::endl;
	if (q1==q2) std::cout << "1) q1==q2\n";
	if (q2!=q3) std::cout << "2) q2!=q3\n";
	if (q2<q3) std::cout << "3) q2<q3\n";
	if (q3>q2) std::cout << "4) q3>q2\n";
	if (q1<=q2) std::cout << "5) q1<=q2\n";
	if (q1>=q2) std::cout << "6) q1>=q2\n";
	std::cout << std::endl;


	//swap
	ft::List<int> foo ((size_t)3,100);
	ft::List<int> bar ((size_t)5,200);
	ft::Queue<int> sw1(foo);
	ft::Queue<int> sw2(bar);
	std::cout << "swap) ";
	for (ft::List<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
	  std::cout << ' ' << *it;
	std::cout << ", ";
	for (ft::List<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
	  std::cout << ' ' << *it;
	std::cout << '\n';

	ft::swap(sw1,sw2);
	std::cout << "    ) ";
	while (!sw1.empty())
	{
		std::cout << ' ' << sw1.front();
		sw1.pop();
	}
	std::cout << ", ";
	while (!sw2.empty())
	{
		std::cout << ' ' << sw2.front();
		sw2.pop();
	}
	std::cout << '\n';
}

void test_queue()
{
	std::cout << "-------------queue_constructor---------------" << std::endl;
	queue_constructor();
	std::cout << "-------------queue_mem_func---------------" << std::endl;
	queue_mem_func();
	std::cout << "-------------queue_non_mem---------------" << std::endl;
	queue_non_mem();
}