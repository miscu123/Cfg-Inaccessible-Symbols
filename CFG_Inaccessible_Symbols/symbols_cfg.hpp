#ifndef SYMBOLS_CFG_HPP
#define SYMBOLS_CFG_HPP

#include <cstdint>
#include <string>
#include <stdio.h>
#include <iostream>
#include <cctype>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <algorithm>

struct Symbols;

void init_VN(std::string VN[26]);
void init_VT(std::string VT[26]);
bool valid_symbol(const std::string &s, std::string VN[26], std::string VT[26]);
void init_P(std::string VN[26], std::string VT[26], std::map<std::string, std::vector<std::string>> &P);
void calculate_H(std::string VN[26], std::string VT[26], std::map<std::string, std::vector<std::string>> &P, std::string H[60], const std::string &start_symbol);
void result_VN(std::string VN[26], std::string H[60], std::string VN2[26], std::string inacc_syms[60], uint8_t &sym_idx);
void result_VT(std::string VT[26], std::string H[60], std::string VT2[26], std::string inacc_syms[60], uint8_t &sym_idx);
void clear_arr(std::string arr[], int n);
void print_arr(const std::string arr[], int n, const std::string &label);
void print_P(const std::map<std::string, std::vector<std::string>> &P);
void compute_all(Symbols &sym);
bool load_grammar_interactive(Symbols &sym);
void reset_all(Symbols &sym);
bool read_VN_VT_from_file(const std::string &file, Symbols &sym);
bool vn_contains(const std::string VN[26], const std::string &s);
bool is_terminal_token(const std::string &tok);
bool add_unique_symbol(std::string arr[26], const std::string &sym);
std::string trim(std::string s);

struct Symbols
{
    // initial variables and/or lists
    std::map<std::string, std::vector<std::string>> P;
    std::string VN[26];
    std::string VT[26];
    std::string H[60];
    std::string start_symbol;

    // the result lists
    std::map<std::string, std::vector<std::string>> P2;
    std::string VN2[26];
    std::string VT2[26];
    uint8_t sym_idx;
    std::string inacc_syms[60];

    Symbols()
    {
        sym_idx = 0;
        clear_arr(inacc_syms, 60);
    }
};

#endif