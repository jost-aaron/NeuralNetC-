#pragma once
#include <iostream>
#include <CL/cl.hpp>
#include <conio.h>
#include "openCL.h"
#include <fstream>


class WeightPackage
{

	std::vector<double> weightPkg0();
	std::vector<double> weightPkg1();
	std::vector<double> weightPkg2();
	std::vector<double> weightPkg3();
	std::vector<double> weightPkg4();
	std::vector<double> weightPkg5();
	std::vector<double> weightPkg6();
	std::vector<double> weightPkg7();
	std::vector<double> weightPkg8();
	std::vector<double> weightPkg9();


public:
	WeightPackage();
	~WeightPackage();

private:

};

WeightPackage::WeightPackage()
{
	std::vector<double> weightPkg0(0);
	std::vector<double> weightPkg1(0);
	std::vector<double> weightPkg2(0);
	std::vector<double> weightPkg3(0);
	std::vector<double> weightPkg4(0);
	std::vector<double> weightPkg5(0);
	std::vector<double> weightPkg6(0);
	std::vector<double> weightPkg7(0);
	std::vector<double> weightPkg8(0);
	std::vector<double> weightPkg9(0);
}

WeightPackage::~WeightPackage()
{
}