/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amblanch <amblanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:21:04 by amblanch          #+#    #+#             */
/*   Updated: 2026/01/22 16:34:21 by amblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv) {
    try {
        if (argc < 2)
            throw (std::invalid_argument("Error"));
        PmergeMe fordJohnson;
        fordJohnson.CreateList(argc, argv);
        fordJohnson.fordJohnson();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}