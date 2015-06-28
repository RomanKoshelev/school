// Листинг 13
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;
using std::tr1::function;

struct lambda_generator
{
	lambda_generator(){
		main();
	}

	int main()
	{
		vector<int> myVec;
		int init = 0;
		generate_n(back_inserter(myVec), 10, [&]
		{
			return init++;
		});

		function<void(int)> traceLambda = [](int _val) -> void
		{
			cout << _val << " ";
		};

		for_each(myVec.begin(), myVec.end(), traceLambda);
		cout << endl;

		function<function<int(int)>(int)> 
		//auto 
		lambdaGen = [](int _val) -> function<int(int)>
		{
			return [_val](int _n) -> int { return _n + _val; };
		};

		transform(myVec.begin(), myVec.end(), myVec.begin(), lambdaGen(2));
		for_each(myVec.begin(), myVec.end(), traceLambda);
		cout << endl;

		return EXIT_SUCCESS;
	}
};


//lambda_generator test;