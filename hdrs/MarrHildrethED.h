#include "includes.h"
/*Marr-Hildreth Edge Detecition Alg.*/
Mat marrhildreth(Mat src)
{
	Mat dst = src.clone();
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_8UC1;

	double start = omp_get_wtime();
	// Gaussian filter:
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

	// Apply Laplace function:
	Mat abs_dst;
	Laplacian(dst, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(dst, abs_dst);

	// Enhance the Edge Dection:
	int thresh = 10;
	int height = src.rows;
	int width = src.cols;
	int step = src.step;
	uchar *data1 = (uchar *)src.data;
	uchar *data2 = (uchar *)dst.data;
	int i = step;
#pragma omp parallel private (i) shared(height,width)
	{
#pragma omp for
		for (i = step + 1; i < height*width; i++){
			if (abs(data1[i] - data1[i - 1]) > thresh || abs(data1[i] - data1[i - step]) > thresh)
				data2[i] = 255;
			else
				data2[i] = 0;
		}
		/* Only master thread does this */
#pragma omp master
		{
			printf("-----------------------------\nFilter: Marr/Hildreth\nNumber of threads: %d\nNumber of cores: %d\nNumber of threads per core: %d\n", omp_get_num_threads(), omp_get_num_procs(), omp_get_num_threads() / omp_get_num_procs());
		}
	}
	double end = omp_get_wtime();
	double seconds = end - start;
	printf("Execution Time: %fs\n-----------------------------\n", seconds);
	return dst;
}