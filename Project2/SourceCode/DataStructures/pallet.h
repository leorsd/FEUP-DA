#ifndef PALLET_H
#define PALLET_H

/**
 * @file pallet.h
 * @brief Definition of the Pallet structure.
 * 
 * @details This file contains the definition of the Pallet structure, which is used to represent pallet data.
 */

/**
 * @brief Structure representing a pallet.
 * 
 * @details The Pallet structure contains information about the pallet's id, weight, and profit.
 */
struct Pallet{
    int id;
    int weight;
    int profit;
};

#endif
