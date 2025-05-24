#ifndef STRUCTS_H
#define STRUCTS_H

/**
 * @file truck.h
 * @brief Definition of truck structures used in the project.
 * 
 * @details This file contains the definition of the Truck structure, which is used to represent truck data.
 */


/**
 * @brief Structure representing a truck.
 * 
 * @details The Truck structure contains information about the truck's capacity and the number of available pallets.
 */
struct Truck{
    int capacity;
    int availablePallets;
};
 
#endif