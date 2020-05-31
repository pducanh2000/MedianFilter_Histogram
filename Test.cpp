#include <iostream>
#include <string>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "DucAnh_Header.h"
int main()
{
	//Doc file text roi hien thi qua 1 cua so 
	Mat new_image;
	ReadText2Mat("D:/repos/Project1/Project1/KETQUA_ANH_3.txt",new_image);
	namedWindow("Anh doc tu file text", WINDOW_NORMAL);
	imshow("Anh doc tu file text", new_image);
	waitKey(0);
	destroyWindow("Anh doc tu file text");
	//MedianFilter
	Mat MedianFilter_Mat = MedianFilter(new_image); 
	namedWindow("median filter ", WINDOW_NORMAL);
	imshow("median filter ", MedianFilter_Mat);
	waitKey(0);
	destroyWindow("median filter");
	 
	//Histogram equalization
	Mat Hist_Mat(new_image.rows,new_image.cols, CV_8UC1);
	EqualizeHist(new_image,Hist_Mat);
	namedWindow("Equalize Histogram ", WINDOW_NORMAL);
	imshow("Equalize Histogram ",Hist_Mat);
	waitKey(0);
	destroyWindow("Equalize Histogram");
	//Luu anh lai bool imwrite()
	imwrite("D:/repos/Project1/Project1/Anh_KETQUA_3.png", new_image);
	//Kiem tra Mat2FileText
	Mat image = imread("D:/5b8cdc389077a1c77b6b041239b0cb46.jpg", IMREAD_GRAYSCALE);
	Mat2FileText(image, "D:/repos/Project1/Project1/my_Mat.txt");
	Mat test1_image;
	ReadText2Mat("D:/repos/Project1/Project1/my_Mat.txt", test1_image);
	namedWindow("TEST",WINDOW_NORMAL);
	imshow("TEST", test1_image);
	waitKey(0);
	destroyWindow("TEST");
	return 0;
}