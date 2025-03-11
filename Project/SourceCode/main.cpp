#include <iostream>
#include "loadGraph.h"
#include "batchReader.h"


int askBatchOrMenu(){
    int choice;
    while (true){
        std::cout << "\n--- Route Planner Menu ---\n";
        std::cout << "\n";
        std::cout << "What method you want to use?\n";
        std::cout << "1. Batch Mode (reads from a input.txt)\n";
        std::cout << "2. Menu Mode (user-friendly)\n";
        std::cout << "3. Exit\n";

        std::cout << "Enter Choice: ";
        std::cin >> choice;
        if(choice < 1 || choice > 3){
          std::cout << "Invalid choice, please try again\n";
        }else{
          return choice;
        }
    }

}
int main(){
    Graph graph;
    loadGraph("../Data/Locations.csv", "../Data/Distances.csv", &graph);
    int alg;
    while (true) {
        std::cout << "\n--- Route Planner Menu ---\n";
        std::cout << "\n";
        std::cout << "1. Independent Route Planning\n";
        std::cout << "2. Restricted Route Planning\n";
        std::cout << "3. Best route for driving and walking\n";
        std::cout << "4. Approximate Solution\n";
        std::cout << "5. Exit\n";

        std::cout << "Enter Choice: ";
        std::cin >> alg;
        if (alg == 5){
          break;
        }
        if (alg >= 1 && alg<= 5){

            int mode = askBatchOrMenu();

            if (mode == 3){
              break;
            }

            if (alg == 1 && mode == 1){
              normalBatchReader(&graph);
              break;
            }else if (alg == 1 && mode == 2){
              //Call normal route menu mode
              std::cout << "Normal Menu\n";
            }else if (alg == 2 && mode == 1){
              restrictedBatchReader(&graph);
              break;
            }else if (alg == 2 && mode == 2) {
                // Call restricted menu mode
                std::cout << "Restricted Menu\n";
            }else if (alg == 3 && mode == 1) {
                drivingAndWalkingBatchReader(&graph);
                break;
            }else if (alg == 3 && mode == 2) {
                // Call best route for driving and walking menu mode
                std::cout << "Best Route walk menu\n";
            }else if (alg == 4 && mode == 1) {
                approximateSolutionBatchReader(&graph);
                break;
            }else if (alg == 4 && mode == 2) {
                // Call approximate solution menu mode
                std::cout << "Approximate Solution Menu\n";
            }
        }else{
            std::cout << "Invalid choice, please try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return 0;
}