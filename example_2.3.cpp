// Example 2-3. Program to add a trackbar slider to the basic viewer window
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace std;

int	g_slider_postion = 0;
CvCapture* g_capture = NULL;

/*
OK, you caught us.  Video playback under linux is still just bad.  Part of this is due to FFMPEG, part of this
is due to lack of standards in video files.  But the position slider here will often not work. We tried to at least
find number of frames using the "getAVIFrames" hack below.  Terrible.  But, this file shows something of how to
put a slider up and play with it.  Sorry.
*/
//Hack because sometimes the number of frames in a video is not accessible. 
//Probably delete this on Widows
int getAVIFrames(char * fname) { 
    char tempSize[4];
    // Trying to open the video file
    ifstream  videoFile( fname , ios::in | ios::binary );
    // Checking the availablity of the file
    if ( !videoFile ) {
      cout << "Couldn’t open the input file " << fname << endl;
      exit( 1 );
    }
    // get the number of frames
    videoFile.seekg( 0x30 , ios::beg );
    videoFile.read( tempSize , 4 );
    int frames = (unsigned char ) tempSize[0] + 0x100*(unsigned char ) tempSize[1] + 0x10000*(unsigned char ) tempSize[2] +    0x1000000*(unsigned char ) tempSize[3];
    videoFile.close(  );
    return frames;
}

void onTrackbarSlide(int pos) {
	cvSetCaptureProperty(g_capture, CV_CAP_PROP_POS_FRAMES, pos);
}

int main(int argc, char** argv) {
	cvNamedWindow("Example3", CV_WINDOW_AUTOSIZE);
	g_capture = cvCreateFileCapture(argv[1]);
	//int frames = (int) cvGetCaptureProperty(g_capture, CV_CAP_PROP_FRAME_COUNT);
	int frames = getAVIFrames(argv[1]); //This is a hack because on linux, getting number of frames often doesn't work
	printf("frame count = %d\n", frames);
	if (frames != 0) {
		cvCreateTrackbar("Position", "Example3", &g_slider_postion, frames, onTrackbarSlide);
	}
	
	IplImage* frame;
	int n = 0;
	while (1) {
		frame = cvQueryFrame(g_capture);
		if (frame == NULL) break;
		n++;
		cvSetTrackbarPos("Position", "Example3", n);
		cvShowImage("Example3", frame);
		char c = cvWaitKey(33);
		if (c == 27) break;
	}
	
	cvReleaseCapture(&g_capture);
	cvDestroyWindow("Example3");
	return 0;
}
