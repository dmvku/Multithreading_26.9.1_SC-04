#pragma once

#include <vector>
#include <thread>

extern const char* outFile;

class Array
{
public:
	Array();
	~Array();

private:
	struct ResultData
	{
		long long result{ 0 };
		int numberOfThreads{ 0 };
		long long summationTime{ 0 };		
	};

	struct ArrayParts
	{
		std::vector <int> arrayPart_;
		long long result{ 0 };
	};

	int numberOfElements_{ 0 };
	int maxValueofElement_{ 0 };
	int maxNumberOfThreads_{ 0 };	
	long long result_{ 0 };
	long long summationTime_{ 0 };

	std::vector <int> mainArray_;
	std::vector <std::thread> threads_;	
	std::vector <ArrayParts> array_;
	std::vector <ResultData> resultData_;

	void startProgramm();
	void selectValue();
	void createArray(int& numberOfElements, int& maxValueofElement);
	void createSubarray(int numberOfThreads);
	void splittingOfTheArray();
	void createThreads();
	void startCalculate();
	void summationInSubarray(ArrayParts& part);
	void joinThreads();	
	void addingResultToData();
	void clearArray();
	void outResult();
};