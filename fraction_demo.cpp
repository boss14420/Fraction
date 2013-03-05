/*
 * =====================================================================================
 *
 *       Filename:  fraction_demo.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/22/2012 12:59:14 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BOSS14420 (boss14420), boss14420@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "fraction.hh"
#include <iostream>
#include <string>
#include <cstdlib>
//#include <unordered_map>

int main(int argc, char *argv[]) {
    if(argc == 3) {
        int a = std::atoi(argv[1]);
        int b = std::atoi(argv[2]);

        boss14420::Fraction f(a,b);
        std::string str1, str2;
        f.decimalization(str1, str2);

        std::cout << "First 500 digit " << f.toString(500) << '\n';
        std::cout << "\nFull decimalization: " << f.toString() << '\n';

//        std::cout << "repeating sequence length " 
//            << str2.length() << std::endl;

        return EXIT_SUCCESS;
    }
    
    return EXIT_FAILURE;
}
