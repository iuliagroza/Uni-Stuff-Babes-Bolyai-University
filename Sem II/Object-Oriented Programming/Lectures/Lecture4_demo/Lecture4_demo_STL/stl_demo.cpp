#include <iostream>
#include <Windows.h>
#include <vector>
#include <deque>
#include <list>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>

using namespace std;

int stringGreater(const string& a, const string& b)
{
	return a > b;
}

class FunctionObject 
{
public:
	bool operator()(const string& a, const string& b) { return a > b; }
};


int main()
{
	system("color f4");

	// *******************************************************************************************************************
	// std::vector
	vector<int> integers{ 1, 2, 3, 4, 5 };
	
	vector<string> strings{ "Hello", ",", "you", "brilliant", "students" };

	cout << "The size of the vector of strings is: " << strings.size() << endl;
	strings.push_back("!");
	cout << "We added another element, now the size of the vectors of strings is: " << strings.size() << endl;
	strings[5] += "!!";
	for (auto s : strings)
		cout << s << " ";
	cout << endl;

	// iterating through a vector with iterators
	for (vector<string>::iterator it = strings.begin(); it != strings.end(); it++)
		cout << *it << " ";
	cout << endl;

	// erase elements
	integers.erase(integers.begin());		// erase the first element
	integers.erase(integers.begin() + 3);	// erase the 4th element
	// create an iterator and erase using the iterator
	auto iter = integers.begin();
	iter++;
	integers.erase(iter);					// the iterator is invalidated here
	//iter--;								// working with an invalidated iterator results in undefined behaviour

	// insert some of the elements back
	integers.insert(integers.begin(), 1);
	integers.insert(integers.begin() + 2, 5);

	// std::deque
	deque<double> doubles{1, 2};
	doubles.push_back(4);
	doubles.push_back(6);
	doubles.push_back(9);
	doubles[2] = doubles[0] + 100;
	auto size = doubles.size();
	cout << size << endl;
	for (auto d : doubles)
		cout << d << " ";
	cout << endl;

	// std::list
	list<double> doubles_list;
	doubles_list.push_back(1);
	doubles_list.push_back(2);
	doubles_list.push_back(10);
	while (!doubles_list.empty()) {
		cout << " " << doubles_list.front();
		doubles_list.pop_front();
	}


	// *******************************************************************************************************************
	// STL algorithms
	// compute the sum of the elements from a vector

	// version 1
	int sum = 0;
	for (int i = 0; i < integers.size(); i++)
		sum += integers[i];

	// version 2
	sum = 0;
	for (const auto& el : integers) 
		sum += el;

	// version 3 - accumulate algorithm
	sum = accumulate(integers.begin(), integers.end(), 0); // accumulate - in header <numeric>

	// --------------------------------------------------------------------------------------------------------------------
	// find algorithm
	auto it = find(strings.begin(), strings.end(), "brilliant");
	*it = "amazing";

	// --------------------------------------------------------------------------------------------------------------------
	// sort algorithm
	sort(strings.begin(), strings.end());
	sort(strings.begin(), strings.end(), stringGreater);
	sort(strings.begin(), strings.end(), FunctionObject{});
	sort(strings.begin(), strings.end(), [](const string a, const string& b) {return a > b; });
	sort(strings.begin(), strings.end(), std::greater<string>());

	// --------------------------------------------------------------------------------------------------------------------
	// algorithms with lambdas
	auto evenNumbers = count_if(integers.begin(), integers.end(), 
		[](int x) { return x % 2 == 0; });
	
	evenNumbers = count_if(integers.begin(), integers.end(), 
		[](int x) -> bool {return x % 2 == 0; }); // we can specify the return type

	vector<int> oddNumbers(5);
	auto isOdd = [](int x) { return x % 2 == 1; }; // the return type is deduced from what is returned in the function
	const bool _2_isOdd = isOdd(2);
	cout << _2_isOdd << endl;
	copy_if(integers.begin(), integers.end(), oddNumbers.begin(), isOdd);

	// specifying a return type for a lambda
	auto lambdaSum = [](double x, double y) -> double { return x + y; };
	cout << "Lambda sum: " << lambdaSum(1.2, 3.3) << endl;

	sort(strings.begin(), strings.end(), 
		[](const string& a, const string& b) { return a < b; });

	for_each(integers.begin(), integers.end(), 
		[](int x) { cout << x << " "; }); // if the lambda returns a result, the result is discarded

	vector<int> doublesOfIntegers(5);
	transform(integers.begin(), integers.end(), 
		doublesOfIntegers.begin(), 
		[](int x) { return x * 2; }); // the return value is assigned to successive elements in the output range

	// using capture lists
	int factor = 3;
	const auto multiply = [factor](int x) { return x * factor; };		
	//auto multiply = [&factor](int x) { return x*factor; };
	int result = multiply(10);	// what is the value of result in the 2 cases: auto multiply = [factor](int x) { return x* factor; };     auto multiply = [&factor](int x) { return x* factor; }; ?
	factor++;
	result = multiply(10);  // what is the value of result in the 2 cases: auto multiply = [factor](int x) { return x* factor; };     auto multiply = [&factor](int x) { return x* factor; }; ?

	int adding_term = 5;
	// default capture by value
	const auto multiply_and_add = [=](int x) { return x * factor + adding_term; };
	adding_term++;
	result = multiply_and_add(10);
	// default capture by reference
	const auto multiply_and_add_ref = [&](int x) { return x * factor + adding_term; };
	factor++;
	adding_term++;
	result = multiply_and_add_ref(10);

	system("pause");
	return 0;
}
