#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <unordered_map>
#include <iomanip>
#include <fstream>
#include <time.h>

class BitcoinExchange {
    private:
        std::map<std::string, float> dataHashMap;
    protected:
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange & src);
        ~BitcoinExchange();
        BitcoinExchange & operator=(const BitcoinExchange & rhs);

        std::string trimSpaces(const std::string &str);
        bool isValidDateFormat(const std::string &date);
        bool isValidValue(const std::string &value);
        bool isPastDate(const std::string &date);
        void fillData(std::ifstream& data);
        float getRateValueFromData(const std::string &date);
        void parseFile(const std::string &file_name);
        void ShowRatesExchange(const std::string &file_name);
};

#endif