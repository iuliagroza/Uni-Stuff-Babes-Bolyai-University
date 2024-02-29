#include <mpi.h>
#include <vector>
#include <iostream>
#include <chrono>
#include <random>

std::vector<int> multiplyRegular(const std::vector<int> &poly1, const std::vector<int> &poly2)
{
    int n1 = poly1.size(), n2 = poly2.size();
    std::vector<int> result(n1 + n2 - 1, 0);

    for (int i = 0; i < n1; i++)
        for (int j = 0; j < n2; j++)
            result[i + j] += poly1[i] * poly2[j];

    return result;
}

// Function to add two polynomials
std::vector<int> add(const std::vector<int> &a, const std::vector<int> &b)
{
    size_t n = std::max(a.size(), b.size());
    std::vector<int> result(n, 0);
    for (size_t i = 0; i < n; ++i)
    {
        int ai = (i < a.size()) ? a[i] : 0;
        int bi = (i < b.size()) ? b[i] : 0;
        result[i] = ai + bi;
    }
    return result;
}

// Function to subtract two polynomials
std::vector<int> subtract(const std::vector<int> &a, const std::vector<int> &b)
{
    size_t n = std::max(a.size(), b.size());
    std::vector<int> result(n, 0);
    for (size_t i = 0; i < n; ++i)
    {
        int ai = (i < a.size()) ? a[i] : 0;
        int bi = (i < b.size()) ? b[i] : 0;
        result[i] = ai - bi;
    }
    return result;
}

// Karatsuba algorithm for polynomial multiplication
std::vector<int> multiplyKaratsuba(const std::vector<int> &a, const std::vector<int> &b)
{
    size_t n = std::max(a.size(), b.size());

    // Base case for recursion
    if (n <= 6)
    {
        return multiplyRegular(a, b);
    }

    // Making the degree of polynomials even
    size_t m = (n + 1) / 2;

    std::vector<int> a_low(a.begin(), a.begin() + std::min(m, a.size()));
    std::vector<int> a_high(a.begin() + std::min(m, a.size()), a.end());
    std::vector<int> b_low(b.begin(), b.begin() + std::min(m, b.size()));
    std::vector<int> b_high(b.begin() + std::min(m, b.size()), b.end());

    std::vector<int> a_high_plus_low = add(a_high, a_low);
    std::vector<int> b_high_plus_low = add(b_high, b_low);

    // Recursive calls
    std::vector<int> z0 = multiplyKaratsuba(a_low, b_low);
    std::vector<int> z1 = multiplyKaratsuba(a_high_plus_low, b_high_plus_low);
    std::vector<int> z2 = multiplyKaratsuba(a_high, b_high);

    // Combining the results
    std::vector<int> temp = subtract(z1, z0);
    temp = subtract(temp, z2);

    std::vector<int> result(a.size() + b.size() - 1, 0);
    for (size_t i = 0; i < z0.size(); i++)
        result[i] += z0[i];
    for (size_t i = 0; i < temp.size(); i++)
        result[i + m] += temp[i];
    for (size_t i = 0; i < z2.size(); i++)
        result[i + 2 * m] += z2[i];

    return result;
}

// Function to generate a random polynomial of degree n
std::vector<int> generateRandomPolynomial(int n)
{
    std::vector<int> polynomial(n + 1);
    std::mt19937 generator(time(nullptr));                    // Random number generator
    std::uniform_int_distribution<int> distribution(-10, 10); // Range of coefficients

    for (int i = 0; i <= n; ++i)
    {
        polynomial[i] = distribution(generator); // Assign random coefficient
    }

    return polynomial;
}

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Check for command line argument
    std::string algorithm;
    if (argc > 1)
    {
        algorithm = argv[1];
    }
    else
    {
        // Default to regular if no argument provided
        algorithm = "regular";
    }

    // Capture the start time
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<int> poly1, poly2;
    // Only the root process initializes the full polynomials
    if (world_rank == 0)
    {
        // Randomly generated
        /* int n = 3;
        int m = 4;

        poly1 = generateRandomPolynomial(n);
        poly2 = generateRandomPolynomial(m); */

        // Simple example
        poly1 = {3, 2, 5, 1, 3, 2};
        poly2 = {1, 4, 6, 1, 1, 4, 6, 1};
    }

    // Broadcast the size of poly1 to all processes
    int size_poly1 = (world_rank == 0) ? poly1.size() : 0;
    int size_poly2 = (world_rank == 0) ? poly2.size() : 0;
    MPI_Bcast(&size_poly1, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&size_poly2, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Resize poly1 and poly2 in all processes
    poly1.resize(size_poly1);
    poly2.resize(size_poly2);

    // Calculate the number of coefficients each process will handle
    std::vector<int> send_counts(world_size);
    std::vector<int> displacements(world_size);

    int sum = 0;
    for (int i = 0; i < world_size; ++i)
    {
        send_counts[i] = size_poly1 / world_size;
        if (i < size_poly1 % world_size)
        {
            send_counts[i]++;
        }
        displacements[i] = sum;
        sum += send_counts[i];
    }

    // Allocate space for local polynomial segment in each process
    std::vector<int> local_poly1_segment(send_counts[world_rank]);

    // Scatter the segments of poly1 to each process
    MPI_Scatterv(poly1.data(), send_counts.data(), displacements.data(), MPI_INT,
                 local_poly1_segment.data(), send_counts[world_rank], MPI_INT, 0, MPI_COMM_WORLD);

    // Broadcast poly2 to all processes
    if (world_rank == 0)
    {
        poly2.resize(size_poly2); // Ensure poly2 is large enough for broadcast
    }
    MPI_Bcast(poly2.data(), size_poly1, MPI_INT, 0, MPI_COMM_WORLD);

    // Perform multiplication locally using the selected algorithm
    std::vector<int> local_result(size_poly1 + size_poly2 - 1, 0);
    if (algorithm == "regular")
    {
        local_result = multiplyRegular(local_poly1_segment, poly2);
    }
    else if (algorithm == "karatsuba")
    {
        local_result = multiplyKaratsuba(local_poly1_segment, poly2);
    }

    // Calculate the size of each local result
    std::vector<int> local_result_sizes(world_size);
    int local_result_size = local_result.size();
    MPI_Gather(&local_result_size, 1, MPI_INT, local_result_sizes.data(), 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Gather and combine the results in the root process
    std::vector<int> final_result;
    if (world_rank == 0)
    {
        final_result.resize(std::accumulate(local_result_sizes.begin(), local_result_sizes.end(), 0));
    }

    std::vector<int> displacements_for_results;
    if (world_rank == 0)
    {
        displacements_for_results.resize(world_size);
        int offset = 0;
        for (int i = 0; i < world_size; ++i)
        {
            displacements_for_results[i] = offset;
            offset += local_result_sizes[i];
        }
    }

    MPI_Gatherv(local_result.data(), local_result_size, MPI_INT, final_result.data(), local_result_sizes.data(), displacements_for_results.data(), MPI_INT, 0, MPI_COMM_WORLD);

    // Combine the partial results into the final polynomial product in the root process
    if (world_rank == 0)
    {
        std::vector<int> combined_result(poly1.size() + poly2.size() - 1, 0);

        for (int i = 0; i < world_size; ++i)
        {
            int start_index = displacements[i]; // Starting index for each segment
            for (int j = 0; j < local_result_sizes[i]; ++j)
            {
                // Ensure that the index is within the bounds of the final result
                int idx = start_index + j;
                if (idx < combined_result.size())
                {
                    combined_result[idx] += final_result[j + displacements_for_results[i]];
                }
            }
        }

        std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start;
        std::cout << "Multiplication took " << diff.count() << " seconds\n";
        // Print the combined result
        for (int coeff : combined_result)
        {
            std::cout << coeff << " ";
        }
        std::cout << std::endl;
    }

    MPI_Finalize();

    return 0;
}
