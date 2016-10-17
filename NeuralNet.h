#pragma once
#include "WeightPackages.cpp"
#include "openCLimplementation.cpp"
#include <vector>
#include <iostream>
#include "Timer.cpp"


// Function prototypes
void fillWeights(int numWeightPkgs, double inputDataSize, double numHiddenNeurons, double hiddenBatchSize, double hiddenBatchs, WeightPackages * weights);