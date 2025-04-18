#include "loadTruck.h"

/**
 * @file loadTruck.cpp
 * @brief Function implementation for loading truck data from a CSV file.
 * 
 * This file contains the function implementation for the loadTruck function declared in loadTruck.h.
 */

bool loadTruck(int choice, Truck& truck) {
    std::string truck_filename;

    if ( choice < 10){
        truck_filename = "../DataSets/TruckAndPallets_0" + std::to_string(choice) + ".csv";
    }else{
        truck_filename = "../DataSets/TruckAndPallets_" + std::to_string(choice) + ".csv";
    }

    std::ifstream truck_file(truck_filename);

    if (!truck_file.is_open()) {
        std::cout << "ERROR: Could not find the data file corresponding to the choice " << choice << "." << std::endl;
        return false;
    }

    std::string line;
    std::getline(truck_file, line); //Skip the first line

    if (!std::getline(truck_file, line)){
        std::cout << "ERROR: The file " << truck_filename << " contains less data than expected." << std::endl;
        return false;
    }
    std::stringstream ss(line);

    int capacity;
    int availablePallets;

    std::getline(ss, line, ',');

    try{
        capacity = std::stoi(line);
    } catch (const std::invalid_argument& e) {
        std::cout << "ERROR: Invalid capacity value in file " << truck_filename << std::endl;
        return false;
    }

    std::getline(ss, line, ',');

    try{
        availablePallets = std::stoi(line);
    } catch (const std::invalid_argument& e) {
        std::cout << "ERROR: Invalid available pallets value in file " << truck_filename << std::endl;
        return false;
    }

    if (getline(truck_file, line)){
        std::cout << "ERROR: The file " << truck_filename << " contains more data than expected." << std::endl;
        return false;
    }

    truck.capacity = capacity;
    truck.availablePallets = availablePallets;

    truck_file.close();
    return true;
}