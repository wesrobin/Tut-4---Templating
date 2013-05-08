/*
 * cmdline_parser.h
 *
 *  Created on: 22 Feb 2012
 *      Author: simon
 *      Extended by: Wesley Robinson - RBNWES001
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
	
	cmdline_parser(void);   // Constructor

	bool process_cmdline(int argc, char * argv[]);  //Parse command line options
        
        bool should_get_user_input (void);
	
	std::string get_input_filename(void) const;
	std::string get_output_filename(void) const;    //Get files

        int get_caesar_key(void);
	std::string get_vigenere_key(void);
	int32_t get_XOR_key(void);  //Get keys
	
	bool should_encode(void);
	bool should_decode(void);
	bool should_group(void);
	bool should_pack(void); //Get options
	
	bool using_XOR(void);
	bool using_vigenere(void);
	bool using_caesar(void);        //Get cipher

	void print_errors(std::ostream & out) const;

	bool should_print_help(void) const;
	void print_help(std::ostream & out) const;      // Output help

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
        static const std::string USERINPUT;
	static const std::string ENCODE;
	static const std::string DECODE;
	static const std::string CKEY;
        static const std::string VKEY;
        static const std::string XKEY;
	static const std::string GROUP;
	static const std::string PACK;
};

#endif /* CMDLINE_PARSER_H_ */
