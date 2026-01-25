/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaury <amaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:20:03 by amblanch          #+#    #+#             */
/*   Updated: 2026/01/25 20:41:00 by amaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int convertStringToInt(std::string value) {
    std::stringstream ss(value);
    int nb = 0;

    ss >> nb;
    return nb;
}

long long convertStringToLongLong(std::string value) {
    std::stringstream ss(value);
    long long nb = 0;
    ss >> nb;
    return nb;
}

float convertStringToFloat(std::string value) {
    std::stringstream ss(value);
    float nb = 0;
    ss >> nb;
    return nb;
}

void parsingInt(std::string input) {
    long long value = convertStringToLongLong(input);
    if (value > std::numeric_limits<int>::max())
        throw (std::invalid_argument("Error: not a int argument"));
    if (value < 0)
        throw (std::invalid_argument("Error: not a positive int argument"));
    for (int i = 0; input[i]; i++)
        if (!isdigit(input[i]))
            throw (std::invalid_argument("Error: not a digit argument"));
}