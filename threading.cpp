#include"threading.h"

#include <iomanip>
#include <iostream>
#include <vector>
#include <thread>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <ctime>

//#include <algorithm>

Array::Array()
{
	selectValue();
	createArray(numberOfElements_, maxValueofElement_);
	startProgramm();
}

Array::~Array()
{

}

void Array::startProgramm()
{	
	for (int numberOfThreads = 1;
		numberOfThreads <= maxNumberOfThreads_;
		numberOfThreads++)
	{
		clearArray();
		createSubarray(numberOfThreads);
		splittingOfTheArray();
		startCalculate();
		addingResultToData();
	}
	outResult();
}

void Array::selectValue()
{
	std::cout << "Select number of elements: ";
	std::cin >> numberOfElements_;
	std::cout << "Select max value of elements: ";
	std::cin >> maxValueofElement_;
	std::cout << "Select number of threads: ";
	std::cin >> maxNumberOfThreads_;	
}

void Array::createArray(int& numberOfElements, int& maxValueofElement)
{
	for (auto i{ 0 }; i < numberOfElements; i++)
		mainArray_.push_back(0 + rand() % abs(maxValueofElement + abs(0)));
}

void Array::createSubarray(int numberOfThreads)
{
	for (int part = 0; part < numberOfThreads; part++)
	{
		ArrayParts subarray;
		array_.push_back(subarray);		
	}
}

void Array::splittingOfTheArray()
{
	int arrayNumber{ 0 };
	for (auto element : mainArray_)
	{
		array_[arrayNumber].arrayPart_.push_back(element);
		arrayNumber++;
		if (arrayNumber == array_.size())
		{
			arrayNumber = 0;
		}
	}
}

void Array::startCalculate()
{
	srand(time(nullptr));
	auto start = std::chrono::high_resolution_clock::now();
	createThreads();
	joinThreads();	
	auto finish = std::chrono::high_resolution_clock::now();
	summationTime_ = (finish - start).count();	
}

void Array::createThreads()
{
	for (auto &element : array_)
	{
		threads_.push_back(std::move(std::thread(
			[this, &element] () { this->summationInSubarray(element); })));
	}
}

void Array::summationInSubarray(ArrayParts& part)
{	
	for (auto element : part.arrayPart_)
	{
		part.result += element;
	}
	result_ += part.result;	
}

void Array::joinThreads()
{
	for (int i{ 0 }; i < array_.size(); i++)
	{
		if (threads_[i].joinable())
		{
			threads_[i].join();
		}			
	}
}

void Array::addingResultToData()
{
	ResultData resultData;
	resultData.result = result_;
	resultData.numberOfThreads = array_.size();
	resultData.summationTime = summationTime_;
	resultData_.push_back(resultData);	
}

void Array::clearArray()
{
	result_ = 0;
	threads_.clear();
	array_.clear();	
}

void Array::outResult()
{	
	std::fstream fileStream(outFile, std::ios::out | std::ios::trunc);

	if (!fileStream.is_open())
	{
		std::fstream fileStream(outFile,
			std::ios::in | std::ios::out | std::ios::app);
	}

	fileStream << "Number of elements: " << numberOfElements_ << "\n";
	std::cout << "Number of elements: " << numberOfElements_ << "\n";
	for (auto &element : resultData_)
	{
		fileStream << "Number of threads: " << element.numberOfThreads
			<< "\t Sum: " << element.result
			<< "\t Time: " << element.summationTime << " ns\n";
		std::cout << "Number of threads: " << element.numberOfThreads
			<< "\t Sum: " << element.result
			<< "\t Time: " << element.summationTime << " ns\n";
	}	

	fileStream.close();
}
