//
//  flatSetTesting.h
//  Project_flat_set
//
//  Created by Veronika Kravchenko on 06/06/2022.
//

#pragma once

#include "flatSet.h"
#include <set>
//TODO: move iostream and algorithm into the cpp file once done separating definition from declaration

namespace testing{

void checkFlatSet(const flatSet& toTest, const std::set<int>& prediction);

void checkFind(const flatSet& toFindIn, const int& toFind);

void checkInsert(flatSet& toInsertInto, const int& toInsert);

//void checkClear(flatSet& toClear);

//void checkErase(flatSet& toEraseFrom, const int& toErase);
}
