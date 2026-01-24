/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaury <amaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:20:03 by amblanch          #+#    #+#             */
/*   Updated: 2026/01/24 22:55:03 by amaury           ###   ########.fr       */
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
    /*for (std::vector<int>::iterator it = stack.begin(); it != stack.end(); it++) {
        std::cout << "iterator : " << *it << std::endl; 
    }
    std::cout << std::endl;*/
}

bool    PmergeMe::checkMax(int pos) {
    int first = pairSize / 2 - 1;
    //std::cout << "CHECK | pos : " << pos << " first : " << first << " pairsize - 1 : " << pairSize - 1 << " size-stack : " << stack.size() << std::endl;
    if (pos + first > (int)stack.size() || pos + pairSize - 1 > (int)stack.size())
        return true;
    //std::cout << "CHECK | first : " << stack[pos + first] << " second : " << stack[pos + pairSize - 1] << " result : ";
    if (stack[pos + first] > stack[pos + pairSize - 1]) {
        //std::cout << "FALSE" << std::endl;
        return (false);
    }
    //std::cout << "TRUE" << std::endl;
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
        //std::cout << "SWAPPER | first : " << stack[pos + i] << " second : " << stack[pos + i + len] << " pairsize : " << pairSize << std::endl;
        swap(stack[pos + i], stack[pos + i + len]);
    }
    //std::cout << std::endl;
}

int     PmergeMe::binarySearch(std::vector<int> stack, int elem) {
    std::vector<int> nb;
    for (int i = pairSize - 1; i < (int)stack.size(); i += pairSize)
        nb.push_back(stack[i]);
    /*for (std::vector<int>::iterator it = nb.begin(); it != nb.end(); it++) {
        std::cout << "(binary)iterator[nb] : " << *it << std::endl; 
    }*/
    size_t i = 0;
    for (i = 0; i < nb.size(); i++)
        if (nb[i] > elem) break ;
    //std::cout << "{binary} find i : " << i << " elem : " << elem << std::endl;
    return i;
}


std::vector<int>    PmergeMe::insertPair(std::vector<int> dst, std::vector<int> *src, int pos, int len) {
    std::vector<int> newstack;
    
    for (int i = 0; i < pos; i++)
        newstack = addPair(newstack, &dst);
    for (int i = len - pairSize + 1; i <= len; i++) {
        newstack.push_back((*src)[i]);
    }
    for (int i = 0; i < pairSize; i++) {
        src->erase(src->begin() + len - i);
    }
    newstack = addRes(newstack, &dst);
    /*for (std::vector<int>::iterator it = newstack.begin(); it != newstack.end(); it++) {
        std::cout << "(insertPair)iterator[newstack] : " << *it << std::endl; 
    }*/
    return (newstack);
}

std::vector<int>    PmergeMe::addPair(std::vector<int> dst, std::vector<int> *src) {
    if (pairSize > (int)src->size())
        return dst;
    int start;
    for (start = 0; start < pairSize; start++)
        dst.push_back((*src)[start]);
    for (start = start - 1; start >= 0; start--)
        src->erase(src->begin() + start);
    return dst;
}

std::vector<int>    PmergeMe::addRes(std::vector<int> dst, std::vector<int> *src) {
    if (src->size() == 0)
        return dst;
    int start;
    for (start = 0; start < (int)src->size(); start++)
        dst.push_back((*src)[start]);
    src->clear();
    return dst;
}

std::vector<int>    PmergeMe::splitStack() {
    std::vector<int>    newstack;
    std::vector<int>    tmp;
    std::vector<int>    res;
    
    newstack = addPair(newstack, &stack);
    while ((int)stack.size() > pairSize) {
        newstack = addPair(newstack, &stack);
        tmp = addPair(tmp, &stack);
    }
    res = addRes(res, &stack);
    /*for (std::vector<int>::iterator it = tmp.begin(); it != tmp.end(); it++) {
        std::cout << "iterator[tmp] : " << *it << std::endl; 
    }
    std::cout << std::endl;
    for (size_t it = 0; it < newstack.size(); it++) {
        std::cout << "iterator[newstack] : " << newstack[it] << std::endl; 
    }
    std::cout << std::endl;
    for (std::vector<int>::iterator it = res.begin(); it != res.end(); it++) {
        std::cout << "iterator[res] : " << *it << std::endl; 
    }*/
    //std::cout << std::endl;
    for (int posJacob = 1; static_cast<int>(tmp.size()) > 0; posJacob++) {
        int len = (jacobList[posJacob] - jacobList[posJacob -1]) * pairSize -1;
        /*std::cout << std::endl << "-------loop init [" << pairSize << "][" << len << "]-------" << std::endl << std::endl;
        for (std::vector<int>::iterator it = tmp.begin(); it != tmp.end(); it++) {
            std::cout << "iterator[tmp] : " << *it << std::endl; 
        }*/
        while (len >= static_cast<int>(tmp.size()))
            len -= pairSize;
        for (; len >= 0; len -= pairSize) {
            /*std::cout << std::endl << "-------JACOB [" << len << "] -------" << std::endl << std::endl;
            for (std::vector<int>::iterator it = tmp.begin(); it != tmp.end(); it++) {
                std::cout << "iterator[tmp] : " << *it << std::endl; 
            }*/
            int posFound = binarySearch(newstack, tmp[len]);
            newstack = insertPair(newstack, &tmp, posFound, len);
        }
        if (posJacob + 2 > static_cast<int>(jacobList.size()))
            addJacobList();
    }
    //std::cout << std::endl;
    stack = addRes(stack, &newstack);
    stack = addRes(stack, &res);
    return (stack);
}

void    PmergeMe::fordJohnson() {
    pairSize = 2;
    initJacobList();
    while (static_cast<size_t>(pairSize) < stack.size()) {
        for (int pos = 0; static_cast<size_t>(pos) < stack.size(); pos += pairSize) {
            //std::cout << "---- New pos [" << pos << "]---------" << std::endl;
            if (checkMax(pos) == false)
                swapper(pos);
        }
        //std::cout << "------NEW LOOP------" << std::endl;
        /*for (std::vector<int>::iterator it = stack.begin(); it != stack.end(); it++) {
            std::cout << "iterator : " << *it << std::endl; 
        }*/
        pairSize *= 2;
    }

    /*std::cout << std::endl;
    std::cout << "----------- insertion ---------" << std::endl;
    std::cout << std::endl;*/
    
    std::vector<int> tmp;
    while (pairSize > 0) {
        //std::cout << "PairSize : " << pairSize << " size : " << stack.size() / pairSize << std::endl;
        tmp = splitStack();
        if (pairSize == 1)
            break ;
        pairSize = pairSize / 2;
    }
    std::cout << "AFTER : ";
    for (std::vector<int>::iterator it = stack.begin(); it != stack.end(); it++) {
        std::cout << *it << " "; 
    }
    std::cout << std::endl;
    //std::cout << std::endl;
}
