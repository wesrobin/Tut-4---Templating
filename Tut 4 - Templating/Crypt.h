/* 
 * Wesley Robinson - RBNWES001
 * Crypt.h
 * Crypt class that uses the traits and policies classes to run a relevant encode or
 * decode method on the text with the supplied key.
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

        /**
         * Encode method which uses the specified key and cipher (with options) to
         * encrypt some given string
         * @param str the string to be encrypted
         * @param key the key to use in encryption
         * @return the encrypted string
         */
        std::string encode (std::string str, decltype(T::key) key) {    //Uses the type for the key stored by the relevant specialisation in the Traits class
            std::stringstream ss;
            std::cout << "Encoding with: " << T::type() << std::endl;
            ss << P::encode(str, key);
            return ss.str();
        }

        /**
         * Decode method which uses the specified key and cipher (with options) to
         * decrypt some given string
         * @param str the string to be decrypted
         * @param key the key to use in decryption
         * @return the decrypted string
         */
        std::string decode (std::string str, decltype(T::key) key) {
            std::stringstream ss;
            std::cout << "Decoding with: " << T::type() << std::endl;
            ss << P::decode(str, key);
            return ss.str();
        }
};

#endif	/* CRYPT_H */

