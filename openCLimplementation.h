#pragma once
#include <iostream>
#include <CL/cl.hpp>
#include <fstream>
#include <string>

// Function Prototypes

void getCLinfo();

std::string OpenCLErrorType(int error);

void checkClError(int err, std::string opperation, std::string additionalInfo);

auto getDevice(int platformNumber, int deviceNumber);

auto getDevice();

cl::Program CreateProgram(cl::Device device, const std::string& file);

std::vector<double> mkData(double size, double defaultVal);
