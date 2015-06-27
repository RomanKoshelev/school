#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <deque>

class A
{
	class StaticConstructor
	{
	public:
		StaticConstructor(const char * s){
			//std::cout << s << "\n";
			A::n = 1000;
		}
	};

	static StaticConstructor constr1;
	static StaticConstructor constr2;
	static int n;

public:
	A()
	{
		i = ++n;
	}
	int i;
};

A::StaticConstructor A::constr2("c2");
A::StaticConstructor A::constr1("c1");
int A::n(10);

void static_test()
{
	void *p = malloc(sizeof(A));
	A* a = new (p)A();

	std::cout << p << " " << a << " " << a->i << "\n";
}