Shared Libraries
================

## tonconsensus

The purpose of this library is to make the verification functionality that is critical to ton's consensus available to other applications, e.g. to language bindings.

### API

The interface is defined in the C header `tonconsensus.h` located in `src/script/tonconsensus.h`.

#### Version

`tonconsensus_version` returns an `unsigned int` with the API version *(currently `1`)*.

#### Script Validation

`tonconsensus_verify_script` returns an `int` with the status of the verification. It will be `1` if the input script correctly spends the previous output `scriptPubKey`.

##### Parameters
- `const unsigned char *scriptPubKey` - The previous output script that encumbers spending.
- `unsigned int scriptPubKeyLen` - The number of bytes for the `scriptPubKey`.
- `const unsigned char *txTo` - The transaction with the input that is spending the previous output.
- `unsigned int txToLen` - The number of bytes for the `txTo`.
- `unsigned int nIn` - The index of the input in `txTo` that spends the `scriptPubKey`.
- `unsigned int flags` - The script validation flags *(see below)*.
- `tonconsensus_error* err` - Will have the error/success code for the operation *(see below)*.

##### Script Flags
- `tonconsensus_SCRIPT_FLAGS_VERIFY_NONE`
- `tonconsensus_SCRIPT_FLAGS_VERIFY_P2SH` - Evaluate P2SH ([BIP16](https://github.com/ton/bips/blob/master/bip-0016.mediawiki)) subscripts
- `tonconsensus_SCRIPT_FLAGS_VERIFY_DERSIG` - Enforce strict DER ([BIP66](https://github.com/ton/bips/blob/master/bip-0066.mediawiki)) compliance
- `tonconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY` - Enforce NULLDUMMY ([BIP147](https://github.com/ton/bips/blob/master/bip-0147.mediawiki))
- `tonconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY` - Enable CHECKLOCKTIMEVERIFY ([BIP65](https://github.com/ton/bips/blob/master/bip-0065.mediawiki))
- `tonconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY` - Enable CHECKSEQUENCEVERIFY ([BIP112](https://github.com/ton/bips/blob/master/bip-0112.mediawiki))
- `tonconsensus_SCRIPT_FLAGS_VERIFY_WITNESS` - Enable WITNESS ([BIP141](https://github.com/ton/bips/blob/master/bip-0141.mediawiki))

##### Errors
- `tonconsensus_ERR_OK` - No errors with input parameters *(see the return value of `tonconsensus_verify_script` for the verification status)*
- `tonconsensus_ERR_TX_INDEX` - An invalid index for `txTo`
- `tonconsensus_ERR_TX_SIZE_MISMATCH` - `txToLen` did not match with the size of `txTo`
- `tonconsensus_ERR_DESERIALIZE` - An error deserializing `txTo`
- `tonconsensus_ERR_AMOUNT_REQUIRED` - Input amount is required if WITNESS is used

### Example Implementations
- [Nton](https://github.com/NicolasDorier/Nton/blob/master/Nton/Script.cs#L814) (.NET Bindings)
- [node-libtonconsensus](https://github.com/bitpay/node-libtonconsensus) (Node.js Bindings)
- [java-libtonconsensus](https://github.com/dexX7/java-libtonconsensus) (Java Bindings)
- [tonconsensus-php](https://github.com/Bit-Wasp/tonconsensus-php) (PHP Bindings)
