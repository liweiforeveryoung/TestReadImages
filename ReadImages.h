#pragma once
#include <fstream>
#include <vector>
#include <opencv2/core.hpp>
#include <string>

//#define _DEBUG_

class ReadImage
{
public:
	ReadImage(std::ofstream& os, int maxPicsNum);
	~ReadImage();

public:
	void testReadImages(int pictureNums[],int num);
	
private:
	std::ofstream& m_os;
	std::vector<cv::Mat> m_mats;
	std::vector<char[100]> m_filenames;
	std::string m_currentMode;
	int m_maxThreads;
	int m_maxPicNums;

private:
	void initFilenames();
	void initOstream();
	void testReadImages(int pictureNum);
	double readImagesWithThreads(int imagesNum, int threadsNum);

public:
	void testVecImage();

};

void translateIntToChar(int num, char str[],int len);

void readImages(std::vector<cv::Mat>::iterator imageBeginIt,std::vector<char[100]>::iterator fileBeginIt, int size);