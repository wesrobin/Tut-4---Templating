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
    
    std::cout << cnn.encode() << std::endl;
    return 0;
}

