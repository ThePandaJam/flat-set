//
//  main.cpp
//  Project_flat_set
//
//  Created by Veronika Kravchenko on 26/05/2022.
//

#include "flatSet.h"
#include "flatSetTesting.h"

#include <iostream>
#include <set>
#include <algorithm>

//TODO: separate code into namespaces, headers and cpp files for clarity

//TODO: why is it safer to use std::distance than size?
//it is safer to calculate distance in the test than assume that size() is implemented correctly

//TODO: play around with command line args
int main(int argc, const char * argv[]) {
    using namespace testing;
    flatSet a{};
    std::cout << "size of flat set a: " << a.size() << '\n';
    std::cout << std::boolalpha;
    std::cout << "distance between beginning and end of a: " << std::distance(a.begin(), a.end()) << '\n';
    std::cout << "Is a empty?: " << a.empty() << '\n';
    std::cout << "a == a: " << (a==a) << '\n';
    std::cout << "a != a: " << (a!=a) << '\n';
    std::cout << "-----------------------------" << '\n';

    flatSet b{42};
    std::cout << "size of flat set b: " << b.size() << '\n';
    std::cout << "distance between beginning and end of b: " << std::distance(b.begin(), b.end()) << '\n';
    std::cout << "Is b empty?: " << b.empty() << '\n';
    std::cout << "b == b: " << (b==b) << '\n';
    std::cout << "b != b: " << (b!=b) << '\n';
    std::cout << "a == b: " << (a==b) << '\n';
    std::cout << "a != b: " << (a!=b) << '\n';
    std::cout << "-----------------------------" << '\n';
    
    //insert 42 into a and compare with b
    checkInsert(a, 42);
    std::cout << "a == b: " << (a==b) << '\n';
    
    //  clear b (would be equal to a) and check
    //b.clear();
    //std::cout << "a == b: " << (a==b) << '\n';
    
    std::cout << "-----------------------------" << '\n';
    
    flatSet c{4, 2};
    flatSet d{2, 3, 4};
    flatSet e{2, 3};
    std::set<int> cSet{2, 4};
    //the set is the same
    checkFlatSet(c, cSet);
    //the sets are not the same size
    checkFlatSet(d, cSet);
    //checking for a single mismatch
    checkFlatSet(e, cSet);
    //checking multiple mismatches in same set
    flatSet f{1, 2, 2, 4, 5, 5, 7};
    std::set<int> fSet{1, 2, 3, 4, 5, 6, 7};
    checkFlatSet(f, fSet);
    
    std::cout << "-----------------------------" << '\n';

    flatSet odds{1, 3, 3, 3, 3, 5, 7};
    flatSet oddsUnique{1, 3, 5, 7};
    std::cout << "odds == oddsUnique: " << (odds==oddsUnique) << '\n';

    checkFind(odds, 3);
    checkFind(odds, 9);

    
    
    return 0;
}
