/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amblanch <amblanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:20:17 by amblanch          #+#    #+#             */
/*   Updated: 2026/01/26 16:13:25 by amblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() {}
RPN::~RPN() {}
RPN::RPN(const RPN &other) {
    this->data = other.data;
}
RPN &RPN::operator=(const RPN &other) {
    if (this != &other) {
        this->data = other.data;
    }
    return *this;
}

std::string RPN::convertIntToString(int value) {
    std::stringstream ss;
    ss << value;

    return (ss.str());
}

int RPN::convertStringToInt(std::string value) {
    std::stringstream ss(value);
    int nb = 0;

    ss >> nb;
    return nb;
}

void    RPN::convert(int *a, int *b) {
    if (data.size() < 3)
        throw (std::invalid_argument("Error: stack size."));
    data.pop();
    if (!isdigit(data.top()[0]))
        throw (std::invalid_argument("Error: not a number [" + data.top() + "]."));
    *a = convertStringToInt(data.top());
    data.pop();
    if (!isdigit(data.top()[0]))
        throw (std::invalid_argument("Error: not a number [" + data.top() + "]."));
    *b = convertStringToInt(data.top());
    data.pop();
}

void RPN::add() {
    int a,b;
    convert(&a, &b);
    data.push(convertIntToString(a + b));
}

void RPN::divide() {
    int a,b;
    convert(&a, &b);
    if (a == 0)
        throw(std::invalid_argument("Error: division by zero."));
    data.push(convertIntToString(b / a));
}

void RPN::substract() {
    int a,b;
    convert(&a, &b);
    data.push(convertIntToString(b - a));
}

void RPN::multiply() {
    int a,b;
    convert(&a, &b);
    data.push(convertIntToString(a * b));
}

std::stack<std::string> next(std::stack<std::string> token, std::string *str, std::string lineDelimiter) {
	if (str->empty()) return token;
    size_t 	lineEnd = str->find(lineDelimiter);
    if (lineEnd == std::string::npos) {
        lineEnd = str->size();
        token.push(str->substr(0, lineEnd));
        str->clear();    
    }
    else {
        token.push(str->substr(0, lineEnd));
        *str = str->substr(lineEnd + 1, str->size());
    }
	return token;
}

void RPN::algo(std::string arg) {
    if (arg.empty())
        throw (std::invalid_argument("Error: empty argument."));
    while (!arg.empty()) {
        data = next(data, &arg, " ");
        if (data.top().size() != 1)
            throw (std::invalid_argument("Error: [" + data.top() + "]."));
        if (data.top() == "-") substract();
        if (data.top() == "+") add();
        if (data.top() == "*") multiply();
        if (data.top() == "/") divide();
    }
    if (data.size() > 1)
        throw (std::invalid_argument("Error: stack size."));
}