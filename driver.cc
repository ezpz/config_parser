#include <iostream>
#include "config_parser.hh"

int main (int argc, char **argv) {
    const char *fname = "example.cfg";
    if (2 == argc) {
        fname = argv[1];
    }

    ConfigFile cfg(fname);
    std::cout << "::global    : '" << cfg.Get ("global") << "'\n";
    std::cout << "Top::key1   : '" << cfg.Get ("Top", "key1") << "'\n";
    std::cout << "Top::key2   : '" << cfg.Get ("Top", "key2") << "'\n";
    std::cout << "Top::key3   : '" << cfg.Get ("Top", "key3") << "'\n";
    std::cout << "Top::key4   : '" << cfg.Get ("Top", "key4") << "'\n";
    std::cout << "Top::key5   : '" << cfg.Get ("Top", "key4") << "'\n";
    std::cout << "Bottom::key : '" << cfg.Get ("Bottom", "key") << "'" 
        << std::endl;
    return 0;
}
