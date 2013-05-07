/* 
 * File:   Crypt_Policies.h
 * Author: wesley
 *
 * Created on 07 May 2013, 1:40 PM
 */

#ifndef CRYPT_POLICIES_H
#define	CRYPT_POLICIES_H

#include "Crypt_Traits.h"
#include "Type.h"

struct Caesar_Encrypt {
    public:
        int key;
        Caesar_Encrypt (int k) : key(k) {}
        
        char operator()(char& c) {
            int ascii = static_cast<int> (c);
        }
};

template <typename Cipher, typename Grouping, typename Packing> class Crypt_Policies {
    public:
        static std::string encode(std::string str) { return "Not implemented"; }
        static std::string decode(std::string str) { return "Not implemented"; }
};

/**
 * Full specialisation of Crypt_Policies for
 * caesar, no packing, no grouping
 */
template <> class Crypt_Policies <caesar, no_packing, no_grouping> {
    public:
        static std::string encode(std::string str) { return "Fuck you asshole"; }
        static std::string decode(std::string str) { return "Not implemented"; }
};

#endif	/* CRYPT_POLICIES_H */

