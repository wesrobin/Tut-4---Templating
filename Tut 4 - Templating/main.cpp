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
    std::cout << cnn.encode("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 2) << std::endl;
    std::cout << cnn.decode("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 2) << std::endl << std::endl;

    Crypt<vigenere, no_packing, no_grouping> vnn;
    std::cout << vnn.encode("ATTACKATDAWN", "LEMONLEMONLE") << std::endl;
    std::cout << vnn.decode("LXFOPVEFRNHR", "LEMONLEMONLE") << std::endl;
    return 0;
}

