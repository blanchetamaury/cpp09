/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaury <amaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:19:16 by amblanch          #+#    #+#             */
/*   Updated: 2026/01/24 22:54:20 by amaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <sstream>
#include <algorithm>

class PmergeMe {
    private:
        std::vector<int>    jacobList;
        std::vector<int>    stack;

        int                 pairSize;

        void    initJacobList();
        void    addJacobList();
    public:
        PmergeMe();
        ~PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);

        int                 convertStringToInt(std::string value);
        void                CreateList(int argc, char **argv);
        void                fordJohnson();
        bool                checkMax(int pos);
        void                swapper(int pos);
        std::vector<int>    splitStack();
        int                 binarySearch(std::vector<int> stack, int elem);
        std::vector<int>    addPair(std::vector<int> dst, std::vector<int> *src);
        std::vector<int>    addRes(std::vector<int> dst, std::vector<int> *src);
        std::vector<int>    insertPair(std::vector<int> dst, std::vector<int> *src, int pos, int len);

};

#endif