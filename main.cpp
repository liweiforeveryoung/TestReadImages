#include "ReadImages.h"

int main()
{
	std::ofstream os("TestResult.txt", std::ios::app | std::ios::end);
	ReadImage rdImage(os, 150);

	int nums[] = { 20,40,80,100,150 };
	rdImage.testReadImages(nums, 5);

	return 0;
}

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <ctime>
#include <iostream>

//void test1()
//{
//	clock_t time1, time2, time3;
//	{
//		time1 = clock();
//		cv::Mat image = cv::imread("E:/HuaShanPics/DSC_J1_00007.JPG");
//		time2 = clock();
//		image.release();
//	}
//	time3 = clock();
//
//	double interval1, interval2;
//	interval1 = static_cast<double>(time2 - time1) / CLOCKS_PER_SEC;
//	interval2 = static_cast<double>(time3 - time2) / CLOCKS_PER_SEC;
//
//	std::cout << interval1 << "    " << interval2 << std::endl;
//}

//void test2()
//{
//	clock_t time1, time2, time3,time4,time5;
//	{
//		time1 = clock();
//		cv::Mat image1 = cv::imread("E:/HuaShanPics/DSC_J1_00007.JPG");
//		time2 = clock();
//
//		cv::Mat image2 = cv::imread("E:/HuaShanPics/DSC_J1_00008.JPG");
//		time3 = clock();
//
//		image1 = image2;
//		time4 = clock();
//	}
//	time5 = clock();
//
//	double interval1, interval2, interval3, interval4;
//	interval1 = static_cast<double>(time2 - time1) / CLOCKS_PER_SEC;
//	interval2 = static_cast<double>(time3 - time2) / CLOCKS_PER_SEC;
//	interval3 = static_cast<double>(time4 - time3) / CLOCKS_PER_SEC;
//	interval4 = static_cast<double>(time5 - time4) / CLOCKS_PER_SEC;
//
//	std::cout << interval1 << "    " << interval2 << "    " << interval3 << "    " << interval4 << std::endl;
//}
//
//int main()
//{
//	test1();
//}
