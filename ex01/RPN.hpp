/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amblanch <amblanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:18:00 by amblanch          #+#    #+#             */
/*   Updated: 2026/01/20 09:44:03 by amblanch         ###   ########.fr       */
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
        int         convertStringToInt(std::string value);
        std::string convertIntToString(int value);

        void         add();
        void         divide();
        void         substract();
        void         multiply();

        void         convert(int *a, int *b);

        
};

#endif