#include "loadPallets.h"

/**
 * @file loadPallets.cpp
 * @brief Function implementation for loading pallets data from a CSV file.
 * 
 * This file contains the function implementation for the loadPallets function declared in loadPallets.h.
 */

bool loadPallets(int choice, int n_pallets, std::vector<Pallet>& pallets) {
    std::string pallets_filename;

    if ( choice < 10){
        pallets_filename = "../DataSets/Pallets_0" + std::to_string(choice) + ".csv";
    }else{
        pallets_filename = "../DataSets/Pallets_" + std::to_string(choice) + ".csv";
    }

    std::ifstream pallets_file(pallets_filename);

    if (!pallets_file.is_open()) {
        std::cout << "ERROR: Could not find the data file corresponding to the choice " << choice << "." << std::endl;
        return false;
    }

    std::string line;
    std::getline(pallets_file, line); // Skip the first line

    for ( int i = 0; i < n_pallets; i++){

        if (!std::getline(pallets_file, line)){
            std::cout << "ERROR: The file " << pallets_filename << " contains less data than expected." << std::endl;
            return false;
        }

        std::stringstream ss(line);

        Pallet pallet;
        std::getline(ss, line, ',');

        int id;
        try{
            id = std::stoi(line);
        } catch (const std::invalid_argument& e) {
            std::cout << "ERROR: Invalid pallet ID in file " << pallets_filename << ", line "<< i+2 << "." << std::endl;
            return false;
        }

        std::getline(ss, line, ',');

        int weight;
        try{
            weight = std::stoi(line);
        } catch (const std::invalid_argument& e) {
            std::cout << "ERROR: Invalid pallet weight in file " << pallets_filename << ", line "<< i+2 << "." << std::endl;
            return false;
        }

        std::getline(ss, line, ',');

        int profit;
        try{
            profit = std::stoi(line);
        } catch (const std::invalid_argument& e) {
            std::cout << "ERROR: Invalid pallet profit in file " << pallets_filename << ", line "<< i+2 << "." << std::endl;
            return false;
        }

        std::string last;
        ss >> last;
        if (!last.empty()){
            std::cout << "ERROR: The file " << pallets_filename << " contains more data than expected on line " << i+2 << "." << std::endl;
            return false;
        }

        pallet.id = id;
        pallet.weight = weight;
        pallet.profit = profit;
        pallets.push_back(pallet);
    }

    if (std::getline(pallets_file, line)) {
        std::cout << "ERROR: The file " << pallets_filename << " contains more data than expected." << std::endl;
        return false;
    }
    
    pallets_file.close();
    return true;
}