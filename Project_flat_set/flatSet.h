//
//  flatSet.h
//  Project_flat_set
//
//  Created by Veronika Kravchenko on 26/05/2022.
//

#pragma once

#include <stdexcept>
#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>

class flatSet{
    private:
    // a flat set is a sorted vector
    //INVARIANT - sorted list
    std::vector<int> m_fs;
    
    //remove duplicates
    void makeUnique() {
        //does not alter the size of the vector, just moves duplicates to the end
        // returns the iterator to one-past the last unique element in the vector
        auto it = std::unique (m_fs.begin(), m_fs.end());
        //removes the duplicates by resizing the vector
        m_fs.resize( std::distance(m_fs.begin(),it) );
        
    }
    
    public:
    using const_iterator = std::vector<int>::const_iterator;
    //default constructor
    flatSet() = default;
    //user-defined constructor
    // TODO: decide whether it is desirable for this constructor to be explicit
    // since we are giving
    //TODO: refactor the constructors to remove duplicate code (add to the unique private function perhaps)
    flatSet(std::vector<int> f)
    : m_fs{std::move(f)} //member initialisation using move semantics
        {
            // invariant - sort the vector by default
            std::sort(m_fs.begin(), m_fs.end());
            // remove duplicate elements
            makeUnique();
        }
    
    //constructor with initialiser list (intrinsically const)
    flatSet(std::initializer_list<int> fi)
        : m_fs{fi} //member initialization
        {
            //sort the vector
            std::sort(m_fs.begin(), m_fs.end());
            //call remove duplicate elements
            makeUnique();
        }
    
    //copy constructor
    flatSet(const flatSet&) = default;
    
    //move constructor
    flatSet(flatSet&&) noexcept = default;
    
    //copy assignment
    flatSet& operator=(const flatSet&) = default;
    
    //move assignment
    flatSet& operator=(flatSet&&) noexcept = default;

    //destructor
    ~flatSet() noexcept = default;
    
    //iterators
    // TODO: is it bad or good or neutral to have non-const iterators for this class?
    // ^ take a look at this from a tester's perspective - always wanting for code to break
    [[nodiscard]]
    auto begin() const noexcept{
        return m_fs.begin();
    }
    
    [[nodiscard]]
    auto end() const noexcept{
        return m_fs.end();
    }

    //  empty - test whether the container is empty
    bool empty() const {
        return m_fs.empty();
    }
    //  size - return container size
    //modular arithmetic with unsigned integers
    // wraparound behaviour i.e. 1-2 != -1, but instead the max value of an unsigned int - 1
    // If an unsigned value is out of range, it is divided by one greater than the largest number of the type,
    //  and only the remainder kept.
    std::size_t size() const {
        return m_fs.size();
    }
    //modifiers
    //  clear -clear content of the flat set
    void clear(){
        m_fs.clear();
    }
    //  insert - insert element (must remain ordered)
    // this insert method will not insert elements that already exist in the flat set
    //TODO: refactor repeating code in insert and find (helper function)
    std::pair<const_iterator, bool> insert(const int &toInsert){
        //O(log n)
        auto it = std::lower_bound(m_fs.begin(), m_fs.end(), toInsert);
        if ((it != m_fs.end()) && (*it == toInsert))
            return { it, false };
        // expensive because the elements to the right of the inserted element need to be moved (or reallocated)
        return { m_fs.insert(it, toInsert), true };
    }
    
    //  erase - erase element(s)
    void erase(int toErase) {
        //use the erase-remove idiom
        // O(n) + O(n) -
        // because the remove moves the elements up after moving the selected element to the end
        // then erases any n-number of elements (in this case one off the end of the vector)
        m_fs.erase(std::remove(m_fs.begin(), m_fs.end(), toErase), m_fs.end());
    }
    
    //lookup
    //  find - get iterator to element (using upper and lower bound)
    // x = element to search
    // lb = lower bound
    // ub = upper bound
    auto find( const int& toFind) const -> const_iterator;
    
    
    //non-member comparisons
    // ==
    [[nodiscard]]
    friend bool operator==(const flatSet& lhs, const flatSet& rhs) = default;
    // !=
    [[nodiscard]]
    friend bool operator!=(const flatSet& lhs, const flatSet& rhs) = default;
    // <
    // ------------- lexicographical comparison ------------
    [[nodiscard]]
    friend bool operator<(const flatSet& lhs, const flatSet& rhs) {
        return lhs.m_fs < rhs.m_fs;
    };
    // <=
    [[nodiscard]]
    friend bool operator<=(const flatSet& lhs, const flatSet& rhs) {
        return lhs.m_fs <= rhs.m_fs;
    };
    // >
    [[nodiscard]]
    friend bool operator>(const flatSet& lhs, const flatSet& rhs) {
        return lhs.m_fs > rhs.m_fs;
    };
    // >=
    [[nodiscard]]
    friend bool operator>=(const flatSet& lhs, const flatSet& rhs) {
        return lhs.m_fs >= rhs.m_fs;
    };
    // <=>
    // ------------ lexicographical three-way comparison ----------
    /*[[nodiscard]]
    friend auto operator<=>(const flatSet& lhs, const flatSet& rhs) = default;*/
    
};
//trailing return type
inline auto flatSet::find( const int& toFind) const -> const_iterator{
    auto it = std::lower_bound(m_fs.begin(), m_fs.end(), toFind);
    if (it == m_fs.end() || (*it != toFind)){
        //element not found
        return m_fs.end();
    }
    //element found
    return it;
}

// debugging duplicates
// do i have #pragma once (or alternative)
// if yes, check for functions which have been both declared and defined and not inline
// (if templated, functions are implicitly inline)