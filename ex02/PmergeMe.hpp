/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaury <amaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:19:16 by amblanch          #+#    #+#             */
/*   Updated: 2026/01/25 21:43:49 by amaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <sstream>
#include <algorithm>
#include <limits>

void                parsingInt(std::string input);
int                 convertStringToInt(std::string value);
float               convertStringToFloat(std::string value);
long long           convertStringToLongLong(std::string value);


/// @brief PmergeMe sort list of element
/// @tparam FordJohnson type of the container and the type of element for the stack, exemple : std::vector<int> or std::deque<float>
/// @tparam Jacobsthal type of the container for the list of Jacobsthal, exemple : std::vector<int>
template<typename FordJohnson, typename Jacobsthal>
class PmergeMe {
    private:
        typedef typename FordJohnson::value_type value_type;
        
        /// @brief is the list of Jacobsthal
        Jacobsthal      jacobList;
        /// @brief is the list of elements to sort
        FordJohnson     stack;
        /// @brief is the size of pair in the stack
        int             pairSize;
        
        /// @brief initializes the first three numbers in the list
        void    initJacobList();
        /// @brief add a number of the list
        void    addJacobList();

        void pushstack(const char* s) {
            pushstack_impl(s, value_type());
        }

        void pushstack_impl(const char* s, int) {
            parsingInt(s);
            int v = convertStringToInt(std::string(s));
            stack.push_back(v);
        }

        void pushstack_impl(const char* s, float) {
            float v = convertStringToFloat(std::string(s));
            stack.push_back(v);
        }

        void pushstack_impl(const char* s, std::string) {
            stack.push_back(std::string(s));
        }
        
        void pushstack_impl(const char* s, char *) {
            stack.push_back(s);
        }
        
    public:
        /// @brief Default Constructor
        PmergeMe();
        /// @brief Default Destructor
        ~PmergeMe();
        /// @brief Constructor by copy
        /// @param other the element to copy
        PmergeMe(const PmergeMe<FordJohnson,Jacobsthal> &other);
        /// @brief Constructor by operator '='
        /// @param other the elemnt to copy
        /// @return the new copy
        PmergeMe<FordJohnson,Jacobsthal> &operator=(const PmergeMe<FordJohnson,Jacobsthal> &other);

        /// @brief create the stack of elements to be sorted 
        /// @param argc number of elements
        /// @param argv list of elements
        void                CreateList(int argc, char **argv);
        
        /// @brief launch Ford-Johnson algorithm
        void                fordJohnson();
        /// @brief Check the pair and the next pair 
        /// @param pos the pos of the pair in the stack
        /// @return true if pos < pos - 1 and false if pos > pos -1
        bool                checkPairMax(int pos);
        /// @brief swap the pair pos
        /// @param pos the pos of the pair
        void                swapPair(int pos);
        void                swap(value_type &a, value_type &b);
        
        /**
         * @brief Split the stack of elements following the pattern and use number of Jacobsthal for insert the tmp pair to the main.
         * 
         *  the pattern before: 
         * 
         *  - main: b1 a1 b2 a2 b3 a3 b4
         * 
         *  the pattern after:
         * 
         * - main: b1 a1 a2 a3
         * 
         * - tmp:  b2 b3 b4
         *
         * 
         * @return The reordered stack
         */ 
        void                splitStack();
        /// @brief find the pos for insert the element
        /// @param stack the liste of elements
        /// @param elem the element for search pos
        /// @return the pos found
        int                 binarySearch(FordJohnson stack, value_type elem);
        
        /// @brief add the first pair of src to dst and delete it to src
        /// @param dst list of elements
        /// @param src adress list of elements
        /// @return the dst list
        FordJohnson         addPair(FordJohnson dst, FordJohnson *src);
        /// @brief add the rest of the dst elements from the adress of src and clear src  
        /// @param dst list of elements
        /// @param src adress list of elements
        /// @return the dst list
        FordJohnson         addRes(FordJohnson dst, FordJohnson *src);
        /// @brief insert the src[len] in the pos of the dst elements
        /// @param dst list of elements
        /// @param src adress list of elements
        /// @param pos position to add the elements in dst
        /// @param len position for the dst elements
        /// @return the dst list
        FordJohnson         insertPair(FordJohnson dst, FordJohnson *src, int pos, int len);

        /// @brief print the list of Jacobsthal
        /// @param startInput a starting phrase to personalize
        void                printJacobsthal(std::string startInput);
        /// @brief print the list of elements
        /// @param startInput a starting phrase to personalize
        void                printStack(std::string startInput);
};

template<typename FordJohnson, typename Jacobsthal>
void    PmergeMe<FordJohnson,Jacobsthal>::printStack(std::string startInput) {
    std::cout << startInput;
    for (typename FordJohnson::iterator it = stack.begin(); it != stack.end(); it++)
        std::cout << *it << " "; 
    std::cout << std::endl;
}

template<typename FordJohnson, typename Jacobsthal>
void    PmergeMe<FordJohnson,Jacobsthal>::printJacobsthal(std::string startInput) {
    std::cout << startInput;
    for (typename Jacobsthal::iterator it = jacobList.begin(); it != jacobList.end(); it++)
        std::cout << *it << " "; 
    std::cout << std::endl;
}

template<typename FordJohnson, typename Jacobsthal>
void    PmergeMe<FordJohnson,Jacobsthal>::initJacobList() {
    jacobList.push_back(1);
    jacobList.push_back(3);
    jacobList.push_back(5);
    jacobList.push_back(11);
}

template<typename FordJohnson, typename Jacobsthal>
void    PmergeMe<FordJohnson,Jacobsthal>::addJacobList() {
    typename Jacobsthal::iterator it = jacobList.end();
    it--;
    int value = *it;
    it--;
    value += (*it * 2);
    jacobList.push_back(value);
}

template<typename FordJohnson, typename Jacobsthal>
PmergeMe<FordJohnson,Jacobsthal>::PmergeMe(): pairSize(2) { }
template<typename FordJohnson, typename Jacobsthal>
PmergeMe<FordJohnson,Jacobsthal>::~PmergeMe() {}
template<typename FordJohnson, typename Jacobsthal>
PmergeMe<FordJohnson,Jacobsthal>::PmergeMe(const PmergeMe<FordJohnson,Jacobsthal> &other) {
    this->stack = other.stack;
    this->pairSize = other.pairSize;
    this->jacobList = other.jacobList;
}

template<typename FordJohnson, typename Jacobsthal>
PmergeMe<FordJohnson,Jacobsthal> &PmergeMe<FordJohnson,Jacobsthal>::operator=(const PmergeMe<FordJohnson,Jacobsthal> &other) {
    if (this != &other) {
        this->stack = other.stack;
        this->pairSize = other.pairSize;
        this->jacobList = other.jacobList;
    }
    return (*this);
}

template<typename FordJohnson, typename Jacobsthal>
void    PmergeMe<FordJohnson,Jacobsthal>::CreateList(int argc, char **argv) {
    for (int i = 1; i < argc; i++)
        pushstack(argv[i]);
}

template<typename FordJohnson, typename Jacobsthal>
bool    PmergeMe<FordJohnson,Jacobsthal>::checkPairMax(int pos) {
    int first = pairSize / 2 - 1;
    if (pos + first >= (int)stack.size() || pos + pairSize - 1 >= (int)stack.size())
        return true;
    if (stack[pos + first] > stack[pos + pairSize - 1])
        return (false);
    return (true);
}

template<typename FordJohnson, typename Jacobsthal>
void     PmergeMe<FordJohnson,Jacobsthal>::swap(value_type &a, value_type &b) {
    value_type tmp = a;
    a = b;
    b = tmp;
}

template<typename FordJohnson, typename Jacobsthal>
void    PmergeMe<FordJohnson,Jacobsthal>::swapPair(int pos) {
    int len = pairSize / 2;
    for (int i = 0; i < len; i++)
        swap(stack[pos + i], stack[pos + i + len]);
}

template<typename FordJohnson, typename Jacobsthal>
int     PmergeMe<FordJohnson,Jacobsthal>::binarySearch(FordJohnson stack, value_type elem) {
    FordJohnson nb;
    for (int i = pairSize - 1; i < (int)stack.size(); i += pairSize)
        nb.push_back(stack[i]);
    size_t i = 0;
    for (i = 0; i < nb.size(); i++)
        if (nb[i] > elem) break ;
    return i;
}

template<typename FordJohnson, typename Jacobsthal>
FordJohnson    PmergeMe<FordJohnson,Jacobsthal>::insertPair(FordJohnson dst, FordJohnson *src, int pos, int len) {
    FordJohnson newstack;
    
    for (int i = 0; i < pos; i++)
        newstack = addPair(newstack, &dst);
    for (int i = len - pairSize + 1; i <= len; i++)
        newstack.push_back((*src)[i]);
    for (int i = 0; i < pairSize; i++)
        src->erase(src->begin() + len - i);
    newstack = addRes(newstack, &dst);
    return (newstack);
}

template<typename FordJohnson, typename Jacobsthal>
FordJohnson    PmergeMe<FordJohnson,Jacobsthal>::addPair(FordJohnson dst, FordJohnson *src) {
    if (pairSize > (int)src->size())
        return dst;
    int start;
    for (start = 0; start < pairSize; start++)
        dst.push_back((*src)[start]);
    for (start = start - 1; start >= 0; start--)
        src->erase(src->begin() + start);
    return dst;
}

template<typename FordJohnson, typename Jacobsthal>
FordJohnson    PmergeMe<FordJohnson,Jacobsthal>::addRes(FordJohnson dst, FordJohnson *src) {
    if (src->size() == 0)
        return dst;
    int start;
    for (start = 0; start < (int)src->size(); start++)
        dst.push_back((*src)[start]);
    src->clear();
    return dst;
}

template<typename FordJohnson, typename Jacobsthal>
void    PmergeMe<FordJohnson,Jacobsthal>::splitStack() {
    FordJohnson    newstack;
    FordJohnson    tmp;
    FordJohnson    res;
    
    newstack = addPair(newstack, &stack);
    while ((int)stack.size() > pairSize) {
        newstack = addPair(newstack, &stack);
        tmp = addPair(tmp, &stack);
    }
    res = addRes(res, &stack);

    for (int posJacob = 1; static_cast<int>(tmp.size()) > 0; posJacob++) {
        int len = (jacobList[posJacob] - jacobList[posJacob -1]) * pairSize -1;
        while (len >= static_cast<int>(tmp.size()))
            len -= pairSize;
        for (; len >= 0; len -= pairSize)
            newstack = insertPair(newstack, &tmp, binarySearch(newstack, tmp[len]), len);
        if (posJacob + 2 > static_cast<int>(jacobList.size()))
            addJacobList();
    }
    stack = addRes(stack, &newstack);
    stack = addRes(stack, &res);
}

template<typename FordJohnson, typename Jacobsthal>
void    PmergeMe<FordJohnson,Jacobsthal>::fordJohnson() {
    pairSize = 2;
    initJacobList();
    while (static_cast<size_t>(pairSize) < stack.size()) {
        for (int pos = 0; static_cast<size_t>(pos) < stack.size(); pos += pairSize) {
            if (checkPairMax(pos) == false)
                swapPair(pos);
        }
        pairSize *= 2;
    }
    
    while (pairSize > 0) {
        splitStack();
        if (pairSize == 1)
            break ;
        pairSize = pairSize / 2;
    }
}

#endif