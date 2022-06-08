//
//  flatSetTesting.cpp
//  Project_flat_set
//
//  Created by Veronika Kravchenko on 07/06/2022.
//

#include "flatSetTesting.h"
#include "flatSet.h"

#include <iostream>
#include <algorithm>

namespace testing {
//using namespace testing;
void checkFlatSet(const flatSet& toTest, const std::set<int>& prediction){
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

void checkFind(const flatSet& toFindIn, const int& toFind){
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

void checkInsert(flatSet& toInsertInto, const int& toInsert){
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
}
