/* 
 * File:   Crypt_Policies.h
 * Author: wesley
 *
 * Created on 07 May 2013, 1:40 PM
 */

#ifndef CRYPT_POLICIES_H
#define	CRYPT_POLICIES_H

#include <algorithm>

#include "Crypt_Traits.h"
#include "Type.h"

/**
 * Functor for caesar encrypt
 */
struct Caesar_Encrypt {
public:
    int key;

    Caesar_Encrypt(int k) : key(k) {
    }

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
    }

    char operator()(char& c) {
        if (c == ' ') {
            return c;
        }//Ignore spaces
        else {
            char temp = (c - 'A' - key);
            while (temp < 0) {
                temp += 26;
            }
            return temp % 26 + 'A';
        } //Decode char
    }
};

/**
 * Functor for XOR encrypt
 */
//struct Caesar_Decrypt {
//public:
//    int key;
//
//    XOR_Encrypt(int k) : key(k) {
//    }
//
//    char operator()(char& c) {
//        if (c == ' ') {
//            return c;
//        }//Ignore spaces
//        else {
//            
//        } //Encode char
//    }
//};

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
 * vigenere, no packing, no grouping
 */
template <> class Crypt_Policies <vigenere, no_packing, no_grouping> {
public:

    static std::string encode(std::string& str, std::string& key) {
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
 * caesar, no packing, no grouping
 */
template <> class Crypt_Policies <XOR, no_packing, no_grouping> {
public:

    static std::string encode(std::string& str, int32_t key) {
        int index = 0;
        std::transform(str.begin(), str.end(), str.begin(), [&index, &key] (char& c)-> char {
            int current_key = (key >> (8 * index)) & 255;
            ++index %= 4;
            return (c ^ current_key);
        });
        return str;
    }

    static std::string decode(std::string str, int32_t key) {
        int index = 0;
        std::transform(str.begin(), str.end(), str.begin(), [&index, &key] (char& c)-> char {
            int current_key = (key >> (8 * index)) & 255;           
            ++index %= 4;
            return (current_key ^ c);
        });
        return str;
    }
};

#endif	/* CRYPT_POLICIES_H */

