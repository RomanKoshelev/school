#include <iostream>
#include <algorithm>
#include <array>

#include <fstream>
#include <istream>
#include <iostream>
#include <string>

// 14:40

template< typename T >
void bubble_sort( T& arr )
{
	for (T::size_type r = 1; r < arr.size(); ++r)
	{
		_ASSERTE(std::is_sorted(arr.begin(), arr.begin() + r - 1));

		for (T::size_type i = r; i > 0; --i)
		{
			if (arr[i] < arr[i - 1])
			{
				std::swap(arr[i], arr[i-1]);
			}
		}
	}
}

template< typename T >
void print(T& arr)
{
	for each (auto i in arr)
	{
		std::cout << i << " ";
	}
	//std::for_each(arr.begin(), arr.end(), [](T::value_type i){ std::cout << i << " "; });
	std::cout << "\n";
}

void bubble_sort_test()
{
	std::cout << "bubble_sort_test\n\n";

	std::array<int,10> aint {9,3,2,4,5,6,8,7,1,0};
		print(aint); 
		bubble_sort(aint); 
		print(aint);
		std::cout << "\n";
		_ASSERTE(std::is_sorted(aint.begin(), aint.end()));
			

	std::array<std::string, 10> astr{ "bc", "xx", "ca", "cb", "cc", "aa", "ab", "ac", "ba", "bb" };
		print(astr);
		bubble_sort(astr);
		print(astr);
		std::cout << "\n";
		_ASSERTE(std::is_sorted(astr.begin(), astr.end()));
}