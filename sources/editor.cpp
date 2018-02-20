/**
 * @file print_ip.cpp
 * @author DGolgovsky
 * @date 2018
 * @brief OTUS C++ homework #4
 *
 * Print ip addresses represented in different ways.
 */

/**
 * @mainpage
 * The program for printing ip-addresses.
 * The address can be represented as an arbitrary integer type.
 * The representation does not depend on the type sign.
 * Displays the address byte, beginning with the oldest one with the "." symbol, as a separator.
 * The address can be represented as a string. It is displayed as is.
 * The address can be represented in the form of containers std::list, std::vector.
 * The contents of the container are displayed element-by-element and are separated "."
 */

#include <list>
#include <vector>
#include <tuple>
#include "libprinter/printer.h"

/**
 * @brief App's main function
 *
 * Used with all c++ programs to init start
 * Main function to demonstrate print_ip
 */
int main(int, char const **)
{
    /**
     * @brief Task Condition
     * Печать адреса как char(-1)
     * Печать адреса как short(0)
     * Печать адреса как int(2130706433)
     * Печать адреса как long(8875824491850138409)
     * Печать адреса как std::string
     * Печать адреса как std::vector
     * Печать адреса как std::list
     * Опционально. Печать адреса как std::tuple
     */

    print_ip(char(-1));
    print_ip(short(0));
    print_ip(int(2130706433));
    print_ip(long(8875824491850138409));

    print_ip(std::string("255.255.255.255"));
    print_ip(std::vector<int>{172, 31, 19, 63});
    print_ip(std::list<int>{192, 168, 1, 42});

    print_ip(std::make_tuple(10, 15, 2, 101));

    return 0;
}
