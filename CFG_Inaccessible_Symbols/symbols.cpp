#include "symbols_cfg.hpp"

bool is_terminal(char c) // MODIFICAT
{
    return islower(c) || c == '(' || c == ')' ||
           c == '+' || c == '*' || c == '-';
}

int get_vt_index(char c)
{
    if (islower(c))
        return c - 'a';

    switch (c)
    {
    case '(':
        return 26;
    case ')':
        return 27;
    case '+':
        return 28;
    case '*':
        return 29;
    case '-':
        return 30;
    default:
        return -1;
    }
}

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

    std::cin.sync();
}

// function to add all VT variables
void init_VT(std::string VT[26])
{
    char val;
    uint8_t idx = 0;
    uint8_t freq_list[31] = {};

    std::cout << "Enter VT symbols: ";
    while (idx < 26)
    {
        std::cin >> val;

        if (is_terminal(val))
        {
            int freq_idx = get_vt_index(val);

            if (freq_list[freq_idx] == 0)
            {
                VT[idx] = std::string(1, val);
                freq_list[freq_idx]++;
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

    std::cin.sync();
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
void init_P(std::string VN[26], std::string VT[26],
            std::map<std::string, std::vector<std::string>> &P)
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
            if (VN[i] == vn)
                vn_found = true;

        if (!vn_found)
        {
            std::cout << "VN is wrong.\n";
            continue;
        }

        std::cout << vn << "--> ";
        std::string prod;
        std::cin >> prod;

        if (prod == "λ" || prod == "lambda")
        {
            P[vn].push_back("λ");
            continue;
        }

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
            continue;

        P[vn].push_back(prod);
    }
}

void calculate_H(std::string VN[26], std::string VT[26],
                 std::map<std::string, std::vector<std::string>> &P,
                 std::string H[60],
                 const std::string &start_symbol)
{
    std::string S = start_symbol;

    if (S.empty())
    {
        std::cout << "Error! No start symbol found!\n";
        return;
    }

    std::set<std::string> H_prev;
    std::set<std::string> H_curr;
    H_curr.insert(S);
    int i = 0;

    bool changed = true;
    while (changed)
    {
        i++;
        H_prev = H_curr;

        for (const auto &pair : P)
        {
            std::string X = pair.first;

            if (H_curr.find(X) != H_curr.end())
            {
                for (const auto &production : pair.second)
                {
                    if (production == "λ")
                        continue;

                    for (char c : production)
                        H_curr.insert(std::string(1, c));
                }
            }
        }

        if (H_curr == H_prev)
            changed = false;
    }

    int idx = 0;
    for (const auto &symbol : H_curr)
        if (idx < 60)
            H[idx++] = symbol;
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
        return;

    for (const auto &kv : P)
    {
        for (const auto &prod : kv.second)
        {
            std::cout << kv.first << "->" << prod << " $ ";
        }
    }
    std::cout << "&";
}

void compute_all(Symbols &sym)
{
    clear_arr(sym.H, 60);
    clear_arr(sym.VN2, 26);
    clear_arr(sym.VT2, 26);
    clear_arr(sym.inacc_syms, 60);
    sym.sym_idx = 0;

    calculate_H(sym.VN, sym.VT, sym.P, sym.H, sym.start_symbol);

    result_VN(sym.VN, sym.H, sym.VN2, sym.inacc_syms, sym.sym_idx);
    result_VT(sym.VT, sym.H, sym.VT2, sym.inacc_syms, sym.sym_idx);
}

std::string trim(std::string s)
{
    auto notSpace = [](unsigned char c)
    { return !std::isspace(c); };
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), notSpace));
    s.erase(std::find_if(s.rbegin(), s.rend(), notSpace).base(), s.end());
    return s;
}

bool add_unique_symbol(std::string arr[26], const std::string &sym)
{
    if (sym.size() != 1)
        return false;

    for (int i = 0; i < 26; i++)
        if (arr[i] == sym)
            return true;

    for (int i = 0; i < 26; i++)
        if (arr[i].empty())
        {
            arr[i] = sym;
            return true;
        }

    return false;
}

bool is_terminal_token(const std::string &tok)
{
    if (tok.size() != 1)
        return false;
    char c = tok[0];
    return (std::islower((unsigned char)c) ||
            c == '(' || c == ')' || c == '+' || c == '*' || c == '-');
}

bool vn_contains(const std::string VN[26], const std::string &s)
{
    for (int i = 0; i < 26; i++)
        if (VN[i] == s)
            return true;
    return false;
}

// Reads ONLY VN and VT from file
bool read_VN_VT_from_file(const std::string &file, Symbols &sym)
{
    std::ifstream fin(file);
    if (!fin.is_open())
    {
        std::cout << "Error: Cannot open file: " << file << "\n";
        return false;
    }

    clear_arr(sym.VN, 26);
    clear_arr(sym.VT, 26);

    std::string line;
    int lineNo = 0;

    while (std::getline(fin, line))
    {
        lineNo++;
        line = trim(line);
        if (line.empty())
            continue;
        if (line[0] == '#')
            continue;

        // VN
        if (line.rfind("VN:", 0) == 0 || line.rfind("VN=", 0) == 0)
        {
            size_t pos = line.find(':');
            if (pos == std::string::npos)
                pos = line.find('=');

            std::stringstream ss(trim(line.substr(pos + 1)));
            std::string tok;
            while (ss >> tok)
            {
                if (tok.size() == 1 && std::isupper((unsigned char)tok[0]))
                    add_unique_symbol(sym.VN, tok);
                else
                    std::cout << "[Line " << lineNo << "] Invalid VN symbol ignored: " << tok << "\n";
            }
            continue;
        }

        // VT
        if (line.rfind("VT:", 0) == 0 || line.rfind("VT=", 0) == 0)
        {
            size_t pos = line.find(':');
            if (pos == std::string::npos)
                pos = line.find('=');

            std::stringstream ss(trim(line.substr(pos + 1)));
            std::string tok;
            while (ss >> tok)
            {
                if (is_terminal_token(tok))
                    add_unique_symbol(sym.VT, tok);
                else
                    std::cout << "[Line " << lineNo << "] Invalid VT symbol ignored: " << tok << "\n";
            }
            continue;
        }
    }

    bool hasVN = false;
    for (int i = 0; i < 26; i++)
        if (!sym.VN[i].empty())
        {
            hasVN = true;
            break;
        }

    if (!hasVN)
    {
        std::cout << "Error: VN is empty after reading the file.\n";
        return false;
    }

    return true;
}

// Reset grammar + results (so we can load a new grammar safely)
void reset_all(Symbols &sym)
{
    sym.P.clear();

    clear_arr(sym.VN, 26);
    clear_arr(sym.VT, 26);

    clear_arr(sym.H, 60);
    clear_arr(sym.VN2, 26);
    clear_arr(sym.VT2, 26);
    clear_arr(sym.inacc_syms, 60);
    sym.sym_idx = 0;

    sym.start_symbol.clear();
}

// Loads VN/VT (file or keyboard), then start symbol, then P (keyboard)
bool load_grammar_interactive(Symbols &sym)
{
    reset_all(sym);

    std::cout << "Load VN and VT from:\n";
    std::cout << "  1) Keyboard input (any key)\n";
    std::cout << "  2) File (VN and VT only) (2)\n";
    std::cout << "Choose (1/2): ";

    int mode = 1;
    std::cin >> mode;

    if (mode == 2)
    {
        std::cout << "Enter file name (example: symbols.txt): ";
        std::string filename;
        std::cin >> filename;

        if (!read_VN_VT_from_file(filename, sym))
        {
            std::cout << "File reading failed.\n";
            return false;
        }

        std::cout << "VN and VT successfully read from file.\n";
        print_arr(sym.VN, 26, "VN");
        print_arr(sym.VT, 26, "VT");
    }
    else
    {
        std::cout << "=== STEP 1: Initialize VN (non-terminals) ===\n";
        std::cout << "Enter VN symbols (uppercase). Stop with an invalid character.\n";
        init_VN(sym.VN);

        std::cout << "\n=== STEP 2: Initialize VT (terminals) ===\n";
        std::cout << "Enter VT symbols (lowercase and operators: ( ) + * -). Stop with an invalid character.\n";
        init_VT(sym.VT);
    }

    // Start symbol
    sym.start_symbol = sym.VN[0];
    std::cout << "Start symbol: " << sym.start_symbol << std::endl;

    // Productions
    std::cout << "\n=== STEP 3: Initialize P (production rules) ===\n";
    std::cout << "Enter productions manually.\n";
    std::cout << "Note: you can type 'lambda' or 'λ' for the empty production.\n";
    init_P(sym.VN, sym.VT, sym.P);

    return true;
}