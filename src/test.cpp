#define BOOST_DISABLE_ASSERTS 
#include "boost/multi_array.hpp"
#include "mkl.h"
#include <iostream>
#include "arrays.hpp"
#include <iomanip>
#include <blitz/array.h>
int main(int argc, char* argv[])
{
const int X_SIZE = atoi(argv[1]);
const int Y_SIZE = atoi(argv[2]);
const int ITERATIONS = atoi(argv[3]);
double startTime;
double endTime;
MKL_INT64 alloc_bytes;
int alloc_buffers;


	typedef boost::multi_array<double, 2> ArrayType;
	ArrayType boostMatrix(boost::extents[X_SIZE][Y_SIZE]);

	mkl_peak_mem_usage(MKL_PEAK_MEM_ENABLE);

	double *nativeMatrix = new double[X_SIZE*Y_SIZE];
	MAT2D<double> test_array(X_SIZE, Y_SIZE);
	startTime = dsecnd();

	for (int i = 0; i < ITERATIONS; ++i)
		for (int x = 0; x < X_SIZE; ++x)
	    		for (int y = 0; y < Y_SIZE; ++y)
				boostMatrix[x][y] = 2.345;

	endTime = dsecnd();
	std::cout << std::setprecision(8) << std::fixed << "Boost elapsed time is : " << (endTime - startTime) << std::endl;

	alloc_bytes = mkl_mem_stat(&alloc_buffers);
	std::cout << "Size of array is " << test_array.size() << " GB" << std::endl;
	startTime = dsecnd();
	for (int i = 0; i < ITERATIONS; ++i)
		for (int y = 0; y < Y_SIZE; ++y)
	    		for (int x = 0; x < X_SIZE; ++x)
				test_array.data[y][x] = 2.345;
				
	std::cout << "Peak memory usage is " << mkl_peak_mem_usage(MKL_PEAK_MEM) << std::endl;
	endTime = dsecnd();
	mkl_peak_mem_usage(MKL_PEAK_MEM_RESET);
	test_array.resize(500,500);
	std::cout << "Peak memory usage is " << mkl_peak_mem_usage(MKL_PEAK_MEM) << std::endl;
	std::cout << "Size of array is " << test_array.size() << " GB" << std::endl; 
	std::cout << "Size in x-direction is " << test_array.sizex << " Size in Y-Direction is " << test_array.sizey << std::endl;
	std::cout << "Value is " << test_array.data[X_SIZE-1][Y_SIZE-1] << std::endl;
	std::cout << std::setprecision(8) << std::fixed << "CSN malloc elapsed time is : " << (endTime - startTime) << std::endl;
	blitz::Array<double, 2> blitzArray( X_SIZE, Y_SIZE );

    	startTime = dsecnd();
    	for (int i = 0; i < ITERATIONS; ++i)
        	for (int y = 0; y < Y_SIZE; ++y)
            		for (int x = 0; x < X_SIZE; ++x)
                		blitzArray(x,y) = 2.345;
	endTime = dsecnd();

	endTime = dsecnd(); //::GetTickCount();
	std::cout << std::setprecision(8) << std::fixed << "blitz elapsed time is : " << (endTime - startTime) << std::endl;
return 0;
}
