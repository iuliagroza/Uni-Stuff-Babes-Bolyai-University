#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using Matrix = std::vector<std::vector<int>>;
using std::cout;
using std::endl;
using std::thread;
using std::vector;
using std::chrono::seconds;
using std::this_thread::sleep_for;

// Function to print a matrix
void printMatrix(const Matrix &matrix)
{
    for (const auto &row : matrix)
    {
        for (auto val : row)
        {
            cout << val << " ";
        }
        cout << endl;
    }
}

// Compute a single element of the resulting matrix
int computeElement(const Matrix &A, const Matrix &B, int row, int col)
{
    int sum = 0;
    for (size_t i = 0; i < A[0].size(); ++i)
    {
        sum += A[row][i] * B[i][col];
    }
    return sum;
}

// Helper function to calculate the task range
std::pair<int, int> getTaskRange(int taskNum, int totalTasks, int totalElements)
{
    int baseElements = totalElements / totalTasks;
    int extraElements = totalElements % totalTasks;
    int start = taskNum * baseElements + std::min(taskNum, extraElements);
    int end = start + baseElements + (taskNum < extraElements ? 1 : 0);
    return {start, end};
}

// Compute task for consecutive elements, row by row
void computeTaskRow(const Matrix &A, const Matrix &B, Matrix &Result, int taskNum, int totalTasks)
{
    int totalElements = A.size() * B[0].size();
    auto [start, end] = getTaskRange(taskNum, totalTasks, totalElements);
    int cols = B[0].size();

    /* cout << "Task " << taskNum << " is starting." << endl; */

    for (int index = start; index < end; ++index)
    {
        int row = index / cols;
        int col = index % cols;
        int res = computeElement(A, B, row, col);
        /* cout << "Task " << taskNum << " is computing element [" << row << "][" << col << "]" << endl;
        sleep_for(seconds(1)); */
        Result[row][col] = res;
    }

    /* cout << "Task " << taskNum << " is finished." << endl; */
}

// Compute task for consecutive elements, column by column
void computeTaskColumn(const Matrix &A, const Matrix &B, Matrix &Result, int taskNum, int totalTasks)
{
    int totalElements = A.size() * B[0].size();
    auto [start, end] = getTaskRange(taskNum, totalTasks, totalElements);
    int rows = A.size();

    cout << "Task " << taskNum << " is starting." << endl;

    for (int index = start; index < end; ++index)
    {
        int col = index / rows;
        int row = index % rows;
        int res = computeElement(A, B, row, col);
        cout << "Task " << taskNum << " is computing element [" << row << "][" << col << "]" << endl;
        sleep_for(seconds(1));
        Result[row][col] = res;
    }

    cout << "Task " << taskNum << " is finished." << endl;
}

// Compute task for every k-th element, going row by row
void computeTaskStride(const Matrix &A, const Matrix &B, Matrix &Result, int taskNum, int totalTasks)
{
    int rows = A.size();
    int cols = B[0].size();

    /* cout << "Task " << taskNum << " is starting." << endl; */

    for (int index = taskNum; index < rows * cols; index += totalTasks)
    {
        int row = index / cols;
        int col = index % cols;
        int res = computeElement(A, B, row, col);
        /* cout << "Task " << taskNum << " is computing element [" << row << "][" << col << "]" << endl;
        sleep_for(seconds(1)); */
        Result[row][col] = res;
    }

    /* cout << "Task " << taskNum << " is finished." << endl; */
}

int main()
{
    // Initialize matrices A and B
    Matrix A = {{1, 2}, {3, 4}};
    Matrix B = {{5, 6}, {7, 8}};
    Matrix Result(A.size(), vector<int>(B[0].size(), 0));

    int numberOfTasks = 4;
    vector<thread> threads;

    // Start timing
    auto start = std::chrono::high_resolution_clock::now();

    // Choose the split method here:
    // For row-wise split
    for (int i = 0; i < numberOfTasks; ++i)
    {
        threads.emplace_back(computeTaskRow, std::ref(A), std::ref(B), std::ref(Result), i, numberOfTasks);
    }

    // For column-wise split (comment out the row-wise section and uncomment this section)
    /* for (int i = 0; i < numberOfTasks; ++i)
    {
        threads.emplace_back(computeTaskColumn, std::ref(A), std::ref(B), std::ref(Result), i, numberOfTasks);
    } */

    // For stride split (comment out the above sections and uncomment this section)
    /* for (int i = 0; i < numberOfTasks; ++i)
    {
        threads.emplace_back(computeTaskStride, std::ref(A), std::ref(B), std::ref(Result), i, numberOfTasks);
    } */

    // Wait for threads to finish
    for (auto &t : threads)
    {
        t.join();
    }

    // End timing
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;

    // Print result
    cout << "Result matrix:\n";
    printMatrix(Result);

    // Print time taken
    cout << "Time taken: " << elapsed.count() << " seconds\n";

    return 0;
}
