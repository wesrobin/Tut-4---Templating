/* 
 * File:   main.cpp
 * Author: wesley
 *
 * Created on 07 May 2013, 1:10 PM
 */

#include <cstdlib>
#include <iostream>

#include "Crypt.h"
#include "Type.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    Crypt<caesar, no_packing, no_grouping> cnn;
    std::cout << cnn.encode("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 1000) << std::endl;
    std::cout << cnn.decode("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 1000) << std::endl << std::endl;
    
    Crypt<caesar, no_packing, grouping> cng;
    std::cout << cng.encode("ABCDEFGH IJKL  MNOPQR STUVWX YZ", 1000) << std::endl;
    std::cout << cng.decode("ABCDEFGH IJKL  MNOPQR STUVWX YZ", 1000) << std::endl << std::endl;

    Crypt<vigenere, no_packing, no_grouping> vnn;
    std::cout << vnn.encode("MATTHEWWOODISACUNT", "LEMONLEMONLEMONLEM") << std::endl;
    std::cout << vnn.decode("XEFHUPAICBOMEOPFRF", "LEMONLEMONLEMONLEM") << std::endl << std::endl;
    
    Crypt<XOR, no_packing, no_grouping> xnn;
    std::cout << xnn.encode("MATTHEWWOODISACUNT", 1) << std::endl;
    std::cout << xnn.decode("LATTIEWWNODIRACUOT", 1) << std::endl << std::endl;
    return 0;
}

