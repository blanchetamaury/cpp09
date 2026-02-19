/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amblanch <amblanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 10:59:13 by amaury            #+#    #+#             */
/*   Updated: 2026/02/19 10:20:53 by amblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::~BitcoinExchange() {}
BitcoinExchange::BitcoinExchange() { openData("data.csv"); }
BitcoinExchange::BitcoinExchange(const BitcoinExchange &other): dataFile(other.dataFile) {}
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
	if (this != &other)
		this->dataFile = other.dataFile;
	return (*this);
}


std::map<std::string, double> split(const std::string& str, std::string lineDelimiter) {
	std::map<std::string, double> tokens;
	size_t 	lineStart = 0;
	size_t 	lineEnd = str.find(lineDelimiter);
	size_t 	DateEnd = str.find(",");
	float	value = 0;

	std::cout << std::fixed;
	std::stringstream ss(str.substr(DateEnd + 1));
	ss >> value;

	while (lineEnd != std::string::npos) {
		std::string date = str.substr(lineStart, str.find(",", lineStart) - lineStart);
		if (date != "date") {
			std::string valuedate;
			valuedate = date.substr(0,4).c_str();
			valuedate += date.substr(5,2).c_str();
			valuedate += date.substr(8,2).c_str();
			tokens[valuedate] = value;
		}
		lineStart = lineEnd + 1;
		lineEnd = str.find(lineDelimiter, lineStart);
		size_t 	DateEnd = str.find(",", lineStart);
		std::stringstream ss(str.substr(DateEnd + 1, lineEnd - DateEnd));
		ss >> value;
	}
	return tokens;
}

void BitcoinExchange::openData(std::string fileName) {
	std::ifstream file(fileName.c_str());
	std::string tmp;
	
	getline(file, tmp, '\0');
	file.close();
	dataFile = split(tmp, "\n");
}

std::map<std::string, double>	BitcoinExchange::getData() {
	return dataFile;
}