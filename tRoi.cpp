// Show how to operate on ROI.
// Note: cvSetImageROI can only be done serially and must be set and reset constantly. So createSubImage is defined.
// cook, 9/4 2009.
#include <opencv/highgui.h>

IplImage* createSubImage(CvSize size, IplImage* image) {
	IplImage *sub_img = cvCreateImageHeader(cvSize(image->width/3, image->height/3), image->depth, image->nChannels);
	sub_img->origin = image->origin;
	sub_img->widthStep = image->widthStep;
	sub_img->imageData = image->imageData +
		(image->height - image->height/3) * image->widthStep +
		(image->width - image->width/3) * image->nChannels;
	return sub_img;
}

int main(int argc, char** argv) {
	IplImage* image = cvLoadImage(argv[1]);
	IplImage* another_sub_img = createSubImage(cvSize(image->width/3, image->height/3), image);
	cvSetImageROI(image, cvRect(0, 0, image->width / 3, image->height / 3));
	cvAddS(image, cvScalar(50), image); // add scalar
	cvAddS(another_sub_img, cvScalar(100), another_sub_img);
	cvResetImageROI(image);
	cvNamedWindow("ROI Example", CV_WINDOW_AUTOSIZE);
	cvShowImage("ROI Example", image);
	cvWaitKey();
	cvReleaseImage(&image);
	return 0;
}
