#include <iostream>
#include <algorithm>
#include <vector>
#include <array>

#include <fstream>
#include <istream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>


// 18:15
// + stdvect<int> (unsigned)
// + sort (only unsigned)
// + unit test
// + unit random test
// + compare to std::sort
// - sort signed int

// --------------------------------------------------------------------------- []
typedef unsigned char digitType;
static const size_t RN = sizeof(int) / sizeof(digitType);
typedef union{
	int n;
	digitType b[RN];
} IntByte;


// --------------------------------------------------------------------------- []
std::vector<digitType> makeDigits(const std::vector<int>& arr, size_t r){
	std::vector<digitType> digits( arr.size(), 0 );
	IntByte ib;
	for (size_t i = 0; i < arr.size(); ++i)
	{
		ib.n = arr[i];
		digits[i] = ib.b[r];
	}
	return digits;
}
// --------------------------------------------------------------------------- []
std::vector<int> countingSortByRadix(const std::vector<int>& arr, size_t r)
{
	const size_t counters_size = 0x1 << (sizeof(digitType)*8);
	std::vector<int> newArr(arr.size());
	std::vector<digitType> digitsIn = makeDigits(arr, r);
	std::vector<digitType> digitsOut(digitsIn.size(), 0);
	std::array<int, counters_size> counters;

	// Count digits
	counters.assign(0);
	for (auto digit : digitsIn)
	{
		counters[digit]++;
	}

	// Count biggest positions for digits (summ left values)
	for (size_t ci = 1; ci < counters.size(); ++ci)
	{
		counters[ci] += counters[ci - 1];
	}

	// Place digits in new positions according to counters
	for (int di = digitsIn.size()-1; di >= 0; --di)
	{
		int digit = digitsIn[di];
		int pos = counters[digit] - 1;
		counters[digit] --;
		digitsOut[pos] = digit;
		newArr[pos] = arr[di];
	}

	return newArr;
}

// --------------------------------------------------------------------------- []
std::vector<int> radix_sort(const std::vector<int>& arr)
{
	std::vector<int> res = arr;
	for (size_t r = 0; r < RN; ++r)
	{
		res = countingSortByRadix(res, r);
	}
	return res;
}

// --------------------------------------------------------------------------- []





// --------------------------------------------------------------------------- []
struct radix_sort_tests
{	
	radix_sort_tests(){
		std::cout << "radix_sort_tests";
		std::cout << std::endl;

		small_array_is_sorted();
		random_array_is_sorted();
		big_random_array_is_sorted();
		radix_sort_is_faster_than_qsort();
	}

private:
	// Tests
	void small_array_is_sorted(){
		test("small_array_is_sorted", makeSmallArr(), true);
	}
	void random_array_is_sorted(){
		test("random_array_is_sorted", makeRandomArr(20), true);
	}	
	
	void big_random_array_is_sorted(){
		test("big_random_array_is_sorted", makeRandomArr(100*1000));
	}

	void radix_sort_is_faster_than_qsort()
	{
		const size_t size = 100 * 1000 *1000;

		std::cout << std::endl;
		std::cout << "radix_sort_is_faster_than_qsort" << std::endl;
		std::cout << "size: " << size << std::endl;

		auto randarr = makeRandomArr(size);
		
		std::cout << "radix_sort...";
		time_t radix_beg = time(0);
		auto sortedarr = radix_sort(randarr);
		time_t radix_end = time(0);
		time_t radix_time = radix_end - radix_beg;
		assert_is_sorted(sortedarr);
		std::cout << std::endl << "radix_time: " << radix_time << std::endl;

		std::cout << "quick_sort...";
		time_t qsort_beg = time(0);
		qsort(&randarr[0], randarr.size(), sizeof(int), [](const void* p1, const void* p2){
			return *((int*)p1) - *((int*)p2);
		});
		time_t qsort_end = time(0);
		time_t qsort_time = qsort_end - qsort_beg;
		assert_is_sorted(randarr);
		std::cout << std::endl << "qsort_time: " << qsort_time << std::endl;
	}

	// Common test
	void test(const char *name, const std::vector<int>& inarr, bool printArrs = false)
	{
		std::cout << std::endl;
		std::cout << name;
		std::cout << std::endl;

		auto unsorted = inarr;
		auto sorted = radix_sort(unsorted);

		if (printArrs){
			print(unsorted);
			print(sorted);
		}

		assert_is_sorted(sorted);
		std::cout << "ok";
		std::cout << std::endl;
	}

	// Utils
	std::vector<int> makeSmallArr(){
		return { 1000, 10, 100, 1, 2, 4, 3, 3, 0, 1 };
	}

	std::vector<int> makeRandomArr(size_t size)
	{
		std::vector<int> res(size);
		for (size_t i = 0; i < size; ++i)
		{
			res[i] = abs(rand());
		}
		return res;
	}

	template< typename T >
	void print(T& arr)
	{
		for (auto i : arr)
		{
			std::cout << (int)i << " ";
		}
		std::cout << std::endl;
	}

	// Asserts
	void assert_is_sorted(const std::vector<int>& arr){
		_ASSERTE(std::is_sorted(arr.begin(), arr.end()));
	}
};

static radix_sort_tests _rs_tests;