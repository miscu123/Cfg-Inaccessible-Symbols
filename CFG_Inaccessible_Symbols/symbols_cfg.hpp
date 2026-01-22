#ifndef SYMBOLS_CFG_HPP
#define SYMBOLS_CFG_HPP

#define lambda λ

#include <cstdint>
#include <string>
#include <stdio.h>
#include <iostream>
#include <cctype>
#include <vector>
#include <map>
#include <set>

void init_VN(std::string VN[26]);
void init_VT(std::string VT[26]);
bool valid_symbol(const std::string &s, std::string VN[26], std::string VT[26]);
void init_P(std::string VN[26], std::string VT[26], std::map<std::string, std::vector<std::string>> &P);
void calculate_H(std::string VN[26], std::string VT[26], std::map<std::string, std::vector<std::string>> &P, std::string H[60]);
void result_VN(std::string VN[26], std::string H[60], std::string VN2[26], std::string inacc_syms[60], uint8_t &sym_idx);
void result_VT(std::string VT[26], std::string H[60], std::string VT2[26], std::string inacc_syms[60], uint8_t &sym_idx);

struct Symbols
{
    // initial variables and/or lists
    std::map<std::string, std::vector<std::string>> P;
    std::string VN[26];
    std::string VT[26];
    std::string H[60];

    // the result lists
    std::map<std::string, std::vector<std::string>> P2;
    std::string VN2[26];
    std::string VT2[26];
    uint8_t sym_idx;
    std::string inacc_syms[60];

    Symbols()
    {
        sym_idx = 0;
    }
};

#endif