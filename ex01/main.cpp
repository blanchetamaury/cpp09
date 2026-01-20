/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amblanch <amblanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:47:25 by amblanch          #+#    #+#             */
/*   Updated: 2026/01/19 14:58:12 by amblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char **argv) {
    try {
        if (argc != 2)
            throw (std::invalid_argument("arg not good"));
        RPN rpn;
        rpn.algo(argv[1]);
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}