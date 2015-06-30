#include <functional>
#include <iostream>

using namespace std;

struct  bind_function
{
	bind_function(){
		main();
	}

	int main() {
		
		auto m0 = plus<int>();

		cout << m0(20,22) << endl;
		//auto 

		auto p1 = bind1st(plus<int>(), 10);
		auto p2 = bind2nd(plus<int>(), 10);
		cout << p1(20) << endl;
		cout << p2(20) << endl;

		auto m1 = bind1st(minus<int>(), 10);
		auto m2 = bind2nd(minus<int>(), 10);
		cout << m1(20) << endl;
		cout << m2(20) << endl;

		return 0;
	}
};

//bind_function test;