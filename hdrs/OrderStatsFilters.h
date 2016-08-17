#include "includes.h"

//Sort the given window using insertion sort
void insertionSort(uchar window[])
{
	int i, j;
	uchar temp;
	for (i = 0; i < 9; i++)
	{
		temp = window[i];
		for (j = i - 1; j >= 0 && temp < window[j]; j--)
		{
			window[j + 1] = window[j];
		}
		window[j + 1] = temp;
	}
}

// Calculates the average of the given window values
int average(uchar window[]){
	int i;
	uchar temp=0;
	for (i = 0; i < 9; i++)
	{
		temp += window[i];
	}
	return temp/9;
}

/* Median Filter */
Mat median(Mat src)
{
	Mat dst;
	double start = omp_get_wtime();

	//Create a sliding window of size 9
	uchar window[9];
	dst = src.clone();
	int y, x, rows = src.rows, cols = src.cols;

	// Parallel Section
	// Filters The given imgage by creating a small window
	#pragma omp parallel private (y, x,window) shared(rows, cols)
	{
		#pragma omp for
			for (y = 1; y < rows - 1; y++)
			{
				for (x = 1; x < cols - 1; x++)
				{
					// Pick up window element (small matrix)
					window[0] = src.at<uchar>(y - 1, x - 1);
					window[1] = src.at<uchar>(y, x - 1);
					window[2] = src.at<uchar>(y + 1, x - 1);
					window[3] = src.at<uchar>(y - 1, x);
					window[4] = src.at<uchar>(y, x);
					window[5] = src.at<uchar>(y + 1, x);
					window[6] = src.at<uchar>(y - 1, x + 1);
					window[7] = src.at<uchar>(y, x + 1);
					window[8] = src.at<uchar>(y + 1, x + 1);
					// Sort the window 
					insertionSort(window);
					// Assign the median pixel value to centered element of the matrix
					dst.at<uchar>(y, x) = window[4];
				}
			}

			/* Only master thread does this */
		#pragma omp master
		{
			printf("-----------------------------\nFilter: Median\nNumber of threads: %d\nNumber of cores: %d\nNumber of threads per core: %d\n", omp_get_num_threads(), omp_get_num_procs(), omp_get_num_threads()/omp_get_num_procs());
		}
	}
	double end = omp_get_wtime();
	double seconds = end - start;
	printf("Execution Time: %fs\n-----------------------------\n", seconds);
	return dst;
}

/* Min Filter */
Mat min(Mat src)
{
	Mat dst;
	double start = omp_get_wtime();

	//Create a sliding window of size 9
	uchar window[9];
	dst = src.clone();
	int y, x, rows = src.rows, cols = src.cols;

	// Parallel Section
	// Filters The given imgage by creating a small window
#pragma omp parallel private (y, x,window) shared(rows, cols)
	{
#pragma omp for
		for (y = 1; y < rows - 1; y++)
		{
			for (x = 1; x < cols - 1; x++)
			{
				// Pick up window element (small matrix)
				window[0] = src.at<uchar>(y - 1, x - 1);
				window[1] = src.at<uchar>(y, x - 1);
				window[2] = src.at<uchar>(y + 1, x - 1);
				window[3] = src.at<uchar>(y - 1, x);
				window[4] = src.at<uchar>(y, x);
				window[5] = src.at<uchar>(y + 1, x);
				window[6] = src.at<uchar>(y - 1, x + 1);
				window[7] = src.at<uchar>(y, x + 1);
				window[8] = src.at<uchar>(y + 1, x + 1);
				// Sort the window 
				insertionSort(window);
				// Assign the min pixel value to centered element of the matrix
				dst.at<uchar>(y, x) = window[0];
			}
		}

		/* Only master thread does this */
#pragma omp master
		{
			printf("-----------------------------\nFilter: Min\nNumber of threads: %d\nNumber of cores: %d\nNumber of threads per core: %d\n", omp_get_num_threads(), omp_get_num_procs(), omp_get_num_threads() / omp_get_num_procs());
		}
	}
	double end = omp_get_wtime();
	double seconds = end - start;
	printf("Execution Time: %fs\n-----------------------------\n", seconds);
	return dst;
}

/* Max Filter*/
Mat max(Mat src)
{
	Mat dst;
	double start = omp_get_wtime();

	//Create a sliding window of size 9
	uchar window[9];
	dst = src.clone();
	int y, x, rows = src.rows, cols = src.cols;

	// Parallel Section
	// Filters The given imgage by creating a small window
#pragma omp parallel private (y, x,window) shared(rows, cols)
	{
#pragma omp for
		for (y = 1; y < rows - 1; y++)
		{
			for (x = 1; x < cols - 1; x++)
			{
				// Pick up window element (small matrix)
				window[0] = src.at<uchar>(y - 1, x - 1);
				window[1] = src.at<uchar>(y, x - 1);
				window[2] = src.at<uchar>(y + 1, x - 1);
				window[3] = src.at<uchar>(y - 1, x);
				window[4] = src.at<uchar>(y, x);
				window[5] = src.at<uchar>(y + 1, x);
				window[6] = src.at<uchar>(y - 1, x + 1);
				window[7] = src.at<uchar>(y, x + 1);
				window[8] = src.at<uchar>(y + 1, x + 1);
				// Sort the window 
				insertionSort(window);
				// Assign the max pixel value to centered element of the matrix
				dst.at<uchar>(y, x) = window[8];
			}
		}

		/* Only master thread does this */
#pragma omp master
		{
			printf("-----------------------------\nFilter: Max\nNumber of threads: %d\nNumber of cores: %d\nNumber of threads per core: %d\n", omp_get_num_threads(), omp_get_num_procs(), omp_get_num_threads() / omp_get_num_procs());
		}
	}
	double end = omp_get_wtime();
	double seconds = end - start;
	printf("Execution Time: %fs\n-----------------------------\n", seconds);
	return dst;
}
/* Min-Max Filter*/
Mat min_max(Mat src){
	Mat dst;
	double start = omp_get_wtime();

	//Create a sliding window of size 9
	uchar window[9];
	dst = src.clone();
	int y, x, rows = src.rows, cols = src.cols;

	// Parallel Section
	// Filters The given imgage by creating a small window
#pragma omp parallel private (y, x,window) shared(rows, cols)
	{
#pragma omp for
		for (y = 1; y < rows - 1; y++)
		{
			for (x = 1; x < cols - 1; x++)
			{
				// Pick up window element (small matrix)
				window[0] = src.at<uchar>(y - 1, x - 1);
				window[1] = src.at<uchar>(y, x - 1);
				window[2] = src.at<uchar>(y + 1, x - 1);
				window[3] = src.at<uchar>(y - 1, x);
				window[4] = src.at<uchar>(y, x);
				window[5] = src.at<uchar>(y + 1, x);
				window[6] = src.at<uchar>(y - 1, x + 1);
				window[7] = src.at<uchar>(y, x + 1);
				window[8] = src.at<uchar>(y + 1, x + 1);
				// Sort the window 
				insertionSort(window);
				// Assign the maximum - minimum to centered element of the matrix
				dst.at<uchar>(y, x) = window[8] - window[0];
			}
		}

		/* Only master thread does this */
#pragma omp master
		{
			printf("-----------------------------\nFilter: Min-Max\nNumber of threads: %d\nNumber of cores: %d\nNumber of threads per core: %d\n", omp_get_num_threads(), omp_get_num_procs(), omp_get_num_threads() / omp_get_num_procs());
		}
	}
	double end = omp_get_wtime();
	double seconds = end - start;
	printf("Execution Time: %fs\n-----------------------------\n", seconds);
	return dst;
}
/* Mid Point Filter*/
Mat midpoint(Mat src){
	Mat dst;
	double start = omp_get_wtime();

	//Create a sliding window of size 9
	uchar window[9];
	dst = src.clone();
	int y, x, rows = src.rows, cols = src.cols;

	// Parallel Section
	// Filters The given imgage by creating a small window
#pragma omp parallel private (y, x,window) shared(rows, cols)
	{
#pragma omp for
		for (y = 1; y < rows - 1; y++)
		{
			for (x = 1; x < cols - 1; x++)
			{
				// Pick up window element (small matrix)
				window[0] = src.at<uchar>(y - 1, x - 1);
				window[1] = src.at<uchar>(y, x - 1);
				window[2] = src.at<uchar>(y + 1, x - 1);
				window[3] = src.at<uchar>(y - 1, x);
				window[4] = src.at<uchar>(y, x);
				window[5] = src.at<uchar>(y + 1, x);
				window[6] = src.at<uchar>(y - 1, x + 1);
				window[7] = src.at<uchar>(y, x + 1);
				window[8] = src.at<uchar>(y + 1, x + 1);
				// Sort the window 
				insertionSort(window);
				// Assign the mid point pixel value to centered element of the matrix
				dst.at<uchar>(y, x) = (window[8] + window[0]) / 2;
			}
		}

		/* Only master thread does this */
#pragma omp master
		{
			printf("-----------------------------\nFilter: Mid Point\nNumber of threads: %d\nNumber of cores: %d\nNumber of threads per core: %d\n", omp_get_num_threads(), omp_get_num_procs(), omp_get_num_threads() / omp_get_num_procs());
		}
	}
	double end = omp_get_wtime();
	double seconds = end - start;
	printf("Execution Time: %fs\n-----------------------------\n", seconds);
	return dst;
}
/* Mean Filter*/
Mat mean(Mat src){
	Mat dst;
	double start = omp_get_wtime();

	//Create a sliding window of size 9
	uchar window[9];
	dst = src.clone();
	int y, x, rows = src.rows, cols = src.cols;

	// Parallel Section
	// Filters The given imgage by creating a small window
#pragma omp parallel private (y, x,window) shared(rows, cols)
	{
#pragma omp for
		for (y = 1; y < rows - 1; y++)
		{
			for (x = 1; x < cols - 1; x++)
			{
				// Pick up window element (small matrix)
				window[0] = src.at<uchar>(y - 1, x - 1);
				window[1] = src.at<uchar>(y, x - 1);
				window[2] = src.at<uchar>(y + 1, x - 1);
				window[3] = src.at<uchar>(y - 1, x);
				window[4] = src.at<uchar>(y, x);
				window[5] = src.at<uchar>(y + 1, x);
				window[6] = src.at<uchar>(y - 1, x + 1);
				window[7] = src.at<uchar>(y, x + 1);
				window[8] = src.at<uchar>(y + 1, x + 1);
				// Assign the average pixel value to centered element of the matrix
				dst.at<uchar>(y, x) = average(window);
			}
		}

		/* Only master thread does this */
#pragma omp master
		{
			printf("-----------------------------\nFilter: Mean\nNumber of threads: %d\nNumber of cores: %d\nNumber of threads per core: %d\n", omp_get_num_threads(), omp_get_num_procs(), omp_get_num_threads() / omp_get_num_procs());
		}
	}
	double end = omp_get_wtime();
	double seconds = end - start;
	printf("Execution Time: %fs\n-----------------------------\n", seconds);
	return dst;
}
