/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaury <amaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:21:04 by amblanch          #+#    #+#             */
/*   Updated: 2026/01/25 21:40:47 by amaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv) {
    try {
        if (argc < 2)
            throw (std::invalid_argument("Error"));
        PmergeMe< std::vector<int>, std::vector<int> > vectorFordJohnson;
        vectorFordJohnson.CreateList(argc, argv);
        vectorFordJohnson.printStack("Before: ");
        vectorFordJohnson.fordJohnson();
        vectorFordJohnson.printStack("After: ");
        vectorFordJohnson.printJacobsthal("Jacob: ");
        PmergeMe< std::deque<int>, std::vector<int> > dequeFordJohnson;
        dequeFordJohnson.CreateList(argc, argv);
        dequeFordJohnson.printStack("Before: ");
        dequeFordJohnson.fordJohnson();
        dequeFordJohnson.printStack("After: ");
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}