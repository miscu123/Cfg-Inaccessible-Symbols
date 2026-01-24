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
bool valid_symbol(const std::string &s, std::string VN[26], std::string VT[26])
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
            if (!valid_symbol(s, VN, VT))
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

void calculate_H(std::string VN[26], std::string VT[26], std::map<std::string, std::vector<std::string>> &P, std::string H[60])
{
    // we calculate H using VN, VT & P
    // find start symbol (first VN)
    std::string S = "";
    for (int i = 0; i < 26; i++)
    {
        if (!VN[i].empty())
        {
            S = VN[i];
            break;
        }
    }

    if (S.empty())
    {
        std::cout << "Error! No start symbol found!" << std::endl;
        return;
    }

    // init: i = 0, H0 = {S}
    std::set<std::string> H_prev;
    std::set<std::string> H_curr;
    H_curr.insert(S);
    int i = 0;

    std::cout << "\ni = " << i << std::endl;
    std::cout << "H" << i << " = { " << S << " }" << std::endl;

    // repeat until Hi = Hi+1
    bool changed = true;
    while (changed)
    {
        i++;
        H_prev = H_curr;

        std::cout << "\ni = " << i << std::endl;
        std::cout << "H" << i - 1 << " = { ";
        for (const auto &sym : H_prev)
        {
            std::cout << sym << " ";
        }
        std::cout << "}" << std::endl;

        // Hi+1 = Hi ∪ {y | X → vyw ∈ P & X ∈ Hi}
        for (const auto &pair : P)
        {
            std::string X = pair.first;

            // if X is in H_curr
            if (H_curr.find(X) != H_curr.end())
            {
                // for every prod
                for (const auto &production : pair.second)
                {
                    // add symbols from P in H
                    for (char c : production)
                    {
                        std::string symbol(1, c);
                        H_curr.insert(symbol);
                    }
                }
            }
        }

        // show new symbols
        std::cout << "H" << i << " = { ";
        for (const auto &sym : H_curr)
        {
            std::cout << sym << " ";
        }
        std::cout << "}" << std::endl;

        // we verify if Hi = Hi-1
        if (H_curr == H_prev)
        {
            changed = false;
            std::cout << "\nCondition met: H" << i << " = H" << i - 1 << std::endl;
        }
    }

    // print out the result
    std::cout << "H = { ";
    int idx = 0;
    for (const auto &symbol : H_curr)
    {
        std::cout << symbol << " ";
        if (idx < 60)
        {
            H[idx] = symbol;
            idx++;
        }
    }
    std::cout << "}" << std::endl;
}

// function to calculate VN2
void result_VN(std::string VN[26], std::string H[60], std::string VN2[26], std::string inacc_syms[60], uint8_t &sym_idx)
{
    // VN2 == VN intersected with H
    uint8_t idx = 0;

    for (uint8_t i = 0; i < 26; i++)
    {
        if (VN[i].empty())
            continue;

        bool found = false;
        for (uint8_t j = 0; j < 60; j++)
        {
            if (VN[i] == H[j])
            {
                found = true;
                VN2[idx++] = VN[i];
                break;
            }
        }
        if (!found)
            inacc_syms[sym_idx++] = VN[i];
    }
}

// function to calculate VT2
void result_VT(std::string VT[26], std::string H[60], std::string VT2[26], std::string inacc_syms[60], uint8_t &sym_idx)
{
    // VT2 == VT intersected with H
    uint8_t idx = 0;

    for (uint8_t i = 0; i < 26; i++)
    {
        if (VT[i].empty())
            continue;

        bool found = false;
        for (uint8_t j = 0; j < 60; j++)
        {
            if (VT[i] == H[j])
            {
                found = true;
                VT2[idx++] = VT[i];
                break;
            }
        }
        if (!found)
            inacc_syms[sym_idx++] = VT[i];
    }
}

void clear_arr(std::string arr[], int n)
{
    for (int i = 0; i < n; i++)
        arr[i].clear();
}

void print_arr(const std::string arr[], int n, const std::string &label)
{
    std::cout << label << ": { ";
    bool any = false;
    for (int i = 0; i < n; i++)
    {
        if (!arr[i].empty())
        {
            std::cout << arr[i] << " ";
            any = true;
        }
    }
    if (!any)
        std::cout << "(empty) ";
    std::cout << "}\n";
}

void print_P(const std::map<std::string, std::vector<std::string>> &P)
{
    std::cout << "P (productions):\n";
    if (P.empty())
    {
        std::cout << "  (empty)\n";
        return;
    }

    for (const auto &kv : P)
    {
        std::cout << "  " << kv.first << " -> ";
        for (size_t i = 0; i < kv.second.size(); i++)
        {
            std::cout << kv.second[i];
            if (i + 1 < kv.second.size())
                std::cout << " | ";
        }
        std::cout << "\n";
    }
}

void compute_all(Symbols &sym)
{
    clear_arr(sym.H, 60);
    clear_arr(sym.VN2, 26);
    clear_arr(sym.VT2, 26);
    clear_arr(sym.inacc_syms, 60);
    sym.sym_idx = 0;

    calculate_H(sym.VN, sym.VT, sym.P, sym.H);

    result_VN(sym.VN, sym.H, sym.VN2, sym.inacc_syms, sym.sym_idx);
    result_VT(sym.VT, sym.H, sym.VT2, sym.inacc_syms, sym.sym_idx);
}