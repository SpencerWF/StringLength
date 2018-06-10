//Skeletonization through the Zhang-Suen algorithm.  This function assumes the image is in 0 or 255 binary.

#include "ZhangSuenFunctions.h"


using namespace cv;

//Perform one iteration of the Zhang Suen thinning algorithm.
//Don't call this function directly from your code.
void zhangSuenIteration(Mat& image, int iteration) {
	Mat marker = Mat::zeros(image.size(), CV_8UC1);
	int transitions, setPixels, cond1, cond2;
	for (int i = 1; i < image.rows-1; i++) {
		uchar* previous = image.ptr<uchar>(i - 1);
		uchar* current  = image.ptr<uchar>(i);
		uchar* next = image.ptr<uchar>(i + 1);
		for (int j = 1; j < image.cols-1; j++) {
			//Get the intensities of all of the neibouring pixels
			uchar p2 = previous[j];
			uchar p3 = previous[j+1];
			uchar p4 = current[j+1];
			uchar p5 = next[j+1];
			uchar p6 = next[j];
			uchar p7 = next[j-1];
			uchar p8 = current[j-1];
			uchar p9 = previous[j-1];

			//Find the number of black to white transitions in the neibouring pixels, in the order, p2-p3-p4-p5-p6-p7-p8-p9-p2
			transitions  = (p2 == 0 && p3 == 1) + (p3 == 0 && p4 == 1) + (p4 == 0 && p5 == 1) + (p5 == 0 && p6 == 1) + (p6 == 0 && p7 == 1) + (p7 == 0 && p8 == 1) + (p8 == 0 && p9 == 1) + (p9 == 0 && p2 == 1);

			//Count the number of white pixels
			setPixels = p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9;

			//If this is a odd number iteration (first, third, fifth), use p4 and p6 as doublely valuable
			if (iteration == 0) {
				cond1 = (p2 * p4 * p6);
				cond2 = (p4 * p6 * p8);
			}

			//If this is a odd number iteration (first, third, fifth), use p2 and p8 as doublely valuable
			else if (iteration == 1) {
				cond1 = (p2 * p4 * p8);
				cond2 = (p2 * p6 * p8);
			}
			//Checks the 5 conditions required for the Zhang Suen algorithm:
			//Only 1 transition occurs from black to white
			//Between 2 and 6 white pixels are neibouring the current pixel
			//For odd number of the iterations
			//One or more of P2, P4, and P6 are white
			//One or more of P4, P6, and P8 are white
			//For even number of the iterations
			//One or more of P2, P4, and P8 are white
			//One or more of P2, P6, and P8 are white
			if (transitions == 1 && (setPixels>= 2 && setPixels<= 6) && cond1 == 0 && cond2 == 0) {
				marker.at<uchar>(i,j) = 1;
			}
		}
	}

	//Set the selected pixels to black
	image &= ~marker;
}

/**
 * Function for thinning the given binary image
 *
 * @param  im  Binary image with range = 0-WHITE
 */
void zhangSuen(Mat& im)
{
	//Changes the image to 0 or 1 binary, instead of 0 or 255 binary
	im /= WHITE;

	//Creates a image variable to be used to compare between iterations
	Mat prev = Mat::zeros(im.size(), CV_8UC1);
	Mat diff;

	//Calls the two iterations of the algorithm, then compares to see if
	//a change has occured, once no more thinning occurs, the skeletonization
	//is completed.
	do {
		zhangSuenIteration(im, 0);
		zhangSuenIteration(im, 1);
		absdiff(im, prev, diff);
		im.copyTo(prev);
	}
	while (countNonZero(diff) > 0);

	//Changes the image back to 0 or 255 binary
	im *= WHITE;
}