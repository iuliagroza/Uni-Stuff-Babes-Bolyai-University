# Hough Transform

This project demonstrates a parallelized approach to perform the Hough Transform for line detection on an image using MPI (Message Passing Interface) and OpenCV. The code is designed to run on multiple processes where the master process reads an image, processes it, and then distributes parts of the image to other processes. Each process applies the Canny edge detector and performs a Hough Transform to detect lines. Finally, the master process gathers the detected lines from all processes and draws them on the original image.

#### © Iulia Groza
