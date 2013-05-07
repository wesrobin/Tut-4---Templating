//Author: David Harris
//Student Number: HRRDAV010
//Date: 05/07/2013
//Description: 	command line parser for tutorial 4
//
//References: Uses code given by Simon Perkins

#include "cmdline_parser.h"
#include <cstdint>

//-------------------------------------------------------------------------//
// Constructor, initialise the variables_map object with default
// constructor, options_descriptor with the name "Options"
//-------------------------------------------------------------------------//
cmdline_parser::cmdline_parser(void) : vm(), od("Options")
{
	// Shorter alias for the boost::program_options namespace
	namespace po = boost::program_options;

	// Add two cmdline options
	// --help or -?
	// --input-file or -i
	od.add_options()
		("help,?", "produce help message")
		
		((INPUTFILE+",i").c_str(), po::value<std::string>(),"input file name")
		((OUTPUTFILE+",o").c_str(), po::value<std::string>(),"output file name")
		((ENCODING+",e").c_str(), "encoding should be performed")
		((DECODING+",d").c_str(), "decoding should be performed")
		((XKEY+",x").c_str(), po::value<int32_t>(),"Encode/Decode with XOR cipher using specifed key")
		((VKEY+",v").c_str(), po::value<std::string>(),"Encode/Decode with Vignere cipher using specifed key")
		((CKEY+",c").c_str(), po::value<int>(),"Encode/Decode with Caesar cipher using specifed key")
		((GROUPING+",g").c_str(),"support for grouping into code blocks")
		((PACKING+",p").c_str(),"support for bit packing");
};

//-------------------------------------------------------------------------//
// Process the cmdline
//-------------------------------------------------------------------------//
bool cmdline_parser::process_cmdline(int argc, char * argv[])
{
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

	//Check if either encode or decode is given
	if(vm.count(ENCODING) + vm.count(DECODING) ==1)
	{
		//Check if valid number of cyphers given
		if(vm.count(XKEY) + vm.count(VKEY) + vm.count(CKEY) != 1)
		{
			success = false;
			errors.push_back("Incorrect number of cyphers specified");
		}
	}
	else
	{
		//Neither or both specified error
		success = false;
		errors.push_back("Either Encode (-e) or Decode (-d) must be specified");
	}

	return success;
	
}

//--------------------------------Methods-------------------------------//
//Files
/**Get Input File
 * 
 * returns the file name of the input file
 */
std::string cmdline_parser::get_input_filename(void) const
{
	if(vm.count(INPUTFILE)==0)//If unspecified return defaultin.txt
		return "defaultin.txt";
	return vm[INPUTFILE].as<std::string>();
}
/**Get Output File
 * 
 * returns the file name of the output file
 */
std::string cmdline_parser::get_output_filename(void) const
{
	if(vm.count(INPUTFILE)==0)//If unspecified return defaultout.txt
		return "defaultout.txt";
	return vm[OUTPUTFILE].as<std::string>();
}

//Encoding
/**Should Encode?
 * 
 * returns true if encoding should be done else returns false
 */
bool cmdline_parser::should_encode(void)
{
	return vm.count(ENCODING)>0;
}
/**Should Decode?
 * 
 * returns true if decoding should be done else returns false
 */
bool cmdline_parser::should_decode(void)
{
	return vm.count(DECODING)>0;
}

//Cyphers
/**Get xor Key
 * 
 * returns the xor key specified
 */
int cmdline_parser::get_xor_key(void)
{
	return vm[XKEY].as<int>();
}
/**Get vignere Key
 * 
 * returns the vignere key specified
 */
std::string cmdline_parser::get_vignere_key(void)
{
	return vm[VKEY].as<std::string>();
}
/**Get caesar Key
 * 
 * returns the caesar key specified
 */
int cmdline_parser::get_caesar_key(void)
{
	return vm[CKEY].as<int>();
}

//Grouping and Packing
/**Should group?
 * 
 * returns true if told to group else false
 */
bool cmdline_parser::should_group(void)
{
	return vm.count(GROUPING)>0;
}
/**Should pack?
 * 
 * returns true if told to pack else false
 */
bool cmdline_parser::should_pack(void)
{
	return vm.count(PACKING)>0;
}

//Cypher Use
/**Using xor?
 * 
 * returns true if told to use xor else false
 */
bool cmdline_parser::using_xor(void)
{
	return vm.count(XKEY)>0;
}
/**Using vignere?
 * 
 * returns true if told to use vignere else false
 */
bool cmdline_parser::using_vignere(void)
{
	return vm.count(VKEY)>0;
}
/**Using caesar?
 * 
 * returns true if told to use caesar else false
 */
bool cmdline_parser::using_caesar(void)
{
	return vm.count(CKEY)>0;
}

//------------------------------End Methods-----------------------------//

//----------------------------------------------------------------------//
// Should we print cmdline help?
//----------------------------------------------------------------------//
bool cmdline_parser::should_print_help(void) const
{
	// Are there instances of the help option stored in the variable map
	return vm.count("help") > 0;
}

//----------------------------------------------------------------------//
// Print out the options_descriptor to the supplied output stream
//----------------------------------------------------------------------//
void cmdline_parser::print_help(std::ostream & out) const
{
	out << od;
}

//----------------------------------------------------------------------//
// Print out the options_descriptor to the supplied output stream
//----------------------------------------------------------------------//
void cmdline_parser::print_errors(std::ostream & out) const
{
	std::cerr << "Error processing command line arguments:" << std::endl;
	std::copy(errors.begin(), errors.end(),
		std::ostream_iterator<std::string>(out, "\n"));
}

// Definition of static strings in the class
const std::string cmdline_parser::INPUTFILE = "input-file";
const std::string cmdline_parser::OUTPUTFILE = "output-file";
const std::string cmdline_parser::ENCODING = "encoding";
const std::string cmdline_parser::DECODING = "decoding";
const std::string cmdline_parser::XKEY = "XOR  key";
const std::string cmdline_parser::VKEY = "Vignere key";
const std::string cmdline_parser::CKEY = "Caesar key";
const std::string cmdline_parser::GROUPING = "grouping";
const std::string cmdline_parser::PACKING = "packing";
