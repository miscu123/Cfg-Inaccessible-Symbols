#include "symbols_cfg.hpp"

int main()
{
    Symbols sym;

    // MANDATORY INPUT BEFORE MENU
    std::cout << "=== STEP 1: Initialize VN (non-terminals) ===\n";
    std::cout << "Enter VN (uppercase). Stop with an invalid character (e.g., 0).\n";
    init_VN(sym.VN);
    sym.start_symbol = sym.VN[0];

    std::cout << "\n=== STEP 2: Initialize VT (terminals) ===\n";
    std::cout << "Enter VT (lowercase). Stop with an invalid character (e.g., 0).\n";
    init_VT(sym.VT);

    std::cout << "\n=== STEP 3: Initialize P (production rules) ===\n";
    std::cout << "Enter productions.\n";
    init_P(sym.VN, sym.VT, sym.P);

    // After VN/VT/P are entered, show the menu
    bool running = true;
    // Flag to track if results are up to date
    bool computed = false;

    while (running)
    {
        std::cout << "\n=============================\n";
        std::cout << "             MENU\n";
        std::cout << "=============================\n";
        std::cout << "1. Display VN\n";
        std::cout << "2. Display VT\n";
        std::cout << "3. Display P\n";
        std::cout << "4. Compute (H, VN2, VT2) + inaccessible symbols\n";
        std::cout << "5. Display H\n";
        std::cout << "6. Display VN2\n";
        std::cout << "7. Display VT2\n";
        std::cout << "8. Display inaccessible symbols\n";
        std::cout << "9. Display ALL (VN, VT, P, H, VN2, VT2, inaccessible)\n";
        std::cout << "0. Exit\n";
        std::cout << "Choose an option: ";

        int opt;
        std::cin >> opt;

        switch (opt)
        {
        case 1:
            print_arr(sym.VN, 26, "VN");
            break;

        case 2:
            print_arr(sym.VT, 26, "VT");
            break;

        case 3:
            print_P(sym.P);
            break;

        case 4:
            compute_all(sym);
            computed = true;
            std::cout << "Done: H, VN2, VT2, and the inaccessible symbols list were computed.\n";
            break;

        case 5:
            if (!computed)
                std::cout << "H is not computed. Run option 4 first.\n";
            else
                print_arr(sym.H, 60, "H");
            break;

        case 6:
            if (!computed)
                std::cout << "VN2 is not computed. Run option 4 first.\n";
            else
                print_arr(sym.VN2, 26, "VN2");
            break;

        case 7:
            if (!computed)
                std::cout << "VT2 is not computed. Run option 4 first.\n";
            else
                print_arr(sym.VT2, 26, "VT2");
            break;

        case 8:
            if (!computed)
                std::cout << "Inaccessible symbols list is not computed. Run option 4 first.\n";
            else
                print_arr(sym.inacc_syms, 60, "Inaccessible symbols ");
            break;

        case 9:
            print_arr(sym.VN, 26, "VN");
            print_arr(sym.VT, 26, "VT");
            print_P(sym.P);

            if (!computed)
            {
                std::cout << "\n(Results H/VN2/VT2/inaccessible are not computed)\n";
                std::cout << "Run option 4 first.\n";
            }
            else
            {
                std::cout << "\n";
                print_arr(sym.H, 60, "H");
                print_arr(sym.VN2, 26, "VN2");
                print_arr(sym.VT2, 26, "VT2");
                print_arr(sym.inacc_syms, 60, "Inaccessible symbols ");
            }
            break;

        case 0:
            running = false;
            std::cout << "Exiting the program.\n";
            break;

        default:
            std::cout << "Invalid option!\n";
            break;
        }
    }

    return 0;
}
