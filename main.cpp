#include "symbols_cfg.h"

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
bool simbol_valid(const std::string& s, std::string VN[26], std::string VT[26])
{
    for (int i = 0; i < 26; i++)
    {
        if (VN[i] == s || VT[i] == s)
            return true;
    }
    return false;
}

// function to add all P variables
void init_P(std::string VN[26], std::string VT[26], std::map<std::string, std::vector<std::string>>& P)
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
void result_P(std::map<std::string, std::vector<std::string>>& P, std::string H[60], std::map<std::string, std::vector<std::string>>& P2)
{
}

int main()
{
    Symbols sym; // structura care contine toate simbolurile și producțiile

    // 1️⃣ Introdu VN obligatoriu
    std::cout << "Introdu VN (simboluri neterminale majuscule):\n";
    init_VN(sym.VN);

    // 2️⃣ Introdu VT obligatoriu
    std::cout << "Introdu VT (simboluri terminale minuscule):\n";
    init_VT(sym.VT);

    // 3️⃣ Introdu P obligatoriu
    std::cout << "Introdu productii (P):\n";
    init_P(sym.VN, sym.VT, sym.P);

    // 4️⃣ Calculeaza VN2, VT2 si P2
    result_VN(sym.VN, sym.H, sym.VN2);
    result_VT(sym.VT, sym.H, sym.VT2);
    result_P(sym.P, sym.H, sym.P2);

    // 5️⃣ Meniu pentru afisare si iesire
    bool running = true;
    while (running)
    {
        std::cout << "\n===== Meniu =====\n";
        std::cout << "1. Afiseaza VN\n";
        std::cout << "2. Afiseaza VT\n";
        std::cout << "3. Afiseaza P\n";
        std::cout << "4. Afiseaza VN2\n";
        std::cout << "5. Afiseaza VT2\n";
        std::cout << "6. Afiseaza P2\n";
        std::cout << "7. Iesi\n";
        std::cout << "Alege o optiune: ";

        int opt;
        std::cin >> opt;

        switch (opt)
        {
        case 1:
            std::cout << "\nVN: ";
            for (int i = 0; i < 26; i++)
            {
                if (!sym.VN[i].empty())
                    std::cout << sym.VN[i] << " ";
            }
            std::cout << "\n";
            break;
        case 2:
            std::cout << "\nVT: ";
            for (int i = 0; i < 26; i++)
            {
                if (!sym.VT[i].empty())
                    std::cout << sym.VT[i] << " ";
            }
            std::cout << "\n";
            break;
        case 3:
            std::cout << "\nP (productii):\n";
            for (auto& kv : sym.P)
            {
                std::cout << kv.first << " -> ";
                for (auto& prod : kv.second)
                    std::cout << prod << " | ";
                std::cout << "\n";
            }
            break;
        case 4:
            std::cout << "\nVN2: ";
            for (int i = 0; i < 26; i++)
            {
                if (!sym.VN2[i].empty())
                    std::cout << sym.VN2[i] << " ";
            }
            std::cout << "\n";
            break;
        case 5:
            std::cout << "\nVT2: ";
            for (int i = 0; i < 26; i++)
            {
                if (!sym.VT2[i].empty())
                    std::cout << sym.VT2[i] << " ";
            }
            std::cout << "\n";
            break;
        case 6:
            std::cout << "\nP2 (productii rezultate):\n";
            for (auto& kv : sym.P2)
            {
                std::cout << kv.first << " -> ";
                for (auto& prod : kv.second)
                    std::cout << prod << " | ";
                std::cout << "\n";
            }
            break;
        case 7:
            running = false;
            std::cout << "Iesire din program.\n";
            break;
        default:
            std::cout << "Optiune invalida!\n";
            break;
        }
    }

    return 0;
}