#pragma once
#include "openCLimplementation.h"

// Generates a report on all OpenCL Platforms and Devices on the platform.
void getCLinfo() {
	std::cout << "OpenCL Platform and Device report\n";

	// Creates a list for where we are going to store the platforms we find.
	std::vector<cl::Platform> platforms;

	// Gets the platforms and saves them to platforms list
	cl::Platform::get(&platforms);

	// If platforms is empty then throw an error
	_ASSERT(platforms.size() > 0);

	// Finds the number of platforms on the system and prints it out.
	int numPlatforms = platforms.size();
	std::cout << "==============================================================\n";
	std::cout << "Platforms on this system: " << numPlatforms << "\n";

	// Iterate through all of the platforms
	for (int j = 0; j <= numPlatforms - 1; j++) {

		std::cout << "==============================================================\n";
		std::cout << "Platform (" << j << ")\n";

		// Selects the platform
		auto platform = platforms[j];

		// Creates a list where we can put the devices
		std::vector<cl::Device> devices;

		// Looks for devices on this platform and loads them into the list devices.
		platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

		// Find the number of devices
		int numDevices = devices.size();

		// If the device list is empty throw an error.
		_ASSERT(numDevices > 0);

		// Iterate through all of the devices
		for (int k = 0; k <= numDevices - 1; k++) {
			std::cout << "    - Device (" << k << ")\n";

			auto device = devices[k];

			// Get the device name and print it to console.
			auto type = device.getInfo<CL_DEVICE_NAME>();
			std::cout << "         - Device Name: " << type << "\n";

			// Get device vendor and print it to console.
			auto vendor = device.getInfo<CL_DEVICE_VENDOR>();
			std::cout << "         - Device Vendor: " << vendor << "\n";

			// Get device OpenCL version and print it to console.
			auto version = device.getInfo<CL_DEVICE_VERSION>();
			std::cout << "         - Device OpenCL Version: " << version << "\n";
		}
	}
	std::cout << "==============================================================\n";
	std::cin.get();
	exit(0);


}

// Gets an opencl device object for a opencl device manually found.
auto getDevice(int platformNumber, int deviceNumber) {

	// Creates a list for where we are going to store the platforms we find.
	std::vector<cl::Platform> platforms;

	// Gets the platforms and saves them to platforms list
	cl::Platform::get(&platforms);

	// Creates a list where we can put the devices
	std::vector<cl::Device> devices;

	// Looks for devices on this platform and loads them into the list devices.
	platforms[platformNumber].getDevices(CL_DEVICE_TYPE_ALL, &devices);

	return devices[deviceNumber];

}

// Gets an opencl device object for a opencl device automatically found.
auto getDevice() {

	// Creates a list for where we are going to store the platforms we find.
	std::vector<cl::Platform> platforms;

	// Gets the platforms and saves them to platforms list
	cl::Platform::get(&platforms);

	// Get number of platforms.
	int numPlatforms = platforms.size();

	cl::Device device;

	bool deviceFound = false;

	for (int j = 0; j < numPlatforms; j++) {

		if (deviceFound) {
			return device;
		}

		// Creates a list where we can put the devices
		std::vector<cl::Device> devices;

		// Looks for devices on this platform and loads them into the list devices.
		platforms[j].getDevices(CL_DEVICE_TYPE_ALL, &devices);

		int numDevices = devices.size();

		for (int k = 0; k < numDevices; k++) {

			auto device = devices[k];

			auto vendor = device.getInfo<CL_DEVICE_VENDOR>();

			if (vendor == "Advanced Micro Devices, Inc.") {
				deviceFound = true;
				return device;

			}
			else {
				std::cout << "ERROR: OpenCL device finder failed to find AMD GPU!\n Please manually locate the device.\n";
				std::cout << "Press enter to exit...";
				std::cin.get();
				exit(1);

			}

		}

	}

	std::cout << "ERROR: OpenCL device finder failed to find AMD GPU!\n Please manually locate the device.\n";
	std::cout << "Press enter to exit...";
	std::cin.get();
	exit(1);

}

// Generates a program for for the given opencl device.
cl::Program CreateProgram(cl::Device device, const std::string& file) {

	// Open up a new device context.
	cl::Context context({ device });

	// Define a new source.
	cl::Program::Sources sources;

	// Kernel files directory name.
	std::string KernelDir = "KernelFiles/";

	// Kernel to run.
	std::string SourceTextName = file;

	// Adds in directory to path of kernel file.
	SourceTextName = KernelDir + SourceTextName;

	// Load the kernal file from a .cl;
	std::ifstream inputClSource(SourceTextName);

	// If ifstream could not open the file throw an error;
	if (!inputClSource) {
		std::cout << "ERROR: Kernel Module could not be loaded from .cl file.\n";
		std::cout << "Press enter to exit...";
		std::cin.get();
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
		std::cin.get();
		exit(1);
	}

	return program;
}

// Creates and initalizes an array of given size and value.
std::vector<double> mkData(double size, double defaultVal) {

	//auto device = getDevice(0, 1);
	auto device = getDevice();
	cl::Program program = CreateProgram(device, "mkData.cl");
	auto context = program.getInfo<CL_PROGRAM_CONTEXT>();

	std::vector<double> vec(size);

	int err = 0;
	cl::Buffer inBuf(context, CL_MEM_READ_ONLY | CL_MEM_HOST_NO_ACCESS | CL_MEM_COPY_HOST_PTR, sizeof(double)*vec.size(), vec.data(), &err);
	checkClError(err, "creating input buffer", "NONE");
	cl::Buffer outBuf(context, CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY, sizeof(double)*vec.size(), nullptr, &err);
	checkClError(err, "creating output buffer", "NONE");
	cl::Kernel kernel(program, "opp");
	checkClError(err, "initalizing a kernel", "NONE");

	err = kernel.setArg(0, inBuf);
	checkClError(err, "setting kernel argument 0", "NONE");
	err = kernel.setArg(1, outBuf);
	checkClError(err, "setting kernel argument 1", "NONE");

	cl::CommandQueue queue(context, device);

	err = queue.enqueueFillBuffer(inBuf, defaultVal, 0, sizeof(double)*(vec.size()));
	checkClError(err, "adding enqueueFillBuffer to the CommandQueue", std::to_string(defaultVal));

	err = queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(vec.size()));
	checkClError(err, "adding enqueueNDRangeKernel to the CommandQueue", "NONE");
	err = queue.enqueueReadBuffer(outBuf, CL_TRUE, 0, sizeof(double)*vec.size(), vec.data());
	checkClError(err, "adding enqueueReadBuffer to the CommandQueue", "NONE");

	queue.finish();

	return vec;

}

// Resolves a opencl error code to its verbose string value.
std::string OpenCLErrorType(int error) {

	switch (error) {
		// run-time and JIT compiler errors
	case 0: return "CL_SUCCESS";
	case -1: return "CL_DEVICE_NOT_FOUND";
	case -2: return "CL_DEVICE_NOT_AVAILABLE";
	case -3: return "CL_COMPILER_NOT_AVAILABLE";
	case -4: return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
	case -5: return "CL_OUT_OF_RESOURCES";
	case -6: return "CL_OUT_OF_HOST_MEMORY";
	case -7: return "CL_PROFILING_INFO_NOT_AVAILABLE";
	case -8: return "CL_MEM_COPY_OVERLAP";
	case -9: return "CL_IMAGE_FORMAT_MISMATCH";
	case -10: return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
	case -11: return "CL_BUILD_PROGRAM_FAILURE";
	case -12: return "CL_MAP_FAILURE";
	case -13: return "CL_MISALIGNED_SUB_BUFFER_OFFSET";
	case -14: return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
	case -15: return "CL_COMPILE_PROGRAM_FAILURE";
	case -16: return "CL_LINKER_NOT_AVAILABLE";
	case -17: return "CL_LINK_PROGRAM_FAILURE";
	case -18: return "CL_DEVICE_PARTITION_FAILED";
	case -19: return "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";

		// compile-time errors
	case -30: return "CL_INVALID_VALUE";
	case -31: return "CL_INVALID_DEVICE_TYPE";
	case -32: return "CL_INVALID_PLATFORM";
	case -33: return "CL_INVALID_DEVICE";
	case -34: return "CL_INVALID_CONTEXT";
	case -35: return "CL_INVALID_QUEUE_PROPERTIES";
	case -36: return "CL_INVALID_COMMAND_QUEUE";
	case -37: return "CL_INVALID_HOST_PTR";
	case -38: return "CL_INVALID_MEM_OBJECT";
	case -39: return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
	case -40: return "CL_INVALID_IMAGE_SIZE";
	case -41: return "CL_INVALID_SAMPLER";
	case -42: return "CL_INVALID_BINARY";
	case -43: return "CL_INVALID_BUILD_OPTIONS";
	case -44: return "CL_INVALID_PROGRAM";
	case -45: return "CL_INVALID_PROGRAM_EXECUTABLE";
	case -46: return "CL_INVALID_KERNEL_NAME";
	case -47: return "CL_INVALID_KERNEL_DEFINITION";
	case -48: return "CL_INVALID_KERNEL";
	case -49: return "CL_INVALID_ARG_INDEX";
	case -50: return "CL_INVALID_ARG_VALUE";
	case -51: return "CL_INVALID_ARG_SIZE";
	case -52: return "CL_INVALID_KERNEL_ARGS";
	case -53: return "CL_INVALID_WORK_DIMENSION";
	case -54: return "CL_INVALID_WORK_GROUP_SIZE";
	case -55: return "CL_INVALID_WORK_ITEM_SIZE";
	case -56: return "CL_INVALID_GLOBAL_OFFSET";
	case -57: return "CL_INVALID_EVENT_WAIT_LIST";
	case -58: return "CL_INVALID_EVENT";
	case -59: return "CL_INVALID_OPERATION";
	case -60: return "CL_INVALID_GL_OBJECT";
	case -61: return "CL_INVALID_BUFFER_SIZE";
	case -62: return "CL_INVALID_MIP_LEVEL";
	case -63: return "CL_INVALID_GLOBAL_WORK_SIZE";
	case -64: return "CL_INVALID_PROPERTY";
	case -65: return "CL_INVALID_IMAGE_DESCRIPTOR";
	case -66: return "CL_INVALID_COMPILER_OPTIONS";
	case -67: return "CL_INVALID_LINKER_OPTIONS";
	case -68: return "CL_INVALID_DEVICE_PARTITION_COUNT";

		// extension errors
	case -1000: return "CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR";
	case -1001: return "CL_PLATFORM_NOT_FOUND_KHR";
	case -1002: return "CL_INVALID_D3D10_DEVICE_KHR";
	case -1003: return "CL_INVALID_D3D10_RESOURCE_KHR";
	case -1004: return "CL_D3D10_RESOURCE_ALREADY_ACQUIRED_KHR";
	case -1005: return "CL_D3D10_RESOURCE_NOT_ACQUIRED_KHR";
	default: return "Unknown OpenCL error";
	}
}

// Checks for opencl errors and provides information about the error.
void checkClError(int err, std::string opperation, std::string additionalInfo) {
	if (err != 0) {
		std::cout << "ERROR: An OpenCL error has occured!\n";
		std::cout << "ERROR DISCRIPTION: This error occured when OpenCL was " << opperation << ".\n";
		std::cout << "Error: " << err << " (" << OpenCLErrorType(err) << ")\n";
		std::cout << "ADDITIONAL DEBUG DATA: " << additionalInfo << ".\n";
		std::cout << "Press enter to exit...";
		std::cin.get();
		exit(1);
	}
}