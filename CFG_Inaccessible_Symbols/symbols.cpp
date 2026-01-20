#include "symbols_cfg.hpp"

// function to add all VN variables
void init_VN(std::string VN[26])
{
    char val;
    uint8_t idx = 0;
    uint8_t freq_list[26] = {};

    std::cout << "Enter VN symbols: ";
    while (idx < 26)
    {
        std::cin >> val;

        if (isalpha(val) && isupper(val))
        {
            if (freq_list[val - 'A'] == 0)
            {
                VN[idx] = std::string(1, val); // convert char to string
                freq_list[val - 'A']++;
                idx++;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
}

// function to add all VT variables
void init_VT(std::string VT[26])
{
    char val;
    uint8_t idx = 0;
    uint8_t freq_list[26] = {};

    std::cout << "Enter a VT symbol: ";
    while (idx < 26)
    {
        std::cin >> val;

        if (isalpha(val) && islower(val))
        {
            if (freq_list[val - 'a'] == 0)
            {
                VT[idx] = std::string(1, val); // convert char to string
                freq_list[val - 'a']++;
                idx++;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
}

// verify if symbol is in VN or VT
bool simbol_valid(const std::string &s, std::string VN[26], std::string VT[26])
{
    for (int i = 0; i < 26; i++)
    {
        if (VN[i] == s || VT[i] == s)
            return true;
    }
    return false;
}

// function to add all P variables
void init_P(std::string VN[26], std::string VT[26], std::map<std::string, std::vector<std::string>> &P)
{
    while (true)
    {
        std::cout << "\nAdd a new prod? (y/n): ";
        char r;
        std::cin >> r;

        if (r != 'y' && r != 'Y')
            break;

        std::cout << "Enter VN: ";
        std::string vn;
        std::cin >> vn;

        bool vn_found = false;

        for (int i = 0; i < 26; i++)
        {
            if (VN[i] == vn)
            {
                vn_found = true;
                break;
            }
        }
        if (!vn_found)
        {
            std::cout << "VN is wrong.\n";
            continue;
        }

        std::cout << vn << "--> ";
        std::string prod;
        std::cin >> prod;

        bool valid = true;
        for (char c : prod)
        {
            std::string s(1, c);
            if (!simbol_valid(s, VN, VT))
            {
                valid = false;
                break;
            }
        }
        if (!valid)
        {
            continue; // add a new prod because this one is not valid
        }

        P[vn].push_back(prod);
    }
}

// function to calculate VN2
void result_VN(std::string VN[26], std::string H[60], std::string VN2[26])
{
}

// function to calculate VT2
void result_VT(std::string VT[26], std::string H[60], std::string VT2[26])
{
}

// function to calculate P2
void result_P(std::map<std::string, std::vector<std::string>> &P, std::string H[60], std::map<std::string, std::vector<std::string>> &P2)
{
}