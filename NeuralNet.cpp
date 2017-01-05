#include "NeuralNet.h"

int main() {

	// Specifying the dimentions of the network.
	const double inputDataSize = 5.0;
	const double numHiddenNeurons = 5.0;
	const double numOutputDims = 5.0;
	const double hiddenBatchSize = 1000.0;
	const double numWeightPkgs = 10.0;
	const double hiddenBatchs = ceil((inputDataSize*numHiddenNeurons)/hiddenBatchSize);
	std::cout.precision(20);

	// Initalizes a timer object and starts it.
	Timer t;
	t.Start();

	std::cout << "Initalizing network\n";
	std::cout << "  -Generating input data set...\n";

	// Generate input vector
	std::vector<double> input = mkData(inputDataSize,1.0);

	std::cout << "  -Validating hidden weight size input...\n";

	// Throw an error if number of hidden neuron weigths is too high (number of weights > 1,000,000,000)
	if (inputDataSize*numHiddenNeurons > hiddenBatchSize*numWeightPkgs) {
		std::cout << "ERROR: Number of hidden layer weights exceds the max allowable. Please adjust data packaging peramiters.\n";
		std::cout << "Attempted number of hidden weights: " << inputDataSize*numHiddenNeurons <<"\n";
		std::cout << "Allowed number of hidden weights: " << hiddenBatchSize*numWeightPkgs << "\n";
		std::cout << "Press enter to continue...";
		
		std::cin.get();
		exit(1);
	}

	std::cout << "  -Validation sucessfull!\n";
	std::cout << "  -Generating weight packages...\n";

	WeightPackages weights(inputDataSize, numHiddenNeurons, hiddenBatchSize);
	WeightPackages * weightsPtr = &weights;

	// Fill The weight packages as needed and check if they
	fillWeights(numWeightPkgs, inputDataSize, numHiddenNeurons, hiddenBatchSize, hiddenBatchs,weightsPtr);
	
	int actualSize = weights.getSize();









	std::vector<double> a(weights.getNeuron(0));
	weights.printOutNeturon(a,0);

	std::cout << "Computation info:\n";
	std::cout << "Values initalized: " << actualSize + input.size() << "\n";
	std::cout << "Total time elapsed: " << t.Current();
	
	std::cout << "\nPress enter to exit...";
	std::cin.get();
	

	return 0;
}

void fillWeights(int numWeightPkgs,double inputDataSize,double numHiddenNeurons,double hiddenBatchSize, double hiddenBatchs ,WeightPackages * weights) {

	for (int j = 0; j <= numWeightPkgs - 1; j++) {

		std::cout << "    *Generating package: (" << j + 1 << "/"<< (int)hiddenBatchs << ")\n";

		double numLeft = inputDataSize*numHiddenNeurons - j*hiddenBatchSize;

		// Check if the number of weights left is greater than the 
		if (numLeft > hiddenBatchSize) {
			numLeft = hiddenBatchSize;
		}

		// Check if the weight packages have been filled with all of the data.
		if (numLeft <= 0) {
			j = numWeightPkgs;
		}
		else {

			// Resize the current weight package.
			weights->resizePkgs(j, numLeft);
			
			// Create a pointer to the current weight package.
			std::vector<double> * currentPkg = weights->getPkgPtr(j);

			// Swap the initalized data into the current weight package by its pointer.
			currentPkg->swap(mkData(numLeft, 1));

		}
	}

	std::cout << "  -Validating weight package sizes...\n";

	// Check if the packages were filled properly if not throw an error.
	double expectedSize = (inputDataSize*numHiddenNeurons);
	//double actualSize = weightPkg0.size() + weightPkg1.size() + weightPkg2.size() + weightPkg3.size() + weightPkg4.size() + weightPkg5.size() + weightPkg6.size() + weightPkg7.size() + weightPkg8.size() + weightPkg9.size();

	double actualSize = ((weights->getPkg(0))).size() + ((weights->getPkg(1))).size() + ((weights->getPkg(2))).size() + ((weights->getPkg(3))).size() + ((weights->getPkg(4))).size() + ((weights->getPkg(5))).size() + ((weights->getPkg(6))).size() + ((weights->getPkg(7))).size() + ((weights->getPkg(8))).size() + ((weights->getPkg(9))).size();

	if (expectedSize - actualSize != 0) {
		std::cout << "ERROR: Weight packages not sucessfully generated.\n";
		std::cout << "Expected number: " << expectedSize << "\n";
		std::cout << "Actual number: " << actualSize << "\n";
		std::cout << "Press enter to exit...";
		std::cin.get();
		exit(1);
	}
	std::cout << "  -Size validation sucessfull!\n";

}









	 



