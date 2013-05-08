/* 
 * Wesley Robinson - RBNWES001
 * Crypt_Traits.h
 * Traits class which uses specialisations of all the different cipher/group/pack 
 * options and stores (and returns) appropriate data for each specialisation.
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
 * caesar, grouping, packing
 */
template <> class Crypt_Traits <caesar, packing, grouping> {
public:
    int key;

    static std::string type(void) {
        return "Caesar, grouping, packing";
    }
};

/**
 * Full specialization of Crypt_Traits
 * caesar, no grouping, packing
 */
template <> class Crypt_Traits <caesar, packing, no_grouping> {
public:
    int key;

    static std::string type(void) {
        return "Caesar, no grouping, packing";
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
 * vigenere, grouping, packing
 */
template <> class Crypt_Traits <vigenere, packing, grouping> {
public:
    std::string key;

    static std::string type(void) {
        return "Vigenere, grouping, packing";
    }
};

/**
 * Full specialization of Crypt_Traits
 * vigenere, no grouping, packing
 */
template <> class Crypt_Traits <vigenere, packing, no_grouping> {
public:
    std::string key;

    static std::string type(void) {
        return "Vigenere, no grouping, packing";
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
 * XOR, grouping, no packing
 */
template <> class Crypt_Traits <XOR, no_packing, grouping> {
public:
    int32_t key;

    static std::string type(void) {
        return "XOR, grouping, no packing";
    }
};

/**
 * Full specialization of Crypt_Traits
 * XOR, grouping, packing
 */
template <> class Crypt_Traits <XOR, packing, grouping> {
public:
    int32_t key;

    static std::string type(void) {
        return "XOR, grouping, packing";
    }
};

/**
 * Full specialization of Crypt_Traits
 * XOR, no grouping, packing
 */
template <> class Crypt_Traits <XOR, packing, no_grouping> {
public:
    int32_t key;

    static std::string type(void) {
        return "XOR, no grouping, packing";
    }
};


#endif	/* CRYPT_TRAITS_H */