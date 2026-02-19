/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amblanch <amblanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:32:14 by amaury            #+#    #+#             */
/*   Updated: 2026/02/19 10:28:40 by amblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

std::string	openFile(std::string fileName) {
	std::ifstream file(fileName.c_str());
	std::string tmp;
	
	if (file.bad() || !file)
		throw (std::invalid_argument("Error: could not open file."));
	getline(file, tmp, '\0');
	file.close();
	return (tmp);
}

bool isLeap(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

bool isValidDate(BitcoinExchange &data,const std::string& s, std::string *date) {
    if (s.size() != 10) {
		return false;
	}
    if (s[4] != '-' || s[7] != '-')
		return false;

    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7)
			continue;
        if (!isdigit(s[i])) 
			return false;
    }

    int y = 0;
	std::stringstream ssY(s.substr(0,4).c_str()); ssY >> y;
	int m = 0;
	std::stringstream ssM(s.substr(5,2).c_str()); ssM >> m;
	int d = 0;
	std::stringstream ssD(s.substr(8,2).c_str()); ssD >> d;

    if (m < 1 || m > 12)
		return false;

    int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (m == 2 && isLeap(y))
		days[1] = 29;
	if (d < 1 || d > days[m - 1])
		return false;
	days[1] = 28;
	std::stringstream ss;
	
	std::string valuedate;
	valuedate = ssY.str();
	valuedate += ssM.str();
	valuedate += ssD.str();
	if (data.getData().count(valuedate) == 0) {
		std::map<std::string, double> datafile = data.getData();
		for (std::map<std::string, double>::iterator it = datafile.begin(); it != datafile.end(); it++) {
			if (valuedate < it->first)
				break ;
			*date = it->first;
		}
	}
	else {
		*date = valuedate;
	}
	return true;
}


void	printLine(BitcoinExchange &data, std::string line, std::string date) {
	double		value = 0;
	bool		status = false;
	
	std::string num = line.substr(line.find(" ", line.find(" ") + 1) + 1);
	for (int i = 0; num[i]; i++) {
		if (!isdigit(num[i]) && num[i] != '.')
			throw (std::invalid_argument("Error: bad input => " + line));
		if (num[i] == '.') {
			if (status == true)
				throw (std::invalid_argument("Error: bad input => " + line));
			status = true;
		}
	}
	std::stringstream ss(num);
	ss >> value;
	if (value < 0)
		throw (std::invalid_argument("Error: not a positive number."));
	if (value > 1000)
		throw (std::invalid_argument("Error: too large a number."));
	if (date.empty())
		throw (std::invalid_argument("Error: date not found in database."));
	else
		std::cout << line.substr(0, line.find(" ")) << " => " << value << " = " << data.getData()[date] * value << std::endl;
}

std::string	checkLine(BitcoinExchange &data, std::string line) {
	std::string date;
	if (line.find(" ") == std::string::npos)
		throw (std::invalid_argument("Error: bad input => " + line));
	std::string sub = line.substr(line.find(" "));
	if (sub.size() < 3 || ( sub[0] != ' ' && sub[1] != '|' && sub[2] != ' '))
		throw (std::invalid_argument("Error: bad input => " + line));
	if (!isValidDate(data, line.substr(0, line.find(" ")), &date))
		throw (std::invalid_argument("Error: bad input => " + line.substr(0, line.find(" "))));
	if (line.size() <= 13)
		throw (std::invalid_argument("Error: bad input => " + line));
	return date;
}

void	compareFile(std::string fileName) {
	std::string str = openFile(fileName);
	BitcoinExchange data;
	size_t 	lineStart = 0;
	size_t 	lineEnd = str.find("\n");
	std::string line = str.substr(lineStart, lineEnd - lineStart);
	if (line != "date | value")
		throw (std::invalid_argument("Error: bad header => " + line));
	lineStart = lineEnd + 1;
	lineEnd = str.find("\n", lineStart);
	line = str.substr(lineStart, lineEnd - lineStart);
	while (lineEnd != std::string::npos) {
		try {
			std::string date = checkLine(data, line);
			printLine(data, line, date);
		}
		catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
		}
		lineStart = lineEnd + 1;
		lineEnd = str.find("\n", lineStart);
		line = str.substr(lineStart, lineEnd - lineStart);
	}
	try {
		std::string date = checkLine(data, line);
		printLine(data, line, date);
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}


int main(int argc, char **argv) {
	try {
		if (argc != 2)
			throw (std::invalid_argument("Error: could not open file."));
		compareFile(argv[1]);
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	
}