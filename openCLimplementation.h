#pragma once
#include <iostream>
#include "WeightPackages.cpp"
#include <fstream>
#include <string>

// Function Prototypes

void getCLinfo();

std::string OpenCLErrorType(int error);

void checkClError(int err, std::string opperation, std::string additionalInfo);

auto getDevice(int platformNumber, int deviceNumber);

auto getDevice();

clLib::Program CreateProgram(clLib::Device device, const std::string& file);

std::vector<double> mkData(double size, double defaultVal);
