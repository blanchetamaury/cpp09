/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amblanch <amblanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:20:03 by amblanch          #+#    #+#             */
/*   Updated: 2026/01/22 17:35:19 by amblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void    PmergeMe::initJacobList() {
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
}
