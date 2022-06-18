#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

int stringGreater(const string &a, const string &b) {
    return a > b;
}

void stl_demo() {
    // std::vector
    vector<int> integers{1, 2, 3, 4, 5};
    vector<string> strings{"Hello", ",", "you", "great", "students"};

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
    integers.erase(integers.begin());        // erase the first element
    integers.erase(integers.begin() + 3);    // erase the 4th element
    // create an iterator and erase using the iterator
    auto iter = integers.begin();
    iter++;
    integers.erase(iter);                    // the iterator is invalidated here
    //iter--;								// working with an invalidated iterator results in undefined behaviour

    // insert some of the elements back
    integers.insert(integers.begin(), 1);
    integers.insert(integers.begin() + 2, 5);

    // *******************************************************************************************************************
    // STL algorithms
    // compute the sum of the elements from a vector

    // version 1
    int sum = 0;
    for (int i = 0; i < integers.size(); i++)
        sum += integers[i];

    // version 2
    sum = 0;
    for (const auto &el : integers)
        sum += el;

    // version 3 - accumulate algorithm
    sum = accumulate(integers.begin(), integers.end(), 0); // accumulate - in header <numeric>

    // --------------------------------------------------------------------------------------------------------------------
    // find algorithm
    auto it = find(strings.begin(), strings.end(), "you");
    *it = "amazing";

    // --------------------------------------------------------------------------------------------------------------------
    // sort algorithm
    sort(strings.begin(), strings.end());
    sort(strings.begin(), strings.end(), stringGreater);
    for (auto s : strings)
        cout << s << " ";
    cout << endl;

    // --------------------------------------------------------------------------------------------------------------------
    // algorithms with lambdas
    int evenNumbers = count_if(integers.begin(), integers.end(),
                               [](int x) { return x % 2 == 0; });

    evenNumbers = count_if(integers.begin(), integers.end(),
                           [](int x) -> bool { return x % 2 == 0; }); // we can specify the return type

    vector<int> oddNumbers(5);
    auto isOdd = [](int x) { return x % 2 == 1; }; // the return type is deduced from what is returned in the function
    bool _2_isOdd = isOdd(2);
    copy_if(integers.begin(), integers.end(), oddNumbers.begin(), isOdd);

    // specifying a return type for a lambda
    auto lambdaSum = [](double x, double y) -> int { return x + y; };
    cout << "Lambda sum: " << lambdaSum(1.2, 3.3) << endl;

    sort(strings.begin(), strings.end(),
         [](const string &a, const string &b) { return a < b; });

    for_each(integers.begin(), integers.end(),
             [](int x) { cout << x << " "; }); // if the lambda returns a result, the result is discarded

    vector<int> doublesOfIntegers(5);
    transform(integers.begin(), integers.end(),
              doublesOfIntegers.begin(),
              [](int x) { return x * 2; }); // the return value is assigned to successive elements in the output range

    // using capture lists
    int factor = 3;
    auto multiply = [factor](int x) { return x * factor; };
//    auto multiply = [&factor](int x) { return x*factor; };
    int result = multiply(10);


    factor++;
    // what is the value of result in the 2 cases:
    //      auto multiply = [factor](int x) { return x* factor; };
    //      auto multiply = [&factor](int x) { return x* factor; }; ?
    result = multiply(10);
    cout<<endl<<result<<endl;

    int adding_term = 5;
    // default capture by value
    auto multiply_and_add = [=](int x) { return x * factor + adding_term; };
    adding_term++;
    result = multiply_and_add(10);
    // default capture by reference
    auto multiply_and_add_ref = [&](int x) { return x * factor + adding_term; };
    factor++;
    adding_term++;
    result = multiply_and_add_ref(10);
}

//int main() {
//    stl_demo();
//}
