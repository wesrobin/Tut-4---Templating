/* 
 * File:   Crypt.h
 * Author: wesley
 *
 * Created on 07 May 2013, 1:48 PM
 */

#ifndef CRYPT_H
#define	CRYPT_H

#include <string>
#include <sstream>

#include "Crypt_Policies.h"
#include "Crypt_Traits.h"

template <typename Cipher, typename Grouping, typename Packing, typename Traits = Crypt_Traits<Cipher, Grouping, Packing>, typename Policies = Crypt_Policies<Cipher, Grouping, Packing> > class Crypt {
public:

    typedef Policies P;
    typedef Traits T;

    std::string encode(std::string str, decltype(T::key) key) {
        std::stringstream ss;
        ss << "Encoding with: " << T::type() << std::endl << P::encode(str, key);
        return ss.str();
    }

    std::string decode(std::string str, decltype(T::key) key) {
        std::stringstream ss;
        ss << "Decoding with: " << T::type() << std::endl << P::decode(str, key);
        return ss.str();
    }
};

#endif	/* CRYPT_H */

