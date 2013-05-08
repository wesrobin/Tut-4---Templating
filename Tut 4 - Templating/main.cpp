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
    std::cout << cnn.encode("I AM IN LOVE WITH A FARTY SOUND", 1000) << std::endl;
    std::cout << cnn.decode("U MY UZ XAHQ IUFT M RMDFK EAGZP", 1000) << std::endl << std::endl;
    
    Crypt<caesar, no_packing, grouping> cng;
    std::cout << cng.encode("I AM IN LOVE WITH A FARTY SOUND", 1000) << std::endl;
    std::cout << cng.decode("UMYUZXAHQIUFTMR MDFKE AGZP", 1000) << std::endl << std::endl;

    Crypt<vigenere, no_packing, no_grouping> vnn;
    std::cout << vnn.encode("I AM IN LOVE WITH A FARTY SOUND", "LEMON") << std::endl;
    std::cout << vnn.decode("T EY WA WSHS JTXT O SLVFM FZYZR", "LEMON") << std::endl << std::endl;
    
    Crypt<vigenere, no_packing, grouping> vng;
    std::cout << vng.encode("I AM IN LOVE WITH A FARTY SOUND", "LEMON") << std::endl;
    std::cout << vng.decode("TEYWA WSHSJ TXTOS LVFMF ZYZR", "LEMON") << std::endl << std::endl;
    
    Crypt<XOR, no_packing, no_grouping> xnn;
    std::cout << xnn.encode("MATTHEWWOODISACUNT", 1) << std::endl;
    std::cout << xnn.decode("LATTIEWWNODIRACUOT", 1) << std::endl << std::endl;
    return 0;
}

