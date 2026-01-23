/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amblanch <amblanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:20:03 by amblanch          #+#    #+#             */
/*   Updated: 2026/01/23 11:06:31 by amblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void    PmergeMe::initJacobList() {
    jacobList.push_back(1);
    jacobList.push_back(3);
    jacobList.push_back(5);
    jacobList.push_back(11);
}

void    PmergeMe::addJacobList() {
    std::vector<int>::iterator it = jacobList.end();
    it--;
    int value = *it;
    it--;
    value += (*it * 2);
    jacobList.push_back(value);
}

PmergeMe::PmergeMe(): pairSize(2) { }
PmergeMe::~PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe &other) {
    this->stack = other.stack;
    this->pairSize = other.pairSize;
    this->jacobList = other.jacobList;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
    if (this != &other) {
        this->stack = other.stack;
        this->pairSize = other.pairSize;
        this->jacobList = other.jacobList;
    }
    return (*this);
}

int PmergeMe::convertStringToInt(std::string value) {
    std::stringstream ss(value);
    int nb = 0;

    ss >> nb;
    return nb;
}

void    PmergeMe::CreateList(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        std::string tmp = argv[i];
        if (tmp.find("-") != std::string::npos)
            throw (std::invalid_argument("Error"));
        stack.push_back(convertStringToInt(argv[i]));
    }
    for (std::vector<int>::iterator it = stack.begin(); it != stack.end(); it++) {
        std::cout << "iterator : " << *it << std::endl; 
    }
    std::cout << std::endl;
}

bool    PmergeMe::checkMax(int pos) {
    int first = pairSize / 2 - 1;
    std::cout << "CHECK | first : " << stack[pos + first] << " second : " << stack[pos + pairSize - 1] << " result : ";
    if (stack[pos + first] > stack[pos + pairSize - 1]) {
        std::cout << "FALSE" << std::endl;
        return (false);
    }
    std::cout << "TRUE" << std::endl;
    return (true);
}

void     swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void    PmergeMe::swapper(int pos) {
    int len = pairSize / 2;
    for (int i = 0; i < len; i++) {
        std::cout << "SWAPPER | first : " << stack[pos + i] << " second : " << stack[pos + i + len] << std::endl;
        swap(stack[pos + i], stack[pos + i + len]);
    }
    std::cout << std::endl;
}

int     PmergeMe::binarySearch(std::vector<int> stack, int elem) {
    int start = stack.size() / pairSize;
    start = start / 2 * pairSize;
    int prevElem = -1;
    int nextElem = -1;
    if (start - pairSize >= 0)
        prevElem = stack[start - pairSize];
    if (start + pairSize <= stack.size())
        nextElem = stack[start + pairSize];
    while (true) {
        if (prevElem == -1) {
            if (stack[start] >)
        }
        else if (nextElem == -1) {
            
        }
        else if (stack[prev]) {
            
        }
    }
}


std::vector<int>    PmergeMe::splitStack() {
    std::vector<int>    newstack;
    std::vector<int>    tmp;
    std::vector<int>    res;

    for (int start = 0; start < pairSize * 2; start++) {
        newstack.push_back(stack[start]);
    }
    for (int start = pairSize * 2; static_cast<size_t>(start) < stack.size(); start += pairSize * 2) {
        for (int i = 0; i < pairSize; i++) {
            tmp.push_back(stack[start + i]);
        }
        for (int i = pairSize; i < pairSize * 2; i++) {
            newstack.push_back(stack[start + i]);
        }
    }
    for (size_t i = stack.size() - stack.size() % pairSize; i < stack.size(); i++) {
        res.push_back(stack[i]);
    }

    for (std::vector<int>::iterator it = tmp.begin(); it != tmp.end(); it++) {
        std::cout << "iterator[tmp] : " << *it << std::endl; 
    }
    std::cout << std::endl;
    for (std::vector<int>::iterator it = newstack.begin(); it != newstack.end(); it++) {
        std::cout << "iterator[newstack] : " << *it << std::endl; 
    }
    std::cout << std::endl;
    for (std::vector<int>::iterator it = res.begin(); it != res.end(); it++) {
        std::cout << "iterator[res] : " << *it << std::endl; 
    }
    std::cout << std::endl;

    
    
    return (tmp);
}

void    PmergeMe::fordJohnson() {
    pairSize = 2;
    initJacobList();
    while (static_cast<size_t>(pairSize) < stack.size()) {
        for (int pos = 0; static_cast<size_t>(pos) < stack.size(); pos += pairSize) {
            if (checkMax(pos) == false)
                swapper (pos);
        }
        std::cout << "------NEW LOOP------" << std::endl;
        for (std::vector<int>::iterator it = stack.begin(); it != stack.end(); it++) {
            std::cout << "iterator : " << *it << std::endl; 
        }
        pairSize *= 2;
    }

    std::cout << std::endl;
    std::cout << "----------- insertion ---------" << std::endl;
    std::cout << std::endl;
    
    std::vector<int> tmp;
    while (pairSize > 1) {
        std::cout << "PairSize : " << pairSize << std::endl;
        if (stack.size() / pairSize >= 3) {
            tmp = splitStack();
            break ;
        }    
        pairSize = pairSize / 2;
    }
    std::cout << std::endl;
}
