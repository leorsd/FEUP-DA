#include <iostream>
#include <vector>
#include "pallet.h"
#include "truck.h"
#include "loadTruck.h"
#include "loadPallets.h"


int askForDataSet(){
    std::string line;
    std::cout << "\n--- Delivery Truck Pallet Packing Optimization ---\n";
    std::cout << "\n";
    std::cout << "What dataset you want to use? Please enter a number between 1 and 10!\n";

    while (true){
        std::cout << "Enter Choice: ";
        try{
            getline(std::cin, line);
            if ( line.empty()){
                std::cout << "Invalid input! A dataset needs to be chosen, please try again.\n";
            }else{
                int choice = std::stoi(line);
                if (choice < 1 || choice > 10){
                    std::cout << "Invalid input! Please enter a number between 1 and 10, please try again.\n";
                }else{
                    return choice;
                }
            }
        } catch (...){
            std::cout << "You entered a non-integer value, please try again.\n";
        }
    }
}

int main(){

    int choice = askForDataSet();

    Truck truck;
    if (!loadTruck(choice, truck)){
        return 1;
    }

    std::vector<Pallet> pallets;
    if (!loadPallets(choice,truck.availablePallets,pallets)){
        return 1;
    }
    return 0;

}