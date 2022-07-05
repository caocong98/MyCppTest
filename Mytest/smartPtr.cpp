#include <iostream>
#include <memory>
using namespace std;


// class B;
// class A
// {
// public:
// 	A()
// 	{
// 		std::cout << "A()" << std::endl;
// 	}
// 	~A()
// 	{
// 		std::cout << "~A()" << std::endl;
// 	}
// public:
// 	shared_ptr<B> spa;
// };
// class B
// {
// public:
// 	B()
// 	{
// 		std::cout << "B()" << std::endl;
// 	}
// 	~B()
// 	{
// 		std::cout << "~B()" << std::endl;
// 	}
// public:
// 	shared_ptr<A> spb;
// };

class B;
class A
{
public:
	A()
	{
		std::cout << "A()" << std::endl;
	}
	~A()
	{
		std::cout << "~A()" << std::endl;
	}
public:
	weak_ptr<B> spa;
};
class B
{
public:
	B()
	{
		std::cout << "B()" << std::endl;
	}
	~B()
	{
		std::cout << "~B()" << std::endl;
	}
public:
	weak_ptr<A> spb;
};

int main()
{
	shared_ptr<A> pa(new A());
	shared_ptr<B> pb(new B());
	pa->spa = pb;
	pb->spb = pa;
	return 0;
}
