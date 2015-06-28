// Листинг 12
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

class MyMegaInitializer
{
public:
	MyMegaInitializer(int _base, int _power)
		: m_val(_base)
		, m_power(_power)
	{}

	void initializeVector(vector<int> & _vec)
	{
		for_each(_vec.begin(), _vec.end(), [this](int & _val) mutable
		{
			_val = m_val;
			m_val *= m_power;
		});
	}

private:
	int m_val, m_power;
};

struct lambda_this_capture
{
	lambda_this_capture(){
		main();
	}

	static int main()
	{
		vector<int> myVec(11);
		MyMegaInitializer initializer(1, 2);
		initializer.initializeVector(myVec);

		for_each(myVec.begin(), myVec.end(), [](int _val)
		{
			cout << _val << " ";
		});
		cout << endl;

		return EXIT_SUCCESS;
	}
};

//lambda_this_capture test;