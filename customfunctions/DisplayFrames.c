//Display images through OpenCV

#include "DisplayFrames.h"


using namespace cv;

//Display a single image, need to supply the frame's name, the Mat file
//and the position, where there are 6 positions.
void disImage(char* winName, Mat Image, int Position) {

	#ifndef WINDOWX
	#define WINDOWX 500
	#define WINDOWY 400
	#endif


	namedWindow(winName, WINDOW_NORMAL);
	imshow(winName, Image);
	resizeWindow(winName, WINDOWX, WINDOWY);

	switch (Position) {
		case 1:
			moveWindow(winName, 0, 0);
			break;
		case 2:
			moveWindow(winName, WINDOWX+5, 0);
			break;
		case 3:
			moveWindow(winName, (WINDOWX*2)+10, 0);
			break;
		case 4:
			moveWindow(winName, 0, WINDOWY+25);
			break;
		case 5:
			moveWindow(winName, WINDOWX+5, WINDOWY+25);
			break;
		case 6:
			moveWindow(winName, (WINDOWX*2)+10, WINDOWY+25);
			break;
		default:
			moveWindow(winName, 0, 0);
			break;
	}
}