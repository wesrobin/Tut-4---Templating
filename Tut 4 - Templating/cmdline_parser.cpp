/* 
 * Wesley Robinson - RBNWES001
 * cmdline_parser.cpp
 * cmdline_parser program for Tut 4
 * Created on 08 May 2013, 02:32 AM
 * Uses base code given by Simon Perkins as part of assignment brief
 */

#include "cmdline_parser.h"
#include <cstdint>


// Definition of static strings in the class
const std::string cmdline_parser::INPUTFILE = "input file";
const std::string cmdline_parser::OUTPUTFILE = "output file";
const std::string cmdline_parser::USERINPUT = "user input";
const std::string cmdline_parser::ENCODE = "encoding";
const std::string cmdline_parser::DECODE = "decoding";
const std::string cmdline_parser::CKEY = "Caesar key";
const std::string cmdline_parser::VKEY = "Vignere key";
const std::string cmdline_parser::XKEY = "XOR key";
const std::string cmdline_parser::GROUP = "grouping";
const std::string cmdline_parser::PACK = "packing";

//-------------------------------------------------------------------------//
// Constructor, initialise the variables_map object with default
// constructor, options_descriptor with the name "Options"
//-------------------------------------------------------------------------//

cmdline_parser::cmdline_parser(void) : vm(), od("Options") {
    // Shorter alias for the boost::program_options namespace
    namespace po = boost::program_options;

    // Add two cmdline options
    // --help or -?
    // --input-file or -i
    od.add_options()
            ("help,?", "show usage help")

            ((INPUTFILE + ",i").c_str(), po::value<std::string>(), "input file name")
            ((OUTPUTFILE + ",o").c_str(), po::value<std::string>(), "output file name")
            ((USERINPUT + ",u").c_str(), "use user input for cipher text")
            ((ENCODE + ",e").c_str(), "encode string")
            ((DECODE + ",d").c_str(), "decode string")
            ((XKEY + ",x").c_str(), po::value<int32_t>(), "XOR cipher Encode/Decode with specifed key")
            ((VKEY + ",v").c_str(), po::value<std::string>(), "Vignere cipher Encode/Decode with specifed key")
            ((CKEY + ",c").c_str(), po::value<int>(), "Caesar cipher Encode/Decode using specifed key")
            ((GROUP + ",g").c_str(), "group input into blocks")
            ((PACK + ",p").c_str(), "char bit packing (NOT IMPLEMENTED, WILL NOT WORK)");
};

//-------------------------------------------------------------------------//
// Process the cmdline
//-------------------------------------------------------------------------//

bool cmdline_parser::process_cmdline(int argc, char * argv[]) {
    // Shorter alias for the boost::program_options namespace
    namespace po = boost::program_options;

    // Clear the variable map
    vm.clear();

    // Parse the cmdline arguments defined by argc and argv,
    // looking for the options defined in the od variable,
    // and store them in the vm variable.
    po::store(po::parse_command_line(argc, argv, od), vm);
    po::notify(vm);

    bool success = true;

    //One of either encode or decode must be defined
    if (vm.count(ENCODE) + vm.count(DECODE) == 1) {
        //Check if valid number of cyphers given
        if (vm.count(XKEY) + vm.count(VKEY) + vm.count(CKEY) != 1) {
            success = false;
            errors.push_back("Incorrect number of ciphers, please give only one");
        }
    } else {
        //Neither or both specified error
        success = false;
        errors.push_back("Must specify whether to encode (-e) or decode (-d)");
    }

    return success;

}

//--------------------------------Methods-------------------------------//
//Files

/**Get Input File
 * 
 * returns the file name of the input file
 */
std::string cmdline_parser::get_input_filename(void) const {
    if (vm.count(INPUTFILE) == 0)//If unspecified return defaultin.txt
        return "input.txt";
    return vm[INPUTFILE].as<std::string>();
}

/**Get Output File
 * 
 * returns the file name of the output file
 */
std::string cmdline_parser::get_output_filename(void) const {
    if (vm.count(OUTPUTFILE) == 0)//If unspecified return defaultout.txt
        return "output.txt";
    return vm[OUTPUTFILE].as<std::string>();
}

bool cmdline_parser::should_get_user_input(void) {
    return vm.count(USERINPUT) > 0;
}

//Encoding

/**Should Encode?
 * 
 * returns true if encoding should be done else returns false
 */
bool cmdline_parser::should_encode(void) {
    return vm.count(ENCODE) > 0;
}

/**Should Decode?
 * 
 * returns true if decoding should be done else returns false
 */
bool cmdline_parser::should_decode(void) {
    return vm.count(DECODE) > 0;
}

//Cyphers

/**Get XOR Key
 * 
 * returns the XOR key specified
 */
int32_t cmdline_parser::get_XOR_key(void) {
    return vm[XKEY].as<int32_t>();
}

/**Get vignere Key
 * 
 * returns the vignere key specified
 */
std::string cmdline_parser::get_vigenere_key(void) {
    return vm[VKEY].as<std::string>();
}

/**Get caesar Key
 * 
 * returns the caesar key specified
 */
int cmdline_parser::get_caesar_key(void) {
    return vm[CKEY].as<int>();
}

//Grouping and Packing

/**Should group?
 * 
 * returns true if told to group else false
 */
bool cmdline_parser::should_group(void) {
    return vm.count(GROUP) > 0;
}

/**Should pack?
 * 
 * returns true if told to pack else false
 */
bool cmdline_parser::should_pack(void) {
    return vm.count(PACK) > 0;
}

//Cypher Use

/**Using xor?
 * 
 * returns true if told to use xor else false
 */
bool cmdline_parser::using_XOR(void) {
    return vm.count(XKEY) > 0;
}

/**Using vignere?
 * 
 * returns true if told to use vignere else false
 */
bool cmdline_parser::using_vigenere(void) {
    return vm.count(VKEY) > 0;
}

/**Using caesar?
 * 
 * returns true if told to use caesar else false
 */
bool cmdline_parser::using_caesar(void) {
    return vm.count(CKEY) > 0;
}

//------------------------------End Methods-----------------------------//

//----------------------------------------------------------------------//
// Should we print cmdline help?
//----------------------------------------------------------------------//

bool cmdline_parser::should_print_help(void) const {
    // Are there instances of the help option stored in the variable map
    return vm.count("help") > 0;
}

//----------------------------------------------------------------------//
// Print out the options_descriptor to the supplied output stream
//----------------------------------------------------------------------//

void cmdline_parser::print_help(std::ostream & out) const {
    out << od;
}

//----------------------------------------------------------------------//
// Print out the options_descriptor to the supplied output stream
//----------------------------------------------------------------------//

void cmdline_parser::print_errors(std::ostream & out) const {
    std::cerr << "Error processing command line arguments:" << std::endl;
    std::copy(errors.begin(), errors.end(),
            std::ostream_iterator<std::string>(out, "\n"));
}
