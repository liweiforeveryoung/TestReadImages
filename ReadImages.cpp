#include <ctime>
#include <iomanip>
#include <thread>
#include <opencv2/imgcodecs.hpp>
#include <cassert>
#include "ReadImages.h"

ReadImage::ReadImage(std::ofstream& os, int maxPicsNum):m_os(os),m_maxPicNums(maxPicsNum),m_mats(maxPicsNum),m_filenames(maxPicsNum),m_maxThreads(std::thread::hardware_concurrency())
{
#ifdef _DEBUG_
	m_currentMode = "DEBUG";
#else
	m_currentMode = "RELEASE";
#endif // _DEBUG_

	initFilenames();
	initOstream();

	m_os << m_currentMode << " Test\n";
	m_os << "hardware_concurrency num : " << m_maxThreads << "\n";

}

ReadImage::~ReadImage()
{
	m_os << std::endl;
	m_os.close();
}

void ReadImage::testReadImages(int pictureNums[],int num)
{
	for (int i = 0;i < num;++i)
	{
		int currentPicsNum = pictureNums[i];
		testReadImages(currentPicsNum);
		m_os << std::endl;
	}
}

void ReadImage::testReadImages(int pictureNum)
{
	assert(pictureNum <= m_maxPicNums);
	m_os << "Test reading " << pictureNum << " images:\n";

	double interval;

	for (int threadsNum = 1; threadsNum <= m_maxThreads; ++threadsNum)
	{
		interval = readImagesWithThreads(pictureNum, threadsNum);
		m_os << "current thread num : " << threadsNum << " cost time: " << interval << "\n";
	}
}



void ReadImage::initFilenames()
{
	auto it = m_filenames.begin();
	int currentNo = 7;
	while (it != m_filenames.end())
	{
		char strNo[4] = { 0 };
		translateIntToChar(currentNo,strNo, 4);
		sprintf_s(*it, "E:/HuaShanPics/DSC_J1_00%s.JPG", strNo);
		++it;
		++currentNo;
	}
}

void ReadImage::initOstream()
{
	m_os << std::setw(10) << std::setprecision(10);
}

double ReadImage::readImagesWithThreads(int imagesNum, int threadsNum)
{
	assert(threadsNum <= m_maxThreads && imagesNum >= 1);

	const unsigned long blockSize = imagesNum / threadsNum;
	const unsigned long lastBlockSize = imagesNum - blockSize * (threadsNum - 1);

	std::vector<std::thread> threads(threadsNum - 1);

	auto imageBeginIt = m_mats.begin();
	auto fileBeginIt = m_filenames.begin();
	auto threadIt = threads.begin();

	clock_t beginTime = clock();

	if (threadsNum != 1)
	{
		while (threadIt != threads.end())
		{
			*threadIt = std::thread(readImages, imageBeginIt, fileBeginIt, blockSize);

			std::advance(imageBeginIt, blockSize);
			std::advance(fileBeginIt, blockSize);

			++threadIt;
		}
	}

	readImages(imageBeginIt, fileBeginIt, lastBlockSize);

	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

	clock_t endTime = clock();
	double interval = static_cast<double>(endTime - beginTime) / CLOCKS_PER_SEC;

	return interval;
}

void ReadImage::testVecImage()
{
	clock_t beginTime = clock();
	auto it = m_mats.begin();
	clock_t middleTime = clock();
	*it = cv::imread("../../../HuaShanPics/DSC_J1_00007.JPG");
	clock_t endTime = clock();

	double interval1 = static_cast<double>(middleTime - beginTime) / CLOCKS_PER_SEC;
	double interval2 = static_cast<double>(endTime - middleTime) / CLOCKS_PER_SEC;

	m_os << "testVecImage result :\n" << interval1 << "    " << interval2 << "\n" << std::endl;
}

void translateIntToChar(int num, char str[],int len)
{
	str[--len] = '\0';
	while (num > 0)
	{
		str[--len] = num % 10 + '0';
		num /= 10;
	}
	while (len != 0)
		str[--len] = '0';
}

void readImages(std::vector<cv::Mat>::iterator imageBeginIt, std::vector<char[100]>::iterator fileBeginIt, int size)
{
	int curNo = 1;
	while (curNo <= size)
	{
		*imageBeginIt = cv::imread(*fileBeginIt);
		++imageBeginIt;
		++fileBeginIt;
		++curNo;
	}
}

