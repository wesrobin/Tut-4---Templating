/* 
 * File:   Crypt_Traits.h
 * Author: wesley
 *
 * Created on 07 May 2013, 1:23 PM
 */

#ifndef CRYPT_TRAITS_H
#define	CRYPT_TRAITS_H

#include "Type.h"

template <typename Cipher, typename Grouping, typename Packing> class Crypt_Traits {
    public:
        char key;
        typedef Cipher cipher;
        typedef Packing packing;
        typedef Grouping grouping;
};

template <> class Crypt_Traits <caesar, no_grouping, no_packing> {
    public:
        int key;
};

#endif	/* CRYPT_TRAITS_H */

