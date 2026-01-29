/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amblanch <amblanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:21:04 by amblanch          #+#    #+#             */
/*   Updated: 2026/01/27 09:49:22 by amblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <ctime>

int main(int argc, char **argv) {
    
    try {
        if (argc < 2)
            throw (std::invalid_argument("Error"));        
        struct timespec start, end;
        PmergeMe< std::vector<int>, std::vector<int> > vectorFordJohnson;
        vectorFordJohnson.CreateList(argc, argv);
        vectorFordJohnson.printStack("Before: ");
        timespec_get(&start, TIME_UTC);
        vectorFordJohnson.fordJohnson();
        timespec_get(&end, TIME_UTC);
        vectorFordJohnson.printStack("After: ");
        long double elapsed_us = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;
        std::cout << std::fixed << "Time to process a range of : " << vectorFordJohnson.GetSize() << " elements with std::vector : " <<  elapsed_us << " us" << std::endl;
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    
    try {
        if (argc < 2)
            throw (std::invalid_argument("Error"));
        struct timespec start, end;
        PmergeMe< std::deque<int>, std::vector<int> > dequeFordJohnson;
        dequeFordJohnson.CreateList(argc, argv);
        timespec_get(&start, TIME_UTC);
        dequeFordJohnson.fordJohnson();
        timespec_get(&end, TIME_UTC);
        long double elapsed_us = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;
        std::cout << std::fixed << "Time to process a range of : " << dequeFordJohnson.GetSize() << " elements with std::deque : " <<  elapsed_us << " us" << std::endl;
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}