// a Example show how to use CvMat.
// About memory and type, pls ref to Figure 3-2.
// cook. 9/4 2009.
#include <iostream>
#include <cstdlib>
#include <opencv/highgui.h>

#define min(a, b) (((a) < (b)) ? (a) : (b))

int main(int argc ,char** argv) {
	CvMat *p, m, I;
	int vals[] = {1, 2, 3, 0, 4, 5, 6, 0, 7, 8, 9, 0};
	float valf[] = {0.1, 2.0, 0.3, 0.0, 0.4, 5.0, 0.6, 0.0, 0.7, 8.0, 0.9, 0.0};
	char valc3[] = {11, 12, 13, 21, 22, 23, 31, 32, 33, -11, -12, -13, -21, -22, -23, -31, -32, -33};
	m = cvMat(3, 4, CV_32SC1, &vals); // not alloc memory, just as cvInitMatHeader.
	p = cvCreateMatHeader(3, 4, CV_32FC1); // not alloc for data, just header.
	cvInitMatHeader(&I, 2, 3, CV_8SC3, valc3); // I is like a image.

	// print m
	int *size;
	int dims;
	dims = cvGetDims(&m, NULL);
	size = new int[dims];
	for (int i = 0; i < dims; i++) 
		size[i] = cvGetDimSize(&m, i);
	// I know the dims == 2
	for (int row = 0; row < size[0]; row++) {
		for (int col = 0; col < size[1]; col++) {
			std::cout << (int) CV_MAT_ELEM(m, int, row, col) << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	delete [] size;
	
	// print p
	if (p) {
		int size[2];
		int dims;

		cvInitMatHeader(p, 3, 4, CV_32FC1, valf);
		dims = cvGetDims(p, (int*)size);
		std::cout << "Dims = " << dims << " : " << size[0] << "x" << size[1] << std::endl;
		for (int i = 0; i < size[0]; i++) {
			// more general way
			//float *q = (float*) cvPtr2D(p, i, 0);
			// for CvMat way and compatable
			float *q = (float*) CV_MAT_ELEM_PTR(*p, i, 0);
			// dependend on the define of CvMat, but effective.
			//float *q = (float*) (p->data.ptr + i * p->step);
			for (int j = 0; j < size[1]; j++)
				std::cout << q[j] << " " ;
			std::cout<<std::endl;
		}
		std::cout << std::endl;
	}

	cvReleaseMat(&p);

	// print I
	dims = cvGetDims(&I, NULL);
	std::cout << "dims = " << dims << " : ";
	std::cout << cvGetDimSize(&I, 0);
	for (int i = 1; i < dims; i++)
		std::cout << "x" << cvGetDimSize(&I, i);
	std::cout << std::endl;
	for (int row = 0; row < 2; row++) {
		char* p = (char*) CV_MAT_ELEM_PTR(I, row, 0);
		for (int col = 0; col < 3; col++) {
			std::cout << "(" << (int)p[3 * col + 0] << " " << (int)p[3 * col + 1] << " " << (int)p[3 * col + 2] << "), ";
		}
		std::cout << std::endl;
	}

	// use cvGetDims, cvPtr2D, etc. to operate on IplImage
	if (argc >= 2) {
		std::cout << "\nImage: The functions, like cvGetDims, cvPtr2D etc., can opertate on IplImage correctly." << std::endl;
		IplImage* image = cvLoadImage(argv[1]);
		dims = cvGetDims(image);
		size = new int[dims];
		cvGetDims(image, size);
		std::cout << "dims = " << dims << " : ";
		std::cout << cvGetDimSize(image, 0);
		for (int i = 1; i < dims; i++)
			std::cout << "x" << cvGetDimSize(image, i);
		std::cout << std::endl;
		int n = min(size[0], size[1]);
		for (int row = 0; row < size[0]; row++) {
			uchar* p = (uchar*) cvPtr2D(image, row, 0);
			for (int col = 0; col < size[1]; col++) {
				// draw a red X
				if (abs(row - col) < 2 || abs((n - 1 - col) - row) < 2)
					p[col * 3 + 2] = 255;
			}
		}
		cvNamedWindow("Red X");
		cvShowImage("Red X", image);
		cvWaitKey();
		delete [] size;
		cvReleaseImage(&image);
	}

	return 0;
}
