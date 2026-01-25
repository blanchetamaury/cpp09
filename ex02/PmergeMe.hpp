/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaury <amaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:19:16 by amblanch          #+#    #+#             */
/*   Updated: 2026/01/25 18:39:14 by amaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <sstream>
#include <algorithm>

template<typename FordJohnson, typename Jacobsthal>
class PmergeMe {
    private:
        Jacobsthal      jacobList;
        FordJohnson     stack;
        int             pairSize;
        
        void    initJacobList();
        void    addJacobList();

        typedef typename FordJohnson::value_type value_type;

        void pushstack(const char* s) {
            pushstack_impl(s, value_type());
        }

        void pushstack_impl(const char* s, int) {
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
        PmergeMe();
        ~PmergeMe();
        PmergeMe(const PmergeMe<FordJohnson,Jacobsthal> &other);
        PmergeMe<FordJohnson,Jacobsthal> &operator=(const PmergeMe<FordJohnson,Jacobsthal> &other);

        int                 convertStringToInt(std::string value);
        float               convertStringToFloat(std::string value);
        void                CreateList(int argc, char **argv);
        void                fordJohnson();
        bool                checkMax(int pos);
        void                swapper(int pos);
        FordJohnson         splitStack();
        int                 binarySearch(FordJohnson stack, value_type elem);
        FordJohnson         addPair(FordJohnson dst, FordJohnson *src);
        FordJohnson         addRes(FordJohnson dst, FordJohnson *src);
        FordJohnson         insertPair(FordJohnson dst, FordJohnson *src, int pos, int len);
        void                swap(value_type &a, value_type &b);

};

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
int PmergeMe<FordJohnson,Jacobsthal>::convertStringToInt(std::string value) {
    std::stringstream ss(value);
    int nb = 0;

    ss >> nb;
    return nb;
}

template<typename FordJohnson, typename Jacobsthal>
float PmergeMe<FordJohnson,Jacobsthal>::convertStringToFloat(std::string value) {
    std::stringstream ss(value);
    float nb = 0;
    ss >> nb;
    return nb;
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
    for (int i = 1; i < argc; i++) {
        std::string tmp = argv[i];
        if (tmp.find("-") != std::string::npos)
            throw (std::invalid_argument("Error"));
        pushstack(argv[i]);
    }
}

template<typename FordJohnson, typename Jacobsthal>
bool    PmergeMe<FordJohnson,Jacobsthal>::checkMax(int pos) {
    int first = pairSize / 2 - 1;
    if (pos + first >= (int)stack.size() || pos + pairSize - 1 >= (int)stack.size())
        return true;
    if (stack[pos + first] > stack[pos + pairSize - 1]) {
        return (false);
    }
    return (true);
}

template<typename FordJohnson, typename Jacobsthal>
void     PmergeMe<FordJohnson,Jacobsthal>::swap(value_type &a, value_type &b) {
    value_type tmp = a;
    a = b;
    b = tmp;
}

template<typename FordJohnson, typename Jacobsthal>
void    PmergeMe<FordJohnson,Jacobsthal>::swapper(int pos) {
    int len = pairSize / 2;
    for (int i = 0; i < len; i++) {
        swap(stack[pos + i], stack[pos + i + len]);
    }
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
FordJohnson    PmergeMe<FordJohnson,Jacobsthal>::splitStack() {
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
        for (; len >= 0; len -= pairSize) {
            int posFound = binarySearch(newstack, tmp[len]);
            newstack = insertPair(newstack, &tmp, posFound, len);
        }
        if (posJacob + 2 > static_cast<int>(jacobList.size()))
            addJacobList();
    }
    stack = addRes(stack, &newstack);
    stack = addRes(stack, &res);
    return (stack);
}

template<typename FordJohnson, typename Jacobsthal>
void    PmergeMe<FordJohnson,Jacobsthal>::fordJohnson() {
    pairSize = 2;
    initJacobList();
    while (static_cast<size_t>(pairSize) < stack.size()) {
        for (int pos = 0; static_cast<size_t>(pos) < stack.size(); pos += pairSize) {
            if (checkMax(pos) == false)
                swapper(pos);
        }
        pairSize *= 2;
    }
    
    FordJohnson tmp;
    while (pairSize > 0) {
        tmp = splitStack();
        if (pairSize == 1)
            break ;
        pairSize = pairSize / 2;
    }
    std::cout << "AFTER : ";
    for (typename FordJohnson::iterator it = stack.begin(); it != stack.end(); it++) {
        std::cout << *it << " "; 
    }
    std::cout << std::endl;
}

#endif