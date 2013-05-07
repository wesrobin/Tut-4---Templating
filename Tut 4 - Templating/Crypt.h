/* 
 * File:   Crypt.h
 * Author: wesley
 *
 * Created on 07 May 2013, 1:48 PM
 */

#ifndef CRYPT_H
#define	CRYPT_H

#include "Crypt_Policies.h"
#include "Crypt_Traits.h"

template <typename Cipher, typename Grouping, typename Packing, typename Traits = Crypt_Traits<Cipher, Grouping, Packing>, typename Policies = Crypt_Policies<Ciper, Grouping, Packing>> class Crypt {
    typedef Policies P;
    typedef Traits T;
};

#endif	/* CRYPT_H */

