// Example 2-3. Program to add a trackbar slider to the basic viewer window
#include <opencv/cv.h>
#include <opencv/highgui.h>

int	g_slider_postion = 0;
CvCapture* g_capture = NULL;

void onTrackbarSlide(int pos) {
	cvSetCaptureProperty(g_capture, CV_CAP_PROP_POS_FRAMES, pos);
}

int main(int argc, char** argv) {
	cvNamedWindow("Example3", CV_WINDOW_AUTOSIZE);
	g_capture = cvCreateFileCapture(argv[1]);
	int frames = (int) cvGetCaptureProperty(g_capture, CV_CAP_PROP_FRAME_COUNT);
	if (frames != 0) {
		cvCreateTrackbar("Position", "Example3", &g_slider_postion, frames, onTrackbarSlide);
	}
	
	IplImage* frame;
	while (1) {
		frame = cvQueryFrame(g_capture);
		if (frame == NULL) break;
		cvShowImage("Example3", frame);
		char c = cvWaitKey(33);
		if (c == 27) break;
	}
	
	cvReleaseCapture(&g_capture);
	cvDestroyWindow("Example3");
	return 0;
}
