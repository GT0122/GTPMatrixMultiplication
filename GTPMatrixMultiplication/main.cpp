#include "Matrix.h"
#include <iostream>
#include <time.h>
#include <utility>

using namespace std;

#define LENGTH 3000

int main()
{
	double* pF64Data1 = new double[LENGTH * LENGTH];
	double* pF64Data2 = new double[LENGTH * LENGTH];
	double* pF64Result = new double[LENGTH * LENGTH];

	srand((unsigned int)time(NULL));

	CMatrix matLeft, matRight, matResult;
	clock_t start, duration;

	int32_t i32Min = 30000;

	for(int i = 0; i < 10; i++)
	{
		for(int i = 0; i < LENGTH; i++)
		{
			for(int j = 0; j < LENGTH; j++)
			{
				pF64Data1[i * LENGTH + j] = (double)rand() / 1600 - 10;
				pF64Data2[i * LENGTH + j] = (double)rand() / 1600 - 10;
				pF64Result[i * LENGTH + j] = 0;
			}
		}

		matLeft.Create(LENGTH, LENGTH);
		matRight.Create(LENGTH, LENGTH);
		matResult.Create(LENGTH, LENGTH);

		matLeft.Assign(pF64Data1, LENGTH, LENGTH);
		matRight.Assign(pF64Data2, LENGTH, LENGTH);

		start = clock();
		matLeft *= matRight;

		duration = clock() - start;

		std::cout << duration << " ms\n" << endl;

		i32Min = min(i32Min, (int32_t)duration);
	}
	std::cout << "min time : " << i32Min << " ms" << endl;

	delete[] pF64Data1;
	delete[] pF64Data2;
	delete[] pF64Result;

	return 0;
}