/* 
 * Wesley Robinson - RBNWES001
 * main.cpp
 * Tut 4 - Templating
 * Program to demonstrate the use of Templating to implement various ciphers which can
 * be used to encrypt and decrypt text.
 * Created on 07 May 2013, 1:10 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ostream>
#include <boost/algorithm/string.hpp>
#include <string>

#include "Crypt.h"
#include "Type.h"
#include "cmdline_parser.h"

using namespace std;

int main(int argc, char** argv) {

    cmdline_parser parser; //Initialise the parser

    if (!parser.process_cmdline(argc, argv)) { //Try parse cmdline args
        cerr << "Couldn't process command line arguments" << endl;
    }

    if (parser.should_print_help()) {   //Print help if requested
        parser.print_help(std::cout);
    }
    
    string encodable = "";      //The string that holds the text to run ciphers on
    string inputFileName = parser.get_input_filename();
    string outputFileName = parser.get_output_filename();
    cout << "Output file in use: " << outputFileName << endl;
    
    if (!parser.should_get_user_input()) {

        

        cout << "Input file in use: " << inputFileName << endl;
        


        string temp;
        ifstream inpFileStream;

        inpFileStream.open(inputFileName);


        if (inpFileStream.is_open()) {

            while (!inpFileStream.eof()) { //Read from file into string encodable
                getline(inpFileStream, temp);
                encodable += temp;
            }
        }


        inpFileStream.close();
    }
    else {
        cout << "Please enter the text you want to pass to the cipher: ";
        getline (cin, encodable);
    }

    boost::to_upper(encodable);
    
    string returnStr = "";
    
    if (parser.using_caesar()) {
        int key = parser.get_caesar_key();
        if (parser.should_pack()) {     //Will return "Not implemented"
            if (parser.should_group()) {
                if (parser.should_encode()) { 
                    Crypt<caesar, packing, grouping> crypt; 
                    returnStr = crypt.encode(encodable, key);
                }
                else {
                    Crypt<caesar, packing, grouping> crypt; 
                    returnStr = crypt.decode(encodable, key);
                }
            }
            else {
                if (parser.should_encode()) { 
                    Crypt<caesar, packing, no_grouping> crypt; 
                    returnStr = crypt.encode(encodable, key); 
                }
                else {
                    Crypt<caesar, packing, no_grouping> crypt; 
                    returnStr = crypt.decode(encodable, key); 
                }
            }
        }
        else {
            if (parser.should_group()) {
                if (parser.should_encode()) { 
                    Crypt<caesar, no_packing, grouping> crypt; 
                    returnStr = crypt.encode(encodable, key);
                }
                else {
                    Crypt<caesar, no_packing, grouping> crypt; 
                    returnStr = crypt.decode(encodable, key);
                }
            }
            else {
                if (parser.should_encode()) { 
                    Crypt<caesar, no_packing, no_grouping> crypt; 
                    returnStr = crypt.encode(encodable, key); 
                }
                else {
                    Crypt<caesar, no_packing, no_grouping> crypt; 
                    returnStr = crypt.decode(encodable, key); 
                }
            }
        }
    }
    else if (parser.using_vigenere()) {
        string key = parser.get_vigenere_key();
        if (parser.should_pack()) {     //Will return "Not implemented"
            if (parser.should_group()) {
                if (parser.should_encode()) { 
                    Crypt<vigenere, packing, grouping> crypt; 
                    returnStr = crypt.encode(encodable, key);
                }
                else {
                    Crypt<vigenere, packing, grouping> crypt; 
                    returnStr = crypt.decode(encodable, key);
                }
            }
            else {
                if (parser.should_encode()) { 
                    Crypt<vigenere, packing, no_grouping> crypt; 
                    returnStr = crypt.encode(encodable, key); 
                }
                else {
                    Crypt<vigenere, packing, no_grouping> crypt; 
                    returnStr = crypt.decode(encodable, key); 
                }
            }
        }
        else {
            if (parser.should_group()) {
                if (parser.should_encode()) { 
                    Crypt<vigenere, no_packing, grouping> crypt; 
                    returnStr = crypt.encode(encodable, key);
                }
                else {
                    Crypt<vigenere, no_packing, grouping> crypt; 
                    returnStr = crypt.decode(encodable, key);
                }
            }
            else {
                if (parser.should_encode()) { 
                    Crypt<vigenere, no_packing, no_grouping> crypt; 
                    returnStr = crypt.encode(encodable, key); 
                }
                else {
                    Crypt<vigenere, no_packing, no_grouping> crypt; 
                    returnStr = crypt.decode(encodable, key); 
                }
            }
        }
    }
    else if (parser.using_XOR()) {
        int32_t key = parser.get_XOR_key();
        if (parser.should_pack()) {     //Will return "Not implemented"
            if (parser.should_group()) {
                if (parser.should_encode()) { 
                    Crypt<XOR, packing, grouping> crypt; 
                    returnStr = crypt.encode(encodable, key);
                }
                else {
                    Crypt<XOR, packing, grouping> crypt; 
                    returnStr = crypt.decode(encodable, key);
                }
            }
            else {
                if (parser.should_encode()) { 
                    Crypt<XOR, packing, no_grouping> crypt; 
                    returnStr = crypt.encode(encodable, key); 
                }
                else {
                    Crypt<XOR, packing, no_grouping> crypt; 
                    returnStr = crypt.decode(encodable, key); 
                }
            }
        }
        else {
            if (parser.should_group()) {
                if (parser.should_encode()) { 
                    Crypt<XOR, no_packing, grouping> crypt; 
                    returnStr = crypt.encode(encodable, key);
                }
                else {
                    Crypt<XOR, no_packing, grouping> crypt; 
                    returnStr = crypt.decode(encodable, key);
                }
            }
            else {
                if (parser.should_encode()) { 
                    Crypt<XOR, no_packing, no_grouping> crypt; 
                    returnStr = crypt.encode(encodable, key); 
                }
                else {
                    Crypt<XOR, no_packing, no_grouping> crypt; 
                    returnStr = crypt.decode(encodable, key); 
                }
            }
        }
    }
    
    ofstream outFileStream;
    outFileStream.open(outputFileName);
    
    outFileStream << returnStr;

    //    Crypt<caesar, no_packing, no_grouping> cnn;
    //    std::cout << cnn.encode("I AM IN LOVE WITH A FARTY SOUND", 1000) << std::endl;
    //    std::cout << cnn.decode("U MY UZ XAHQ IUFT M RMDFK EAGZP", 1000) << std::endl << std::endl;
    //    
    //    Crypt<caesar, no_packing, grouping> cng;
    //    std::cout << cng.encode("I AM IN LOVE WITH A FARTY SOUND", 1000) << std::endl;
    //    std::cout << cng.decode("UMYUZXAHQIUFTMR MDFKE AGZP", 1000) << std::endl << std::endl;
    //
    //    Crypt<vigenere, no_packing, no_grouping> vnn;
    //    std::cout << vnn.encode("I AM IN LOVE WITH A FARTY SOUND", "LEMON") << std::endl;
    //    std::cout << vnn.decode("T EY WA WSHS JTXT O SLVFM FZYZR", "LEMON") << std::endl << std::endl;
    //    
    //    Crypt<vigenere, no_packing, grouping> vng;
    //    std::cout << vng.encode("I AM IN LOVE WITH A FARTY SOUND", "LEMON") << std::endl;
    //    std::cout << vng.decode("TEYWA WSHSJ TXTOS LVFMF ZYZR", "LEMON") << std::endl << std::endl;
    //    
    //    Crypt<XOR, no_packing, no_grouping> xnn;
    //    std::cout << xnn.encode("MATTHEWWOODISACUNT", 1) << std::endl;
    //    std::cout << xnn.decode("LATTIEWWNODIRACUOT", 1) << std::endl << std::endl;
    //    
    //    Crypt<XOR, no_packing, grouping> xng;
    //    std::cout << xng.encode("MATTHEWW OODISA CUNT", 1) << std::endl;
    //    std::cout << xng.decode("LATTI EWVOO EISAB UNU", 1) << std::endl << std::endl;

    return 0;
}

