//
//  flatSetTesting.h
//  Project_flat_set
//
//  Created by Veronika Kravchenko on 06/06/2022.
//

#pragma once

#include "flatSet.h"
#include "flatSetTesting.h"

#include <set>
#include <iostream>
#include <algorithm>

namespace testing{

template <class Key>
void checkFlatSet(const flatSet<Key>& toTest, const std::set<Key>& prediction){
    auto toTestDistance{std::distance(toTest.begin(), toTest.end())};
    auto predictionDistance{std::distance(prediction.begin(), prediction.end())};

    if(toTestDistance == predictionDistance){
        
        //[](){}() - immediately-invoked lambda
        const bool passed = [&toTest, &prediction](){
            auto iterToTest{toTest.begin()};
            auto iterPrediction{prediction.begin()};
            
            for(; iterToTest != toTest.end(); ++iterToTest, ++iterPrediction){
                if(*iterToTest != *iterPrediction){
                    std::cout << "Value mismatch at element " << std::distance(toTest.begin(), iterToTest) << ": predicted " << *iterPrediction << ", actual " << *iterToTest << '\n';
                    return false;
                }
            }
            return true;
        }();
        
        
        if(passed){
            std::cout << "The flat set and the predicted set are the same.\n";
        }
    } else{
        std::cout << "The flat set and the predicted set are not the same size.\n";
    }
}

template <class Key>
void checkFind(const flatSet<Key>& toFindIn, const Key& toFind){
    auto iter = toFindIn.find(toFind);
    bool found = true;
    if (iter == toFindIn.end()){
        found = false;
        std::cout << toFind << " could not be found in this flat set.\n";
    }
    if (found){
        std::cout<< toFind << " is at index " << std::distance(toFindIn.begin(), iter) << " in the flat set.\n";
    }
}

template <class Key>
void checkInsert(flatSet<Key>& toInsertInto, const Key& toInsert){
    const auto [iter, success]{toInsertInto.insert(toInsert)};
    bool insertSuccessful = true;
    if(iter == toInsertInto.end()){
        insertSuccessful = false;
        std::cout << "Inserting element " << toInsert << " unsuccessful.\n";
    }
    if(insertSuccessful){
        std::cout << toInsert << " has been successfully inserted into the flat set at position " << std::distance(toInsertInto.begin(), iter) << ".\n";
    }
    
}

//void checkClear(flatSet& toClear);

//void checkErase(flatSet& toEraseFrom, const int& toErase);
}
