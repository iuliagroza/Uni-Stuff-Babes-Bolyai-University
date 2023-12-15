#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <random>

using namespace std;

// Regular O(n^2) polynomial multiplication
vector<int> multiplyRegular(const vector<int> &a, const vector<int> &b)
{
    vector<int> result(a.size() + b.size() - 1, 0);
    for (size_t i = 0; i < a.size(); i++)
    {
        for (size_t j = 0; j < b.size(); j++)
        {
            result[i + j] += a[i] * b[j];
        }
    }
    return result;
}

// Function to multiply a part of the polynomial
void multiplyPart(const vector<int> &a, const vector<int> &b, vector<int> &result, int start, int end)
{
    for (int i = start; i < end; ++i)
    {
        for (size_t j = 0; j < b.size(); ++j)
        {
            if (i - j >= 0 && i - j < a.size())
            {
                result[i] += a[i - j] * b[j];
            }
        }
    }
}

// Parallelized Regular O(n^2) polynomial multiplication
vector<int> multiplyRegularParallel(const vector<int> &a, const vector<int> &b)
{
    int n = a.size() + b.size() - 1;
    vector<int> result(n, 0);

    int maxThreads = thread::hardware_concurrency();
    vector<thread> threads(maxThreads);
    int blockSize = n / maxThreads;

    for (int i = 0; i < maxThreads; ++i)
    {
        int start = i * blockSize;
        int end = (i == maxThreads - 1) ? n : start + blockSize;

        threads[i] = thread(multiplyPart, ref(a), ref(b), ref(result), start, end);
    }

    // Wait for all threads to complete
    for (thread &t : threads)
    {
        if (t.joinable())
        {
            t.join();
        }
    }

    return result;
}

// Function to add two polynomials
vector<int> add(const vector<int> &a, const vector<int> &b)
{
    size_t n = max(a.size(), b.size());
    vector<int> result(n, 0);
    for (size_t i = 0; i < n; ++i)
    {
        int ai = (i < a.size()) ? a[i] : 0;
        int bi = (i < b.size()) ? b[i] : 0;
        result[i] = ai + bi;
    }
    return result;
}

// Function to subtract two polynomials
vector<int> subtract(const vector<int> &a, const vector<int> &b)
{
    size_t n = max(a.size(), b.size());
    vector<int> result(n, 0);
    for (size_t i = 0; i < n; ++i)
    {
        int ai = (i < a.size()) ? a[i] : 0;
        int bi = (i < b.size()) ? b[i] : 0;
        result[i] = ai - bi;
    }
    return result;
}

// Karatsuba algorithm for polynomial multiplication
vector<int> multiplyKaratsuba(const vector<int> &a, const vector<int> &b)
{
    size_t n = max(a.size(), b.size());

    // Base case for recursion
    if (n <= 6)
    {
        return multiplyRegular(a, b);
    }

    // Making the degree of polynomials even
    size_t m = (n + 1) / 2;

    vector<int> a_low(a.begin(), a.begin() + min(m, a.size()));
    vector<int> a_high(a.begin() + min(m, a.size()), a.end());
    vector<int> b_low(b.begin(), b.begin() + min(m, b.size()));
    vector<int> b_high(b.begin() + min(m, b.size()), b.end());

    vector<int> a_high_plus_low = add(a_high, a_low);
    vector<int> b_high_plus_low = add(b_high, b_low);

    // Recursive calls
    vector<int> z0 = multiplyKaratsuba(a_low, b_low);
    vector<int> z1 = multiplyKaratsuba(a_high_plus_low, b_high_plus_low);
    vector<int> z2 = multiplyKaratsuba(a_high, b_high);

    // Combining the results
    vector<int> temp = subtract(z1, z0);
    temp = subtract(temp, z2);

    vector<int> result(a.size() + b.size() - 1, 0);
    for (size_t i = 0; i < z0.size(); i++)
        result[i] += z0[i];
    for (size_t i = 0; i < temp.size(); i++)
        result[i + m] += temp[i];
    for (size_t i = 0; i < z2.size(); i++)
        result[i + 2 * m] += z2[i];

    return result;
}

// Parallelized Karatsuba algorithm for polynomial multiplication
vector<int> multiplyKaratsubaParallel(const vector<int> &a, const vector<int> &b)
{
    size_t n = max(a.size(), b.size());

    // Base case for recursion
    if (n <= 6)
    {
        return multiplyRegularParallel(a, b);
    }

    size_t m = (n + 1) / 2;

    vector<int> a_low(a.begin(), a.begin() + min(m, a.size()));
    vector<int> a_high(a.begin() + min(m, a.size()), a.end());
    vector<int> b_low(b.begin(), b.begin() + min(m, b.size()));
    vector<int> b_high(b.begin() + min(m, b.size()), b.end());

    vector<int> a_high_plus_low = add(a_high, a_low);
    vector<int> b_high_plus_low = add(b_high, b_low);

    vector<int> z0, z1, z2;

    // Create threads for independent tasks
    thread t1([&]()
              { z0 = multiplyKaratsubaParallel(a_low, b_low); });
    thread t2([&]()
              { z1 = multiplyKaratsubaParallel(a_high_plus_low, b_high_plus_low); });
    thread t3([&]()
              { z2 = multiplyKaratsubaParallel(a_high, b_high); });

    // Wait for threads to complete
    t1.join();
    t2.join();
    t3.join();

    vector<int> temp = subtract(z1, z0);
    temp = subtract(temp, z2);

    vector<int> result(a.size() + b.size() - 1, 0);
    for (size_t i = 0; i < z0.size(); i++)
        result[i] += z0[i];
    for (size_t i = 0; i < temp.size(); i++)
        result[i + m] += temp[i];
    for (size_t i = 0; i < z2.size(); i++)
        result[i + 2 * m] += z2[i];

    return result;
}

std::vector<int> generateRandomPolynomial(size_t size)
{
    std::vector<int> polynomial(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10); // Range of coefficients: 1 to 10

    for (size_t i = 0; i < size; ++i)
    {
        polynomial[i] = dis(gen);
    }

    return polynomial;
}

int main()
{
    vector<int> poly1 = {1, 2, 3};
    vector<int> poly2 = {4, 5, 6};

    // Regular multiplication
    auto start = chrono::high_resolution_clock::now();
    auto regularResult = multiplyRegular(poly1, poly2);
    auto end = chrono::high_resolution_clock::now();
    cout << "Time for regular multiplication: "
         << chrono::duration_cast<chrono::microseconds>(end - start).count() << " ms" << endl;
    cout << "Regular result size: " << regularResult.size() << endl;

    // Parallel regular multiplication
    start = chrono::high_resolution_clock::now();
    auto parallelRegularResult = multiplyRegularParallel(poly1, poly2);
    end = chrono::high_resolution_clock::now();
    cout << "Time for parallel regular multiplication: "
         << chrono::duration_cast<chrono::microseconds>(end - start).count() << " ms" << endl;
    cout << "Parallel regular result size: " << parallelRegularResult.size() << endl;

    // Karatsuba multiplication
    start = chrono::high_resolution_clock::now();
    auto karatsubaResult = multiplyKaratsuba(poly1, poly2);
    end = chrono::high_resolution_clock::now();
    cout << "Time for Karatsuba multiplication: "
         << chrono::duration_cast<chrono::microseconds>(end - start).count() << " ms" << endl;
    cout << "Karatsuba result size: " << karatsubaResult.size() << endl;

    // Parallel Karatsuba multiplication
    start = chrono::high_resolution_clock::now();
    auto parallelKaratsubaResult = multiplyKaratsubaParallel(poly1, poly2);
    end = chrono::high_resolution_clock::now();
    cout << "Time for parallel Karatsuba multiplication: "
         << chrono::duration_cast<chrono::microseconds>(end - start).count() << " ms" << endl;
    cout << "Parallel Karatsuba result size: " << parallelKaratsubaResult.size() << endl;

    // Display the first few and last few coefficients of the result
    auto displayCoefficients = [](const vector<int> &result)
    {
        const size_t displayCount = 5; // Number of coefficients to display from start and end
        for (size_t i = 0; i < min(result.size(), displayCount); i++)
        {
            cout << result[i] << " ";
        }
        if (result.size() > 2 * displayCount)
        {
            cout << "... ";
            for (size_t i = result.size() - displayCount; i < result.size(); i++)
            {
                cout << result[i] << " ";
            }
        }
        cout << endl;
    };

    cout << "Regular result: ";
    displayCoefficients(regularResult);
    cout << "Parallel regular result: ";
    displayCoefficients(parallelRegularResult);
    cout << "Karatsuba result: ";
    displayCoefficients(karatsubaResult);
    cout << "Parallel Karatsuba result: ";
    displayCoefficients(parallelKaratsubaResult);

    // Experiments
    // Small size polynomials
    auto polySmall1 = generateRandomPolynomial(10);
    auto polySmall2 = generateRandomPolynomial(10);

    // Medium size polynomials
    auto polyMedium1 = generateRandomPolynomial(100);
    auto polyMedium2 = generateRandomPolynomial(100);

    // Large size polynomials
    auto polyLarge1 = generateRandomPolynomial(1000);
    auto polyLarge2 = generateRandomPolynomial(1000);

    // Very large size polynomials
    auto polyVeryLarge1 = generateRandomPolynomial(10000);
    auto polyVeryLarge2 = generateRandomPolynomial(10000);

    return 0;
}
