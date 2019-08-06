// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The ton Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ton_SCRIPT_tonCONSENSUS_H
#define ton_SCRIPT_tonCONSENSUS_H

#include <stdint.h>

#if defined(BUILD_ton_INTERNAL) && defined(HAVE_CONFIG_H)
#include <config/ton-config.h>
  #if defined(_WIN32)
    #if defined(DLL_EXPORT)
      #if defined(HAVE_FUNC_ATTRIBUTE_DLLEXPORT)
        #define EXPORT_SYMBOL __declspec(dllexport)
      #else
        #define EXPORT_SYMBOL
      #endif
    #endif
  #elif defined(HAVE_FUNC_ATTRIBUTE_VISIBILITY)
    #define EXPORT_SYMBOL __attribute__ ((visibility ("default")))
  #endif
#elif defined(MSC_VER) && !defined(STATIC_LIBtonCONSENSUS)
  #define EXPORT_SYMBOL __declspec(dllimport)
#endif

#ifndef EXPORT_SYMBOL
  #define EXPORT_SYMBOL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define tonCONSENSUS_API_VER 1

typedef enum tonconsensus_error_t
{
    tonconsensus_ERR_OK = 0,
    tonconsensus_ERR_TX_INDEX,
    tonconsensus_ERR_TX_SIZE_MISMATCH,
    tonconsensus_ERR_TX_DESERIALIZE,
    tonconsensus_ERR_AMOUNT_REQUIRED,
    tonconsensus_ERR_INVALID_FLAGS,
} tonconsensus_error;

/** Script verification flags */
enum
{
    tonconsensus_SCRIPT_FLAGS_VERIFY_NONE                = 0,
    tonconsensus_SCRIPT_FLAGS_VERIFY_P2SH                = (1U << 0), // evaluate P2SH (BIP16) subscripts
    tonconsensus_SCRIPT_FLAGS_VERIFY_DERSIG              = (1U << 2), // enforce strict DER (BIP66) compliance
    tonconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY           = (1U << 4), // enforce NULLDUMMY (BIP147)
    tonconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY = (1U << 9), // enable CHECKLOCKTIMEVERIFY (BIP65)
    tonconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY = (1U << 10), // enable CHECKSEQUENCEVERIFY (BIP112)
    tonconsensus_SCRIPT_FLAGS_VERIFY_WITNESS             = (1U << 11), // enable WITNESS (BIP141)
    tonconsensus_SCRIPT_FLAGS_VERIFY_ALL                 = tonconsensus_SCRIPT_FLAGS_VERIFY_P2SH | tonconsensus_SCRIPT_FLAGS_VERIFY_DERSIG |
                                                               tonconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY | tonconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY |
                                                               tonconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY | tonconsensus_SCRIPT_FLAGS_VERIFY_WITNESS
};

/// Returns 1 if the input nIn of the serialized transaction pointed to by
/// txTo correctly spends the scriptPubKey pointed to by scriptPubKey under
/// the additional constraints specified by flags.
/// If not nullptr, err will contain an error/success code for the operation
EXPORT_SYMBOL int tonconsensus_verify_script(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen,
                                                 const unsigned char *txTo        , unsigned int txToLen,
                                                 unsigned int nIn, unsigned int flags, tonconsensus_error* err);

EXPORT_SYMBOL int tonconsensus_verify_script_with_amount(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen, int64_t amount,
                                    const unsigned char *txTo        , unsigned int txToLen,
                                    unsigned int nIn, unsigned int flags, tonconsensus_error* err);

EXPORT_SYMBOL unsigned int tonconsensus_version();

#ifdef __cplusplus
} // extern "C"
#endif

#undef EXPORT_SYMBOL

#endif // ton_SCRIPT_tonCONSENSUS_H
