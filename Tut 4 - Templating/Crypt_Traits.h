/* 
 * File:   Crypt_Traits.h
 * Author: wesley
 *
 * Created on 07 May 2013, 1:23 PM
 */

#ifndef CRYPT_TRAITS_H
#define	CRYPT_TRAITS_H

#include "Type.h"
#include <cstdint>

template <typename Cipher, typename Grouping, typename Packing> class Crypt_Traits {
public:
    char key;
    typedef Cipher cipher;
    typedef Packing packing;
    typedef Grouping grouping;
};

/**
 * Full specialization of Crypt_Traits
 * caesar, no grouping, no packing
 */
template <> class Crypt_Traits <caesar, no_packing, no_grouping> {
public:
    int key;

    static std::string type(void) {
        return "Caesar, no grouping, no packing";
    }
};

/**
 * Full specialization of Crypt_Traits
 * vigenere, no grouping, no packing
 */
template <> class Crypt_Traits <vigenere, no_packing, no_grouping> {
public:
    std::string key;

    static std::string type(void) {
        return "Vigenere, no grouping, no packing";
    }
};

/**
 * Full specialization of Crypt_Traits
 * XOR, no grouping, no packing
 */
template <> class Crypt_Traits <XOR, no_packing, no_grouping> {
public:
    int32_t key;

    static std::string type(void) {
        return "XOR, no grouping, no packing";
    }
};


#endif	/* CRYPT_TRAITS_H */