#include "includes.h"
/*
 *	Displays two image windos 
 */
void show(Mat in, Mat out){
	imshow("Input",in);
	imshow("Output", out);
}