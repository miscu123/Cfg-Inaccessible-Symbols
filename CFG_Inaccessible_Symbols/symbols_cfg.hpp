#ifndef SYMBOLS_CFG_HPP
#define SYMBOLS_CFG_HPP

// define lambda
// #define λ 0

#include <cstdint>
#include <string>
#include <stdio.h>
#include <iostream>
#include <cctype>
#include <vector>
#include <map>

void init_VN(std::string VN[26]);
void init_VT(std::string VT[26]);
bool simbol_valid(const std::string &s, std::string VN[26], std::string VT[26]);
void init_P(std::string VN[26], std::string VT[26], std::map<std::string, std::vector<std::string>> &P);
void result_VN(std::string VN[26], std::string H[60], std::string VN2[26]);
void result_VT(std::string VT[26], std::string H[60], std::string VT2[26]);
void result_P(std::map<std::string, std::vector<std::string>> &P, std::string H[60], std::map<std::string, std::vector<std::string>> &P2);

struct Symbols
{
    // initial variables and/or lists
    std::map<std::string, std::vector<std::string>> P;
    std::string VN[26];
    std::string VT[26];
    std::string H[60];
    volatile uint8_t j;

    // the result lists
    std::map<std::string, std::vector<std::string>> P2;
    std::string VN2[26];
    std::string VT2[26];
    std::string inacc_syms[60];
};

#endif