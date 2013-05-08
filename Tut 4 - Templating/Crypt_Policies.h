/* 
 * Wesley Robinson - RBNWES001
 * Crypt_Policies.h
 * Policies class which uses specialisations of all the different cipher/group/pack 
 * options and runs an appropriate method in each case.
 * Created on 07 May 2013, 1:40 PM
 */

#ifndef CRYPT_POLICIES_H
#define	CRYPT_POLICIES_H

#include <algorithm>

#include "Crypt_Traits.h"
#include "Type.h"

/**
 * Method to strip given string of all white space
 * @param str the string to be stripped
 * @return the string without the spaces
 */
std::string stripSpaces (std::string& str) {
    str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());      //Uses STL to find and delete all spaces. Works by moving all spaces to the end of the string, 
                                                                                //then calling the erase() function on the string to delete these spaces
    return str;
}

/**
 * Method to group a (whitespace free) string into 'words' of five letters each
 * @param str the string to be grouped
 * @return the grouped string
 */
std::string group (std::string& str) {
    str = stripSpaces(str);
    for (int i = 0 ; i < str.length() ; ++i) {
        if (i % 6 == 0) {
            str.insert(i, " "); //Also inserts at i = 0, will need to remove it!
        }
    }
    return str.substr(1);       //Removes the leading space
}

/**
 * Method to generate the rest of the key for the Vigenere cipher, given the prefix
 * @param str the string to generate the key for
 * @param keyPref the prefix of the key
 * @return string containing the whole key
 */
std::string generate_key (std::string& str, std::string& keyPref) {
    std::string temp = "";      //Temp variable to store the generated key
    std::string::iterator keyIt = keyPref.begin();      //Iterator starts at the beginning of the key
    for (char c : str) {        //Iterates through str, char at a time
        if (c == ' ') { temp += ' '; }  //If c is a space, there should be a corresponding space in the key
        else {
            if (keyIt == keyPref.end()) { keyIt = keyPref.begin(); }    //If the iterator has reached the end of the string, reset it to the beginning again
            temp += *keyIt;     //Add the current location of the iterator to the generated key
            ++keyIt;    //Increment the iterator
        }
    }
    return temp;
}

/**
 * Functor for caesar encrypt
 */
struct Caesar_Encrypt {
public:
    int key;

    Caesar_Encrypt(int k) : key(k) {
    }   //Constructor

    /**
     * Operator overload for (), causes struct to be a functor
     * @param c the character to be encoded
     * @return the encoded character
     */
    char operator()(char& c) {
        if (c == ' ') {
            return c;
        }//Ignore spaces
        else {
            return (c - 'A' + key) % 26 + 'A';
        } //Encode char
    }
};

/**
 * Functor for caesar decrypt
 */
struct Caesar_Decrypt {
public:
    int key;

    Caesar_Decrypt(int k) : key(k) {
    }   //Constructor
    
    /**
     * Operator overload for (), causes struct to be a functor
     * @param c the character to be encoded
     * @return the encoded character
     */
    char operator()(char& c) {
        if (c == ' ') {
            return c;
        }//Ignore spaces
        else {
            int temp = (c - 'A' - key);
            while (temp < 0) {
                temp += 26;
            }
            return (temp % 26) + 'A';
        } //Decode char
    }
};

/**
 * General non-specialised method, which is not used, and so is not implemented.
 * Will run when the user uses options that are not implemented as specialisations
 */
template <typename Cipher, typename Grouping, typename Packing> class Crypt_Policies {
public:

    static std::string encode(std::string str, int key) {
        return "Not implemented";
    }

    static std::string decode(std::string str, int key) {
        return "Not implemented";
    }
};

/**
 * Full specialisation of Crypt_Policies for
 * caesar, no packing, no grouping
 */
template <> class Crypt_Policies <caesar, no_packing, no_grouping> {
public:

    static std::string encode(std::string& str, int key) {
        std::transform(str.begin(), str.end(), str.begin(), Caesar_Encrypt(key));
        return str;
    }

    static std::string decode(std::string str, int key) {
        std::transform(str.begin(), str.end(), str.begin(), Caesar_Decrypt(key));
        return str;
    }
};

/**
 * Full specialisation of Crypt_Policies for
 * caesar, no packing, grouping
 */
template <> class Crypt_Policies <caesar, no_packing, grouping> {
public:
    static std::string encode(std::string& str, int key) {
        std::transform(str.begin(), str.end(), str.begin(), Caesar_Encrypt(key));       //First encodes the string
        str = group(str);       //Groups encoded string
        return str;
    }

    static std::string decode(std::string str, int key) {
        std::transform(str.begin(), str.end(), str.begin(), Caesar_Decrypt(key));
        str = group(str);
        return str;
    }
};

/**
 * Full specialisation of Crypt_Policies for
 * caesar, packing, grouping
 */
template <> class Crypt_Policies <caesar, packing, grouping> {
public:
    static std::string encode(std::string str, int key) {
        return "Not implemented";
    }

    static std::string decode(std::string str, int key) {
        return "Not implemented";
    }
};

/**
 * Full specialisation of Crypt_Policies for
 * caesar, packing, no grouping
 */
template <> class Crypt_Policies <caesar, packing, no_grouping> {
public:
    static std::string encode(std::string str, int key) {
        return "Not implemented";
    }

    static std::string decode(std::string str, int key) {
        return "Not implemented";
    }
};

/**
 * Full specialisation of Crypt_Policies for
 * vigenere, no packing, no grouping
 */
template <> class Crypt_Policies <vigenere, no_packing, no_grouping> {
public:
    static std::string encode(std::string& str, std::string& key) {
        key = generate_key(str, key);
        std::transform(str.begin(), str.end(), key.begin(), str.begin(), [](char& c1, const char& c2)->char {
            if (c1 == ' ') {
                return c1;
            }//Ignore spaces
            else {
                return ((c1 - 'A') + (c2 - 'A')) % 26 + 'A';
            }
        }); //Encoded using a lambda
        return str;
    }

    static std::string decode(std::string str, std::string& key) {
        key = generate_key(str, key);
        std::transform(str.begin(), str.end(), key.begin(), str.begin(), [](char& c1, const char& c2)->char {
            if (c1 == ' ') {
                return c1;
            }//Ignore spaces
            else {
                char temp = (c1 - 'A') - (c2 - 'A');
                while (temp < 0) {
                    temp += 26;
                }
                return temp % 26 + 'A';
            }
        }); //Encoded using a lambda
        return str;
    }
};

/**
 * Full specialisation of Crypt_Policies for
 * vigenere, no packing, grouping
 */
template <> class Crypt_Policies <vigenere, no_packing, grouping> {
public:
    static std::string encode(std::string& str, std::string& key) {
        key = generate_key(str, key);
        std::transform(str.begin(), str.end(), key.begin(), str.begin(), [](char& c1, const char& c2)->char {
            if (c1 == ' ') {
                return c1;
            }//Ignore spaces
            else {
                return ((c1 - 'A') + (c2 - 'A')) % 26 + 'A';
            }
        }); //Encoded using a lambda
        str = group (str);
        return str;
    }

    static std::string decode(std::string str, std::string& key) {
        key = generate_key(str, key);
        std::transform(str.begin(), str.end(), key.begin(), str.begin(), [](char& c1, const char& c2)->char {
            if (c1 == ' ') {
                return c1;
            }//Ignore spaces
            else {
                char temp = (c1 - 'A') - (c2 - 'A');
                while (temp < 0) {
                    temp += 26;
                }
                return temp % 26 + 'A';
            }
        }); //Encoded using a lambda
        str = group(str);
        return str;
    }
};

/**
 * Full specialisation of Crypt_Policies for
 * vigenere, packing, grouping
 */
template <> class Crypt_Policies <vigenere, packing, grouping> {
public:
    static std::string encode(std::string str, std::string key) {
        return "Not implemented";
    }

    static std::string decode(std::string str, std::string key) {
        return "Not implemented";
    }
};

/**
 * Full specialisation of Crypt_Policies for
 * vigenere, packing, no grouping
 */
template <> class Crypt_Policies <vigenere, packing, no_grouping> {
public:
    static std::string encode(std::string str, std::string key) {
        return "Not implemented";
    }

    static std::string decode(std::string str, std::string key) {
        return "Not implemented";
    }
};

/**
 * Full specialisation of Crypt_Policies for
 * caesar, no packing, no grouping
 */
template <> class Crypt_Policies <XOR, no_packing, no_grouping> {
public:
    static std::string encode(std::string& str, int32_t key) {  //This works by using each 32bit int as a key for 4 separate chars (each 8bits long)
        int index = 0;  //Index that will be maintained in the lambda below
        std::transform(str.begin(), str.end(), str.begin(), [&index, &key] (char& c)-> char {   //Uses STL transform to apply XOR on the string to be encrypted
            int current_key = (key >> (8 * index)) & 255;       //Selects the correct 8 bits to encode the current char with
            ++index %= 4;       //Maintains the index value, ensuring that subsequent chars will use the next 8 bits of the 32bit int
            return (c ^ current_key);   //Returns the XOR of the key and the char
        });
        return str;
    }

    static std::string decode(std::string str, int32_t key) {   //Same method as above
//        int index = 0;
//        std::transform(str.begin(), str.end(), str.begin(), [&index, &key] (char& c)-> char {
//            int current_key = (key >> (8 * index)) & 255;           
//            ++index %= 4;
//            return (current_key ^ c);
//        });
//        return str;
        return encode(str, key);        //Need only do this because of the nature of XORing!
    }
};

/**
 * Full specialisation of Crypt_Policies for
 * caesar, no packing, grouping
 */
template <> class Crypt_Policies <XOR, no_packing, grouping> {
public:
    static std::string encode(std::string& str, int32_t key) {
        int index = 0;
        str = group(str);
        std::transform(str.begin(), str.end(), str.begin(), [&index, &key] (char& c)-> char {
            int current_key = (key >> (8 * index)) & 255;
            ++index %= 4;
            return (c ^ current_key);
        });
        return str;
    }

    static std::string decode(std::string str, int32_t key) {
        int index = 0;
//        str = group(str);     //Group has been removed, since there is no way to degroup XOR encrypted stuff.
        std::transform(str.begin(), str.end(), str.begin(), [&index, &key] (char& c)-> char {
            int current_key = (key >> (8 * index)) & 255;           
            ++index %= 4;
            return (current_key ^ c);
        });
        return str;
    }
};

/**
 * Full specialisation of Crypt_Policies for
 * XOR, packing, grouping
 */
template <> class Crypt_Policies <XOR, packing, grouping> {
public:
    static std::string encode(std::string str, int32_t key) {
        return "Not implemented";
    }

    static std::string decode(std::string str, int32_t key) {
        return "Not implemented";
    }
};

/**
 * Full specialisation of Crypt_Policies for
 * XOR, packing, no grouping
 */
template <> class Crypt_Policies <XOR, packing, no_grouping> {
public:
    static std::string encode(std::string str, int32_t key) {
        return "Not implemented";
    }

    static std::string decode(std::string str, int32_t key) {
        return "Not implemented";
    }
};

#endif	/* CRYPT_POLICIES_H */

