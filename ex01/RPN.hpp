/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amblanch <amblanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:18:00 by amblanch          #+#    #+#             */
/*   Updated: 2026/01/29 10:40:06 by amblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>

class RPN {
    private:
        std::stack<std::string> data;
    public:
        RPN();
        ~RPN();
        RPN(const RPN &other);
        RPN &operator=(const RPN &other);
        
        void        algo(std::string);
        double      convertStringToInt(std::string value);
        std::string convertIntToString(double value);

        void         add();
        void         divide();
        void         substract();
        void         multiply();

        void         convert(double *a, double *b);

        
};

#endif