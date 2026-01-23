/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amblanch <amblanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:19:16 by amblanch          #+#    #+#             */
/*   Updated: 2026/01/23 10:28:57 by amblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
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
};

#endif