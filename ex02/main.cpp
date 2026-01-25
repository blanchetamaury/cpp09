/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaury <amaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:21:04 by amblanch          #+#    #+#             */
/*   Updated: 2026/01/25 18:28:21 by amaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv) {
    try {
        if (argc < 2)
            throw (std::invalid_argument("Error"));
        PmergeMe< std::vector<float>, std::vector<int> > vectorFordJohnson;
        vectorFordJohnson.CreateList(argc, argv);
        vectorFordJohnson.fordJohnson();
        PmergeMe< std::deque<float>, std::vector<int> > dequeFordJohnson;
        dequeFordJohnson.CreateList(argc, argv);
        dequeFordJohnson.fordJohnson();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}