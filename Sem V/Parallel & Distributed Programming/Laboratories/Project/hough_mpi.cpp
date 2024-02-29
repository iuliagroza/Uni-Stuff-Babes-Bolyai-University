#include <mpi.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc != 2)
    {
        if (rank == 0)
        {
            std::cerr << "Usage: " << argv[0] << " <Image_Path>" << std::endl;
        }
        MPI_Finalize();
        return 1;
    }

    double start_time = MPI_Wtime();

    std::string imagePath = argv[1];
    cv::Mat image, grayImage, edgeImage;

    // Master node reads the image and preprocesses it
    if (rank == 0)
    {
        image = cv::imread(imagePath, cv::IMREAD_COLOR);
        if (image.empty())
        {
            std::cerr << "Error: Unable to open the image file!" << std::endl;
            MPI_Abort(MPI_COMM_WORLD, 1);
            return 1;
        }
        cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);

        // Preprocess with Gaussian Blur
        cv::GaussianBlur(grayImage, grayImage, cv::Size(5, 5), 1.5); // Apply blur to the grayscale image
    }

    // Broadcast the image dimensions and type to all nodes
    int img_cols, img_type, elem_size;
    if (rank == 0)
    {
        img_cols = grayImage.cols;
        img_type = grayImage.type();
        elem_size = grayImage.elemSize();
    }

    MPI_Bcast(&img_cols, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&img_type, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&elem_size, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Divide and distribute the image
    int total_rows = rank == 0 ? grayImage.rows : 0;
    MPI_Bcast(&total_rows, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int rows_per_process = total_rows / size;
    int remaining_rows = total_rows % size;

    std::vector<int> sendcounts(size), displs(size);

    int start_row = 0;
    for (int i = 0; i < size; ++i)
    {
        sendcounts[i] = (rows_per_process + (i < remaining_rows ? 1 : 0)) * img_cols * elem_size;
        displs[i] = start_row * img_cols * elem_size;
        start_row += rows_per_process + (i < remaining_rows ? 1 : 0);
    }

    cv::Mat local_image;
    int local_rows = rows_per_process + (rank < remaining_rows ? 1 : 0);
    local_image.create(local_rows, img_cols, img_type);

    // Print the sendcounts and displs arrays for debugging
    if (rank == 0)
    {
        for (int i = 0; i < size; ++i)
        {
            std::cout << "sendcounts[" << i << "]: " << sendcounts[i] << ", displs[" << i << "]: " << displs[i] << std::endl;
        }
    }

    std::cout << "Process " << rank << " local_rows: " << local_rows << ", img_cols: " << img_cols << ", elem_size: " << elem_size << std::endl;

    // MPI_Scatterv call
    MPI_Scatterv(rank == 0 ? grayImage.data : nullptr, sendcounts.data(), displs.data(), MPI_UNSIGNED_CHAR,
                 local_image.data, sendcounts[rank], MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);

    // Apply Canny edge detector with new thresholds
    cv::Mat edges;
    double lower_threshold = 100;
    double upper_threshold = lower_threshold * 2;
    cv::Canny(local_image, edges, lower_threshold, upper_threshold, 3);

    // Perform Hough Transform
    std::vector<cv::Vec2f> local_lines;
    cv::HoughLines(edges, local_lines, 1, CV_PI / 180, 60, 30);

    // Gather the line data - first gather the number of lines detected by each process
    int local_line_count = static_cast<int>(local_lines.size());
    std::vector<int> line_counts(size);
    MPI_Gather(&local_line_count, 1, MPI_INT, line_counts.data(), 1, MPI_INT, 0, MPI_COMM_WORLD);

    std::vector<cv::Vec2f> all_lines;
    std::vector<int> recvcounts(size), displs_lines(size);
    int total_line_count = 0;

    if (rank == 0)
    {
        for (int i = 0; i < size; ++i)
        {
            recvcounts[i] = line_counts[i] * 2; // Each line has 2 float values (rho, theta)
            displs_lines[i] = total_line_count;
            total_line_count += recvcounts[i];
        }
        all_lines.resize(total_line_count / 2); // Resize to total number of lines
    }

    MPI_Gatherv(local_lines.data(), local_line_count * 2, MPI_FLOAT,
                all_lines.data(), recvcounts.data(), displs_lines.data(), MPI_FLOAT,
                0, MPI_COMM_WORLD);

    // Master node draws the lines and outputs the image
    if (rank == 0)
    {
        for (size_t i = 0; i < all_lines.size(); ++i)
        {
            float rho = all_lines[i][0], theta = all_lines[i][1];
            cv::Point pt1, pt2;
            double a = cos(theta), b = sin(theta);
            double x0 = a * rho, y0 = b * rho;
            pt1.x = cvRound(x0 + 1000 * (-b));
            pt1.y = cvRound(y0 + 1000 * (a));
            pt2.x = cvRound(x0 - 1000 * (-b));
            pt2.y = cvRound(y0 - 1000 * (a));
            cv::line(image, pt1, pt2, cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
        }

        cv::imwrite("output_image.jpg", image); // Save the image

        // Display the image
        cv::namedWindow("Detected Lines", cv::WINDOW_AUTOSIZE);
        cv::imshow("Detected Lines", image);
        cv::waitKey(0); // Wait for a keystroke in the window

        // Display the edges
        cv::namedWindow("Edges", cv::WINDOW_AUTOSIZE);
        cv::imshow("Edges", edges);
        cv::waitKey(0);
    }

    double end_time = MPI_Wtime();
    if (rank == 0)
    {
        std::cout << "Execution time: " << end_time - start_time << " seconds" << std::endl;
    }

    MPI_Finalize();
    return 0;
}
