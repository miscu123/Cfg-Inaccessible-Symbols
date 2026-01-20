#ifndef SYMBOLS_CFG_HPP
#define SYMBOLS_CFG_HPP

// define lambda
#define λ 0

#include <stdint.h>
#include <string>
#include <stdio.h>

std::string init_VN(std::string &VN);
std::string init_VT(std::string &VT);
std::string init_P(std::string &VN, std::string &VT, std::string &P);
std::string result_VN(std::string &VN, std::string &H, std::string &VN2);
std::string result_VT(std::string &VT, std::string &H, std::string &VT2);
std::string result_P(std::string &P, std::string &H, std::string &P2);

struct Symbols
{
    // initial variables and/or lists
    std::string P;
    std::string VN;
    std::string VT;
    std::string H;
    volatile int j;

    // the result lists
    std::string P2;
    std::string VN2;
    std::string VT2;
    std::string inacc_syms;
};

#endif