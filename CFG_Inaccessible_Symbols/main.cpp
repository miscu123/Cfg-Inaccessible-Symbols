#include "symbols_cfg.hpp"

int main()
{
    Symbols sym;
    bool computed = false;

    // Initial grammar load
    while (true)
    {
        if (load_grammar_interactive(sym))
            break;

        std::cout << "Grammar loading failed. Try again? (y/n): ";
        char r;
        std::cin >> r;
        if (r != 'y' && r != 'Y')
            return 1;
    }

    bool running = true;
    while (running)
    {
        std::cout << "\n=============================\n";
        std::cout << "              MENU\n";
        std::cout << "=============================\n";
        std::cout << "1. Display VN\n";
        std::cout << "2. Display VT\n";
        std::cout << "3. Display P\n";
        std::cout << "4. Compute (H, VN2, VT2) and inaccessible symbols\n";
        std::cout << "5. Display H\n";
        std::cout << "6. Display VN2\n";
        std::cout << "7. Display VT2\n";
        std::cout << "8. Display inaccessible symbols\n";
        std::cout << "9. Display ALL\n";
        std::cout << "10. Load a NEW grammar (VN, VT, start symbol, P)\n";
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
            std::cout << "\n";
            break;

        case 4:
            compute_all(sym);
            computed = true;
            std::cout << "Computation completed successfully.\n";
            break;

        case 5:
            if (!computed)
                std::cout << "H is not computed yet. Run option 4 first.\n";
            else
                print_arr(sym.H, 60, "H");
            break;

        case 6:
            if (!computed)
                std::cout << "VN2 is not computed yet. Run option 4 first.\n";
            else
                print_arr(sym.VN2, 26, "VN2");
            break;

        case 7:
            if (!computed)
                std::cout << "VT2 is not computed yet. Run option 4 first.\n";
            else
                print_arr(sym.VT2, 26, "VT2");
            break;

        case 8:
            if (!computed)
                std::cout << "Inaccessible symbols are not computed yet. Run option 4 first.\n";
            else
                print_arr(sym.inacc_syms, 60, "Inaccessible symbols");
            break;

        case 9:
            print_arr(sym.VN, 26, "VN");
            print_arr(sym.VT, 26, "VT");
            std::cout << "Start symbol: " << sym.start_symbol << "\n";
            print_P(sym.P);
            std::cout << "\n";

            if (computed)
            {
                print_arr(sym.H, 60, "H");
                print_arr(sym.VN2, 26, "VN2");
                print_arr(sym.VT2, 26, "VT2");
                print_arr(sym.inacc_syms, 60, "Inaccessible symbols");
            }
            else
            {
                std::cout << "Results not computed yet. Run option 4.\n";
            }
            break;

        case 10:
        {
            if (load_grammar_interactive(sym))
            {
                computed = false; // invalidate results for the new grammar
                std::cout << "New grammar loaded successfully.\n";
            }
            else
            {
                std::cout << "Failed to load new grammar. The current grammar may have been reset.\n";
                std::cout << "Please load again (option 10).\n";
                computed = false;
            }
            break;
        }

        case 0:
            running = false;
            std::cout << "Exiting program.\n";
            break;

        default:
            std::cout << "Invalid option!\n";
            break;
        }
    }

    return 0;
}