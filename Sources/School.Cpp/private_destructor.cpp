#include <iostream>

class a {
	~a() {}
	friend void delete_a(a* p);
};


void delete_a(a* p)  {
	delete p;
}

void private_destructor_test()
{
	a *p = new a;
	// a a1; Error
	delete_a(p);
}