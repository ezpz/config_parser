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
    long x = cfg.Get< long >("Number", "x");
    std::cout << "Number::x   : " << x << "\n";
    std::vector< long > xs = cfg.Get< std::vector< long > >("Vector", "xs");
    for (std::string::size_type i = 0; i < xs.size (); ++i) {
        std::cout << " xs[" << i << "] : " << xs[i] << std::endl;
    }
    std::cout << "Bottom::key : '" << cfg.Get ("Bottom", "key") << "'" 
        << std::endl;
    if (cfg.Get< bool > ("Bool", "y")) {
        std::cout << "Bool::y   : true" << std::endl;
    } else {
        std::cout << "Bool::y   : false" << std::endl;
    }
    return 0;
}
