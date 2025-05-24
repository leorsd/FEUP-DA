#include "truck.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

/**
 * @file loadTruck.h
 * @brief Function declaration for loading truck data from a CSV file.
 * 
 * @details This file contains the function declaration for reading truck data from a CSV file and populating the Truck structure. 
 * The corresponding function implementation is in loadTruck.cpp.
 */

/**
 * @brief Loads truck data from a CSV file.
 * 
 * @param choice The datset choice.
 * @param truck Reference to the Truck structure to be populated.
 * @return true if the truck data was loaded successfully, false otherwise.
 */
bool loadTruck(int choice, Truck& truck);