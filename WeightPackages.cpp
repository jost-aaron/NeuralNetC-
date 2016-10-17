#pragma once
#include <iostream>
#include <vector>
#include <algorithm>


class WeightPackages
{
private:

	double numInputNeurons;
	double numHiddenNeurons;
	double numWeights;
	double numPkgs;
	double weightsPerNeuron;
	std::vector<int> pkgSizes;

	// Member variables
	std::vector<double> weightPkg0;
	std::vector<double> weightPkg1;
	std::vector<double> weightPkg2;
	std::vector<double> weightPkg3;
	std::vector<double> weightPkg4;
	std::vector<double> weightPkg5;
	std::vector<double> weightPkg6;
	std::vector<double> weightPkg7;
	std::vector<double> weightPkg8;
	std::vector<double> weightPkg9;

	

public:
	// Object constructor
	WeightPackages(double inputNeurons,double hiddenNeurons, double weightsPerPackage) {
		numInputNeurons = inputNeurons;
		numHiddenNeurons = hiddenNeurons;
		numWeights = inputNeurons*hiddenNeurons;
		numPkgs = 10;
		pkgSizes.resize(numPkgs);
		weightsPerNeuron = numWeights / numHiddenNeurons;
	};

	// Returns the given weight package
	std::vector<double>  getPkg(int pkgNum){
	
		// DEBUG CODE
		

		// Switch statment to allow the selecting of a weight package based its number.
		switch (pkgNum)
		{

		case 0:
			// create a refference to the weight package and return it.
			return weightPkg0;
		case 1:
			return weightPkg1;
		case 2:
			return weightPkg2;
		case 3:
			return weightPkg3;
		case 4:
			return weightPkg4;
		case 5:
			return weightPkg5;
		case 6:
			return weightPkg6;
		case 7:
			return weightPkg7;
		case 8:
			return weightPkg8;
		case 9:
			return weightPkg9;

		default:
			std::cout << "ERROR: Tried to access a weight package that does not exist!\n";
			std::cout << "Atempted to access pkg: " << pkgNum << "\n";
			std::cout << "Press enter to exit...";
			std::cin.get();
			exit(1);
		}
	}

	// Returns the given weight package
	std::vector<double>  getPkgElements(int pkgNum,int startIndex,int endIndex) {

		std::vector<double> output(endIndex - startIndex);



		// Switch statment to allow the selecting of a weight package based its number.
		switch (pkgNum)
		{

		case 0:
			for (int j = 0; j <= (endIndex - startIndex -1);j++) {
				output[j] = weightPkg0[j + startIndex];
				
			}
			return output;
		case 1:
			for (int j = 0; j <= (endIndex - startIndex - 1); j++) {
				output[j] = weightPkg1[j + startIndex];
				
			}
			return output;
		case 2:
			for (int j = 0; j <= (endIndex - startIndex - 1); j++) {
				output[j] = weightPkg2[j + startIndex];
				
			}
			return output;
		case 3:
			for (int j = 0; j <= (endIndex - startIndex - 1); j++) {
				output[j] = weightPkg3[j + startIndex];
				
			}
			return output;
		case 4:
			for (int j = 0; j <= (endIndex - startIndex - 1); j++) {
				output[j] = weightPkg4[j + startIndex];
				
			}
			return output;
		case 5:
			for (int j = 0; j <= (endIndex - startIndex - 1); j++) {
				output[j] = weightPkg5[j + startIndex];
				
			}
			return output;
		case 6:
			for (int j = 0; j <= (endIndex - startIndex - 1); j++) {
				output[j] = weightPkg6[j + startIndex];
			}
			return output;
		case 7:
			for (int j = 0; j <= (endIndex - startIndex - 1); j++) {
				output[j] = weightPkg7[j + startIndex];
			}
			return output;
		case 8:
			for (int j = 0; j <= (endIndex - startIndex - 1); j++) {
				output[j] = weightPkg8[j + startIndex];
			}
			return output;
		case 9:
			for (int j = 0; j <= (endIndex - startIndex - 1); j++) {
				output[j] = weightPkg9[j + startIndex];
			}
			return output;

		default:
			std::cout << "ERROR: Tried to access a weight package that does not exist!\n";
			std::cout << "Atempted to access pkg: " << pkgNum << "\n";
			std::cout << "Press enter to exit...";
			std::cin.get();
			exit(1);
		}
	}

	// Returns the given weight package
	std::vector<double> * getPkgPtr(int pkgNum) {

		// DEBUG CODE


		// Switch statment to allow the selecting of a weight package based its number.
		switch (pkgNum)
		{

		case 0:
			// create a refference to the weight package and return it.
			return &weightPkg0;
		case 1:
			return &weightPkg1;
		case 2:
			return &weightPkg2;
		case 3:
			return &weightPkg3;
		case 4:
			return &weightPkg4;
		case 5:
			return &weightPkg5;
		case 6:
			return &weightPkg6;
		case 7:
			return &weightPkg7;
		case 8:
			return &weightPkg8;
		case 9:
			return &weightPkg9;

		default:
			std::cout << "ERROR: Tried to access a weight package that does not exist!\n";
			std::cout << "Atempted to access pkg: " << pkgNum << "\n";
			std::cout << "Press enter to exit...";
			std::cin.get();
			exit(1);
		}
	}

	// Resizes the package of number pkgNum and resizes it to size 
	void resizePkgs(int pkgNum,int size) {
		switch (pkgNum)
		{
		case 0: 
			weightPkg0.resize(size);
			pkgSizes[pkgNum] = size;
			break;
		case 1:
			weightPkg1.resize(size);
			pkgSizes[pkgNum] = size;
			break;
		case 2:
			weightPkg2.resize(size);
			pkgSizes[pkgNum] = size;
			break;
		case 3:
			weightPkg3.resize(size);
			pkgSizes[pkgNum] = size;
			break;
		case 4:
			weightPkg4.resize(size);
			pkgSizes[pkgNum] = size;
			break;
		case 5:
			weightPkg5.resize(size);
			pkgSizes[pkgNum] = size;
			break;
		case 6:
			weightPkg6.resize(size);
			pkgSizes[pkgNum] = size;
			break;
		case 7:
			weightPkg7.resize(size);
			pkgSizes[pkgNum] = size;
			break;
		case 8:
			weightPkg8.resize(size);
			pkgSizes[pkgNum] = size;
			break;
		case 9:
			weightPkg9.resize(size);
			pkgSizes[pkgNum] = size;
			break;

		default:
			std::cout << "ERROR: Tried to resize a weight package that does not exist!\n";
			std::cout << "Atempted to resize pkg: " << pkgNum << "\n";
			std::cout << "Press enter to exit...";
			std::cin.get();
			exit(1);
			break;
		}
	}


	// Gets the weights for the neuron of given value
	std::vector<int> locateNeuron(int neuronNum) {

		// Check if the neuron you are trying to access exists.
		if (neuronNum > numHiddenNeurons) {
			std::cout << "ERROR: Trying to access a neuron which does not exist!\n";
			std::cout << "Press enter to exit...";
			std::cin.get();
			exit(1);
		}

		
		
		// Check if the ratio is a whole number.
		if (weightsPerNeuron != double((int)weightsPerNeuron)) {
			std::cout << "ERROR: number of weights/neuron could not be resolved to a whole number!\n";
			std::cout << "Press enter to exit...";
			std::cin.get();
			exit(1);
		}

		// Starting location of the neurons weights
		int sGIndex = weightsPerNeuron*(neuronNum);

	

		int sizeOfPkgs = pkgSizes[0];
		
		// What package it starts in.
		
		int sPkg = floor(sGIndex/(sizeOfPkgs));

		int eGIndex = sGIndex + weightsPerNeuron;

		int ePkg = floor(eGIndex/(sizeOfPkgs));

		int sLIndex = sGIndex - weightsPerNeuron*(sPkg);
		
		int eLIndex;

		if (ePkg == sPkg) {
			eLIndex = sLIndex + weightsPerNeuron;
		}
		else {
			eLIndex = eGIndex - weightsPerNeuron*(ePkg);
		}

		std::vector<int> location(4);

		location[0] = sPkg;
		location[1] = ePkg;
		location[2] = sLIndex;
		location[3] = eLIndex;

		return location;

	}

	std::vector<double> getNeuron(int neuronNum) {

		std::vector<double> c;

		std::vector<int> local = locateNeuron(neuronNum);
		
		int sPkg = local[0];
		int ePkg = local[1];
		int sLoc = local[2];
		int eLoc = local[3];

		if (sPkg == ePkg) {
			return getPkgElements(sPkg,sLoc,eLoc);
		}
		else {
			std::vector<double> a(getPkgElements(sPkg, sLoc, weightsPerNeuron-1));
			std::vector<double> b(getPkgElements(ePkg, 0, eLoc));

			c.insert(c.end(),a.begin(),a.end());
			c.insert(c.end(),b.begin(),b.end());
		}

		return c;

	}

	int getSize() {

		int a = weightPkg0.size();
		a += weightPkg1.size();
		a += weightPkg2.size();
		a += weightPkg3.size();
		a += weightPkg4.size();
		a += weightPkg5.size();
		a += weightPkg6.size();
		a += weightPkg7.size();
		a += weightPkg8.size();
		a += weightPkg9.size();

		return a;

	}

};



