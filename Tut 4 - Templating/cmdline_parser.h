/*
 * cmdline_parser.h
 *
 *  Created on: 22 Feb 2012
 *      Author: simon
 */

#ifndef CMDLINE_PARSER_H_
#define CMDLINE_PARSER_H_

#include <iostream>
#include <list>
#include <string>

#include <boost/program_options.hpp>

//---------------------------------------------------------------------------//
class cmdline_parser
{
public:
    //-----------------------------------------------------------------------//
	// Constructor
	cmdline_parser(void);

	// Member function that parses command line options
	bool process_cmdline(int argc, char * argv[]);
	
	// Return the input filename
	std::string get_input_filename(void) const;
	// Return the output filename
	std::string get_output_filename(void) const;
	// Get vignere key
	std::string get_vignere_key(void);
	
	// Get xor key
	int get_xor_key(void);
	// Get caesar key
	int get_caesar_key(void);
	
	// Should we encode
	bool should_encode(void);
	// Should we decode
	bool should_decode(void);
	// Should we group
	bool should_group(void);
	// Should we pack
	bool should_pack(void);
	
	// Which Cypher
	bool using_xor(void);
	bool using_vignere(void);
	bool using_caesar(void);

	void print_errors(std::ostream & out) const;

	bool should_print_help(void) const;
	// Output help to the specified output stream
	void print_help(std::ostream & out) const;

private:
    //-----------------------------------------------------------------------//
	// Member variables
	boost::program_options::variables_map vm;
	boost::program_options::options_description od;
	std::list<std::string> errors;

    //-----------------------------------------------------------------------//
	// Static string variables
	static const std::string INPUTFILE;
	static const std::string OUTPUTFILE;
	static const std::string ENCODING;
	static const std::string DECODING;
	static const std::string XKEY;
	static const std::string VKEY;
	static const std::string CKEY;
	static const std::string GROUPING;
	static const std::string PACKING;
};

#endif /* CMDLINE_PARSER_H_ */
