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

/**
 * Trait that will be used when a combination is used that has not been implemented
 * in this program.
 */
template <typename Cipher, typename Grouping, typename Packing> class Crypt_Traits {
public:
    char key;
    typedef Cipher cipher;
    typedef Packing packing;
    typedef Grouping grouping;
    static std::string type(void) {
        return "Not implemented";
    }
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
 * caesar, no grouping, no packing
 */
template <> class Crypt_Traits <caesar, no_packing, grouping> {
public:
    int key;

    static std::string type(void) {
        return "Caesar, grouping, no packing";
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
 * vigenere, no grouping, no packing
 */
template <> class Crypt_Traits <vigenere, no_packing, grouping> {
public:
    std::string key;

    static std::string type(void) {
        return "Vigenere, grouping, no packing";
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

/**
 * Full specialization of Crypt_Traits
 * XOR, no grouping, no packing
 */
template <> class Crypt_Traits <XOR, no_packing, grouping> {
public:
    int32_t key;

    static std::string type(void) {
        return "XOR, grouping, no packing";
    }
};


#endif	/* CRYPT_TRAITS_H */