
#pragma once
#include <iostream>
#include <CL/cl.hpp>
#include <conio.h>
#include "openCL.h"
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>

void openCLExample() {

	// Get the computing device;
	auto device = getDevice(0, 0);

	std::cout << "Using device: " << device.getInfo<CL_DEVICE_NAME>() << "\n";

	// Open up a new device context.
	cl::Context context({ device });

	// Define a new source.
	cl::Program::Sources sources;

	// Kernel files directory name.
	std::string KernelDir = "KernelFiles/";

	// Kernel to run.
	std::string SourceTextName = "mult2.cl";

	// Adds in directory to path of kernel file.
	SourceTextName = KernelDir + SourceTextName;

	// Load the kernal file from a .cl;
	std::ifstream inputClSource(SourceTextName);

	// If ifstream could not open the file throw an error;
	if (!inputClSource) {
		std::cout << "ERROR: Kernel Module could not be loaded from .cl file.\n";
		std::cout << "Press enter to exit...";
		getch();
		exit(1);
	}

	// Read through the file and copy each char into the kernel code string.
	std::string kernel_code(std::istreambuf_iterator<char>(inputClSource), (std::istreambuf_iterator<char>()));

	// Push the kernel code to the program sources object.
	sources.push_back({ std::make_pair(kernel_code.c_str(),kernel_code.length()) });

	// Initalize a new program object.
	cl::Program program(context, sources);

	// Try to build the program and if it fails throw an error;
	if (program.build({ device }) != CL_SUCCESS) {
		std::cout << "Error occured while building kernel code: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device) << "\n";
		std::cout << "Press enter to exit...";
		getch();
		exit(1);
	}

	// create buffers on the device
	cl::Buffer buffer_A(context, CL_MEM_READ_WRITE, sizeof(int) * 10);
	cl::Buffer buffer_B(context, CL_MEM_READ_WRITE, sizeof(int) * 10);
	cl::Buffer buffer_C(context, CL_MEM_READ_WRITE, sizeof(int) * 10);

	// Input data
	int A[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int B[] = { 0, 1, 2, 0, 1, 2, 0, 1, 2, 0 };

	//create queue to which we will push commands for the device.
	cl::CommandQueue queue(context, device);

	//write arrays A and B to the device
	queue.enqueueWriteBuffer(buffer_A, CL_TRUE, 0, sizeof(int) * 10, A);
	queue.enqueueWriteBuffer(buffer_B, CL_TRUE, 0, sizeof(int) * 10, B);

	//Run the kernel
	cl::Kernel kernel_add = cl::Kernel(program, "opp");
	kernel_add.setArg(0, buffer_A);
	kernel_add.setArg(1, buffer_B);
	kernel_add.setArg(2, buffer_C);
	queue.enqueueNDRangeKernel(kernel_add, cl::NullRange, cl::NDRange(10), cl::NullRange);
	queue.finish();

	// Initalize a buffer to dump results into.
	int C[10];

	//read result C from the device to array C
	queue.enqueueReadBuffer(buffer_C, CL_TRUE, 0, sizeof(int) * 10, C);

	std::cout << " result: \n";
	for (int i = 0; i<10; i++) {
		std::cout << C[i] << " ";
	}



}

float* openCLMakeInputData(int platformNum, int deviceNum, int size, int initVal) {

	// Get the computing device;
	auto device = getDevice(platformNum, deviceNum);

	std::cout << "Using device: " << device.getInfo<CL_DEVICE_NAME>() << "\n";

	// Open up a new device context.
	cl::Context context({ device });

	// Define a new source.
	cl::Program::Sources sources;

	// Kernel files directory name.
	std::string KernelDir = "KernelFiles/";

	// Kernel to run.
	std::string SourceTextName = "mkData.cl";

	// Adds in directory to path of kernel file.
	SourceTextName = KernelDir + SourceTextName;

	// Load the kernal file from a .cl;
	std::ifstream inputClSource(SourceTextName);

	// If ifstream could not open the file throw an error;
	if (!inputClSource) {
		std::cout << "ERROR: Kernel Module could not be loaded from .cl file.\n";
		std::cout << "Press enter to exit...";
		getch();
		exit(1);
	}

	// Read through the file and copy each char into the kernel code string.
	std::string kernel_code(std::istreambuf_iterator<char>(inputClSource), (std::istreambuf_iterator<char>()));

	// Push the kernel code to the program sources object.
	sources.push_back({ std::make_pair(kernel_code.c_str(),kernel_code.length()) });

	// Initalize a new program object.
	cl::Program program(context, sources);

	// Try to build the program and if it fails throw an error;
	if (program.build({ device }) != CL_SUCCESS) {
		std::cout << "Error occured while building kernel code: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device) << "\n";
		std::cout << "Press enter to exit...";
		getch();
		exit(1);
	}

	float outputSize = size;

	// create buffers on the device
	cl::Buffer buffer_A(context, CL_MEM_READ_WRITE, sizeof(int));
	cl::Buffer buffer_C(context, CL_MEM_READ_WRITE, sizeof(int) * outputSize);

	// Input data
	int A[]{ initVal };


	//create queue to which we will push commands for the device.
	cl::CommandQueue queue(context, device);

	//write arrays A to the device
	queue.enqueueWriteBuffer(buffer_A, CL_TRUE, 0, sizeof(int), A);


	//Run the kernel
	cl::Kernel kernel_add = cl::Kernel(program, "opp");
	kernel_add.setArg(0, buffer_A);
	kernel_add.setArg(1, buffer_C);

	queue.enqueueNDRangeKernel(kernel_add, cl::NullRange, cl::NDRange(outputSize), cl::NullRange);
	queue.finish();

	// Initalize a buffer to dump results into.
	float *C = new float[outputSize];

	//read result C from the device to array C
	queue.enqueueReadBuffer(buffer_C, CL_TRUE, 0, sizeof(int) * outputSize, C);

	//std::cout << " result: \n";

	//std::wcout << "Size of input data set: " << sizeof(C) / sizeof(*C) << "\n";
	//for (int i = 0; i<100; i++) {
	//std::cout << C[i] << " ";
	//}

	return C;


}

// Compute c = a + b.
static const char source[] =
"kernel void add(\n"
"       ulong n,\n"
"       global const double *a,\n"
"       global const double *b,\n"
"       global double *c\n"
"       )\n"
"{\n"
"    size_t i = get_global_id(0);\n"
"    if (i < n) {\n"
"       c[i] = a[i] + b[i];\n"
"    }\n"
"}\n";

int main1() {
	const size_t N = 1 << 20;

	try {
		// Get list of OpenCL platforms.
		std::vector<cl::Platform> platform;
		cl::Platform::get(&platform);

		if (platform.empty()) {
			std::cerr << "OpenCL platforms not found." << std::endl;
			return 1;
		}

		// Get first available GPU device which supports double precision.
		cl::Context context;
		std::vector<cl::Device> device;
		for (auto p = platform.begin(); device.empty() && p != platform.end(); p++) {
			std::vector<cl::Device> pldev;

			try {
				p->getDevices(CL_DEVICE_TYPE_GPU, &pldev);

				for (auto d = pldev.begin(); device.empty() && d != pldev.end(); d++) {
					if (!d->getInfo<CL_DEVICE_AVAILABLE>()) continue;

					std::string ext = d->getInfo<CL_DEVICE_EXTENSIONS>();

					if (
						ext.find("cl_khr_fp64") == std::string::npos &&
						ext.find("cl_amd_fp64") == std::string::npos
						) continue;

					device.push_back(*d);
					context = cl::Context(device);
				}
			}
			catch (...) {
				device.clear();
			}
		}

		if (device.empty()) {
			std::cerr << "GPUs with double precision not found." << std::endl;
			return 1;
		}

		std::cout << device[0].getInfo<CL_DEVICE_NAME>() << std::endl;

		// Create command queue.
		cl::CommandQueue queue(context, device[0]);

		// Compile OpenCL program for found device.
		cl::Program program(context, cl::Program::Sources(
			1, std::make_pair(source, strlen(source))
			));

		try {
			program.build(device);
		}
		catch (const cl::Error&) {
			std::cerr
				<< "OpenCL compilation error" << std::endl
				<< program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device[0])
				<< std::endl;
			return 1;
		}

		cl::Kernel add(program, "add");

		// Prepare input data.
		std::vector<double> a(N, 1);
		std::vector<double> b(N, 2);
		std::vector<double> c(N);

		// Allocate device buffers and transfer input data to device.
		cl::Buffer A(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
			a.size() * sizeof(double), a.data());

		cl::Buffer B(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
			b.size() * sizeof(double), b.data());

		cl::Buffer C(context, CL_MEM_READ_WRITE,
			c.size() * sizeof(double));

		// Set kernel parameters.
		add.setArg(0, static_cast<cl_ulong>(N));
		add.setArg(1, A);
		add.setArg(2, B);
		add.setArg(3, C);

		// Launch kernel on the compute device.
		queue.enqueueNDRangeKernel(add, cl::NullRange, N, cl::NullRange);

		// Get result back to host.
		queue.enqueueReadBuffer(C, CL_TRUE, 0, c.size() * sizeof(double), c.data());

		// Should get '3' here.
		std::cout << c[42] << std::endl;
	}
	catch (const cl::Error &err) {
		std::cerr
			<< "OpenCL error: "
			<< err.what() << "(" << err.err() << ")"
			<< std::endl;
		return 1;
	}

	getch();
}


int main3() {
	//get all platforms (drivers)
	std::vector<cl::Platform> all_platforms;
	cl::Platform::get(&all_platforms);
	if (all_platforms.size() == 0) {
		std::cout << " No platforms found. Check OpenCL installation!\n";
		exit(1);
	}
	cl::Platform default_platform = all_platforms[1];
	std::cout << "Using platform: " << default_platform.getInfo<CL_PLATFORM_NAME>() << "\n";

	//get default device of the default platform
	std::vector<cl::Device> all_devices;
	default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
	if (all_devices.size() == 0) {
		std::cout << " No devices found. Check OpenCL installation!\n";
		exit(1);
	}
	cl::Device default_device = all_devices[0];
	std::cout << "Using device: " << default_device.getInfo<CL_DEVICE_NAME>() << "\n";


	cl::Context context({ default_device });

	cl::Program::Sources sources;

	// kernel calculates for each element C=A+B
	std::string kernel_code =
		"   void kernel simple_add(global const int* A, global const int* B, global int* C){       "
		"       C[get_global_id(0)]=A[get_global_id(0)]+B[get_global_id(0)];                 "
		"   }                                                                               ";
	sources.push_back({ kernel_code.c_str(),kernel_code.length() });

	cl::Program program(context, sources);

	if (program.build({ default_device }) != CL_SUCCESS) {
		std::cout << " Error building: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device) << "\n";
		exit(1);
	}


	// create buffers on the device
	cl::Buffer buffer_A(context, CL_MEM_READ_WRITE, sizeof(int) * 10);
	cl::Buffer buffer_B(context, CL_MEM_READ_WRITE, sizeof(int) * 10);
	cl::Buffer buffer_C(context, CL_MEM_READ_WRITE, sizeof(int) * 10);

	int A[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int B[] = { 0, 1, 2, 0, 1, 2, 0, 1, 2, 0 };

	//create queue to which we will push commands for the device.
	cl::CommandQueue queue(context, default_device);

	//write arrays A and B to the device
	queue.enqueueWriteBuffer(buffer_A, CL_TRUE, 0, sizeof(int) * 10, A);
	queue.enqueueWriteBuffer(buffer_B, CL_TRUE, 0, sizeof(int) * 10, B);


	//run the kernel
	//	cl::KernelFunctor simple_add(cl::Kernel(program, "simple_add"), queue, cl::NullRange, cl::NDRange(10), cl::NullRange);
	//simple_add(buffer_A, buffer_B, buffer_C);

	//alternative way to run the kernel
	cl::Kernel kernel_add = cl::Kernel(program, "simple_add");
	kernel_add.setArg(0, buffer_A);
	kernel_add.setArg(1, buffer_B);
	kernel_add.setArg(2, buffer_C);
	queue.enqueueNDRangeKernel(kernel_add, cl::NullRange, cl::NDRange(10), cl::NullRange);
	queue.finish();

	int C[10];
	//read result C from the device to array C
	queue.enqueueReadBuffer(buffer_C, CL_TRUE, 0, sizeof(int) * 10, C);

	std::cout << " result: \n";
	for (int i = 0; i<10; i++) {
		std::cout << C[i] << " ";
	}
	std::cout << "Press enter to exit...";
	getch();
	return 0;
}

