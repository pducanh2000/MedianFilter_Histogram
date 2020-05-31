#pragma once
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace cv;
void ReadText2Mat(std::string file, Mat& my_Mat) {
	std::ifstream in;
	in.open(file);
	std::string line;
	int height = 0;
	int width = 0;
	// Lay cac so trong file text
	while (getline(in, line)) {
		height++;
		std::istringstream stream(line);
		int x;
		while (stream >> x) {
			my_Mat.push_back((uchar)x);
			width++;
		}
	}
	in.close();
	width /= height;
	//Doi lai kich co cua my_Mat tu (1,width*height) thanh (height,width) 1 channel
	my_Mat = my_Mat.reshape(1, height);
}
void Mat2FileText(Mat& my_Mat, std::string file) {
	std::ofstream out;
	out.open(file);
	for (int i = 0; i < my_Mat.rows; i++) {
		for (int j = 0; j < my_Mat.cols; j++) {
			out << (int)my_Mat.at<uchar>(i, j) << ' ';
		}
		out << '\n';
	}
}
int median(int* Mat, int Size) {
	// O(n^2)
	for (int i = 0; i < Size - 1; i++) {
		for (int j = 0; j < Size; j++) {
			if (Mat[i] < Mat[j]) {
				Mat[i] = Mat[i] + Mat[j];
				Mat[j] = Mat[i] - Mat[j];
				Mat[i] = Mat[i] - Mat[j];
			}
		}
	}
	return Mat[Size / 2 + 1];
}
Mat MedianFilter(Mat& my_Mat) {
	Mat new_Mat(my_Mat.rows, my_Mat.cols, CV_8UC1, Scalar(1));
	// Phan ma tran co kich thuoc (my_Mat.rows-2,my_Mat.cols-2)
	int Mat[9];
	for (int i = 0; i < my_Mat.rows - 2; i++) {
		for (int j = 0; j < my_Mat.cols - 2; j++) {
			int a = 0;
			for (int x = i; x < i + 3; x++) {
				for (int y = j; y < j + 3; y++) {
					Mat[a] = int(my_Mat.at<uchar>(x, y));
					a++;
				}
			}
			new_Mat.at<uchar>(i + 1, j + 1) = uchar(median(Mat, 9));
		}
	}
	// Vien ngoai cua ma tran
	for (int i = 0; i < new_Mat.cols; i++) {
		new_Mat.at<uchar>(0, i) = my_Mat.at<uchar>(0, i);
		new_Mat.at<uchar>(new_Mat.rows-1, i) = my_Mat.at<uchar>(my_Mat.rows-1, i);
	}
	for (int i = 1; i < new_Mat.rows-1; i++) {
		new_Mat.at<uchar>(i,0) = my_Mat.at<uchar>(i,0);
		new_Mat.at<uchar>(i,new_Mat.cols - 1) = my_Mat.at<uchar>(i,my_Mat.cols - 1);
	}
	return new_Mat;
}
void Histogram(Mat my_Mat, int* histogram) {
	for (int i = 0; i < 256; i++) {
		histogram[i] = 0;
	}
	for (int i = 0; i < my_Mat.rows; i++) {
		for (int j = 0; j < my_Mat.cols; j++) {
			histogram[(int)my_Mat.at<uchar>(i, j)]++;
		}
	}
}
void CdfHistogram(int* histogram, int* cdf) {
	cdf[0] = histogram[0];
	for (int i = 1; i < 256; i++) {
		cdf[i] = histogram[i] + cdf[i - 1];
	}
}
void Normalize(int* histogram) {
	// Tim max
	int max = histogram[0];
	for (int i = 1; i < 256; i++) {
		if (max < histogram[i]) {
			max = histogram[i];
		}
	}
	// Chuan hoa khoang tu 0 den 255
	for (int i = 0; i < 256; i++) {
		histogram[i] = (int)(((double)histogram[i] / max) * 255);
	}
}
void EqualizeHist(Mat& Input, Mat& Output) {
	int histogram[256];
	Histogram(Input, histogram);
	int cdf[256];
	CdfHistogram(histogram, cdf);
	Normalize(cdf);
	for (int x = 0; x < Input.rows; x++) {
		for (int y = 0; y < Input.cols; y++) {
				Output.at<uchar>(x, y) = uchar(cdf[(int)Input.at<uchar>(x,y)]);
		}
	}

}
