#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <iterator>

int main()
{
	system("color f4");

	std::vector<int> myvector;
	for (int i = 1; i < 10; i++)
		myvector.push_back(i * 10);

	// output iterator example
	std::ostream_iterator<int> out_it{ std::cout, ", " }; // writes sequentially to an output stream
	std::copy(myvector.begin(), myvector.end(), out_it);
	std::cout << std::endl;

	// try to use this iterator to read data => ERROR
	// int elem = *out_it;

	// input iterator example
	// let's change values on positions 0 and 1
	std::cout << "Please input values on positions 0 and 1: ";
	std::istream_iterator<int> endOfStreamIterator{}; // the default constructor constructs an end of stream iterator
	std::istream_iterator<int> in_it{ std::cin }; // reads successively from an input stream
	if (in_it != endOfStreamIterator)
		myvector[0] = *in_it;
	in_it++;
	if (in_it != endOfStreamIterator)
		myvector[1] = *in_it;
	std::cout << myvector[0] << " " << myvector[1] << '\n';

	// try to use this iterator to write data => ERROR
	// std::copy(myvector.begin(), myvector.begin() + 1, in_it);


	// ---------------------------------------------------------------------------------------------------------
	std::vector<int> v{ 1, 2, 3, 4, 5, 6 };
	std::vector<int> odds;
	std::deque<int> evens;

	// back inserter
	copy_if(v.begin(), v.end(), back_inserter(odds), [](int x) { return x % 2 == 1; });
	for_each(odds.begin(), odds.end(), [](int x) { std::cout << x << " "; });	// 1 3 5
	std::cout << std::endl;

	// front inserter
	std::front_insert_iterator<std::deque<int>> evensIterator(evens);
	copy_if(v.begin(), v.end(), evensIterator, [](int x) { return x % 2 == 0; });
	for_each(evens.begin(), evens.end(), [](int x) { std::cout << x << " "; });	// 6 4 2
	std::cout << std::endl;

	system("pause");
}
