# Copyright (c) 2013-2016 The ton Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

DIST_SUBDIRS = secp256k1 univalue

AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS) $(GPROF_LDFLAGS) $(SANITIZER_LDFLAGS)
AM_CXXFLAGS = $(DEBUG_CXXFLAGS) $(HARDENED_CXXFLAGS) $(WARN_CXXFLAGS) $(NOWARN_CXXFLAGS) $(ERROR_CXXFLAGS) $(GPROF_CXXFLAGS) $(SANITIZER_CXXFLAGS)
AM_CPPFLAGS = $(DEBUG_CPPFLAGS) $(HARDENED_CPPFLAGS)
AM_LIBTOOLFLAGS = --preserve-dup-deps
EXTRA_LIBRARIES =

if EMBEDDED_UNIVALUE
LIBUNIVALUE = univalue/libunivalue.la

$(LIBUNIVALUE): $(wildcard univalue/lib/*) $(wildcard univalue/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)
else
LIBUNIVALUE = $(UNIVALUE_LIBS)
endif

ton_INCLUDES=-I$(builddir) $(BDB_CPPFLAGS) $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

ton_INCLUDES += -I$(srcdir)/secp256k1/include
ton_INCLUDES += $(UNIVALUE_CFLAGS)

LIBton_SERVER=libton_server.a
LIBton_COMMON=libton_common.a
LIBton_CONSENSUS=libton_consensus.a
LIBton_CLI=libton_cli.a
LIBton_UTIL=libton_util.a
LIBton_CRYPTO_BASE=crypto/libton_crypto_base.a
LIBtonQT=qt/libtonqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la

if ENABLE_ZMQ
LIBton_ZMQ=libton_zmq.a
endif
if BUILD_ton_LIBS
LIBtonCONSENSUS=libtonconsensus.la
endif
if ENABLE_WALLET
LIBton_WALLET=libton_wallet.a
LIBton_WALLET_TOOL=libton_wallet_tool.a
endif

LIBton_CRYPTO= $(LIBton_CRYPTO_BASE)
if ENABLE_SSE41
LIBton_CRYPTO_SSE41 = crypto/libton_crypto_sse41.a
LIBton_CRYPTO += $(LIBton_CRYPTO_SSE41)
endif
if ENABLE_AVX2
LIBton_CRYPTO_AVX2 = crypto/libton_crypto_avx2.a
LIBton_CRYPTO += $(LIBton_CRYPTO_AVX2)
endif
if ENABLE_SHANI
LIBton_CRYPTO_SHANI = crypto/libton_crypto_shani.a
LIBton_CRYPTO += $(LIBton_CRYPTO_SHANI)
endif

$(LIBSECP256K1): $(wildcard secp256k1/src/*.h) $(wildcard secp256k1/src/*.c) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES += \
  $(LIBton_CRYPTO) \
  $(LIBton_UTIL) \
  $(LIBton_COMMON) \
  $(LIBton_CONSENSUS) \
  $(LIBton_SERVER) \
  $(LIBton_CLI) \
  $(LIBton_WALLET) \
  $(LIBton_WALLET_TOOL) \
  $(LIBton_ZMQ)

lib_LTLIBRARIES = $(LIBtonCONSENSUS)

bin_PROGRAMS =
noinst_PROGRAMS =
TESTS =
BENCHMARKS =

if BUILD_tonD
  bin_PROGRAMS += tond
endif

if BUILD_ton_CLI
  bin_PROGRAMS += ton-cli
endif
if BUILD_ton_TX
  bin_PROGRAMS += ton-tx
endif
if ENABLE_WALLET
if BUILD_ton_WALLET
  bin_PROGRAMS += ton-wallet
endif
endif

.PHONY: FORCE check-symbols check-security
# ton core #
ton_CORE_H = \
  addrdb.h \
  addrman.h \
  attributes.h \
  banman.h \
  base58.h \
  bech32.h \
  bloom.h \
  blockencodings.h \
  blockfilter.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkqueue.h \
  clientversion.h \
  coins.h \
  compat.h \
  compat/assumptions.h \
  compat/byteswap.h \
  compat/endian.h \
  compat/sanity.h \
  compressor.h \
  consensus/consensus.h \
  consensus/tx_check.h \
  consensus/tx_verify.h \
  core_io.h \
  core_memusage.h \
  cuckoocache.h \
  flatfile.h \
  fs.h \
  httprpc.h \
  httpserver.h \
  index/base.h \
  index/blockfilterindex.h \
  index/txindex.h \
  indirectmap.h \
  init.h \
  interfaces/chain.h \
  interfaces/handler.h \
  interfaces/node.h \
  interfaces/wallet.h \
  key.h \
  key_io.h \
  dbwrapper.h \
  limitedmap.h \
  logging.h \
  memusage.h \
  merkleblock.h \
  miner.h \
  net.h \
  net_processing.h \
  netaddress.h \
  netbase.h \
  netmessagemaker.h \
  node/coin.h \
  node/psbt.h \
  node/transaction.h \
  noui.h \
  optional.h \
  outputtype.h \
  policy/feerate.h \
  policy/fees.h \
  policy/policy.h \
  policy/rbf.h \
  policy/settings.h \
  pow.h \
  protocol.h \
  psbt.h \
  random.h \
  reverse_iterator.h \
  reverselock.h \
  rpc/blockchain.h \
  rpc/client.h \
  rpc/protocol.h \
  rpc/rawtransaction_util.h \
  rpc/register.h \
  rpc/request.h \
  rpc/server.h \
  rpc/util.h \
  scheduler.h \
  script/descriptor.h \
  script/keyorigin.h \
  script/sigcache.h \
  script/sign.h \
  script/signingprovider.h \
  script/standard.h \
  shutdown.h \
  streams.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/events.h \
  support/lockedpool.h \
  sync.h \
  threadsafety.h \
  threadinterrupt.h \
  timedata.h \
  torcontrol.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  undo.h \
  util/bip32.h \
  util/bytevectorhash.h \
  util/error.h \
  util/fees.h \
  util/system.h \
  util/memory.h \
  util/moneystr.h \
  util/rbf.h \
  util/threadnames.h \
  util/time.h \
  util/translation.h \
  util/url.h \
  util/validation.h \
  validation.h \
  validationinterface.h \
  versionbits.h \
  versionbitsinfo.h \
  walletinitinterface.h \
  wallet/coincontrol.h \
  wallet/crypter.h \
  wallet/db.h \
  wallet/feebumper.h \
  wallet/fees.h \
  wallet/ismine.h \
  wallet/load.h \
  wallet/psbtwallet.h \
  wallet/rpcwallet.h \
  wallet/wallet.h \
  wallet/walletdb.h \
  wallet/wallettool.h \
  wallet/walletutil.h \
  wallet/coinselection.h \
  warnings.h \
  zmq/zmqabstractnotifier.h \
  zmq/zmqconfig.h\
  zmq/zmqnotificationinterface.h \
  zmq/zmqpublishnotifier.h \
  zmq/zmqrpc.h


obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh "$(abs_top_builddir)/src/obj/build.h" \
	  "$(abs_top_srcdir)"
libton_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between tond and ton-qt
# Contains code accessing mempool and chain state that is meant to be separated
# from wallet and gui code (see node/README.md). Shared code should go in
# libton_common or libton_util libraries, instead.
libton_server_a_CPPFLAGS = $(AM_CPPFLAGS) $(ton_INCLUDES) $(MINIUPNPC_CPPFLAGS) $(EVENT_CFLAGS) $(EVENT_PTHREADS_CFLAGS)
libton_server_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libton_server_a_SOURCES = \
  addrdb.cpp \
  addrman.cpp \
  banman.cpp \
  blockencodings.cpp \
  blockfilter.cpp \
  chain.cpp \
  consensus/tx_verify.cpp \
  flatfile.cpp \
  httprpc.cpp \
  httpserver.cpp \
  index/base.cpp \
  index/blockfilterindex.cpp \
  index/txindex.cpp \
  interfaces/chain.cpp \
  interfaces/node.cpp \
  init.cpp \
  dbwrapper.cpp \
  miner.cpp \
  net.cpp \
  net_processing.cpp \
  node/coin.cpp \
  node/psbt.cpp \
  node/transaction.cpp \
  noui.cpp \
  policy/fees.cpp \
  policy/rbf.cpp \
  policy/settings.cpp \
  pow.cpp \
  rest.cpp \
  rpc/blockchain.cpp \
  rpc/mining.cpp \
  rpc/misc.cpp \
  rpc/net.cpp \
  rpc/rawtransaction.cpp \
  rpc/server.cpp \
  script/sigcache.cpp \
  shutdown.cpp \
  timedata.cpp \
  torcontrol.cpp \
  txdb.cpp \
  txmempool.cpp \
  ui_interface.cpp \
  validation.cpp \
  validationinterface.cpp \
  versionbits.cpp \
  $(ton_CORE_H)

if ENABLE_WALLET
libton_server_a_SOURCES += wallet/init.cpp
endif
if !ENABLE_WALLET
libton_server_a_SOURCES += dummywallet.cpp
endif

if ENABLE_ZMQ
libton_zmq_a_CPPFLAGS = $(AM_CPPFLAGS) $(ton_INCLUDES) $(ZMQ_CFLAGS)
libton_zmq_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libton_zmq_a_SOURCES = \
  zmq/zmqabstractnotifier.cpp \
  zmq/zmqnotificationinterface.cpp \
  zmq/zmqpublishnotifier.cpp \
  zmq/zmqrpc.cpp
endif


# wallet: shared between tond and ton-qt, but only linked
# when wallet enabled
libton_wallet_a_CPPFLAGS = $(AM_CPPFLAGS) $(ton_INCLUDES)
libton_wallet_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libton_wallet_a_SOURCES = \
  interfaces/wallet.cpp \
  wallet/coincontrol.cpp \
  wallet/crypter.cpp \
  wallet/db.cpp \
  wallet/feebumper.cpp \
  wallet/fees.cpp \
  wallet/ismine.cpp \
  wallet/load.cpp \
  wallet/psbtwallet.cpp \
  wallet/rpcdump.cpp \
  wallet/rpcwallet.cpp \
  wallet/wallet.cpp \
  wallet/walletdb.cpp \
  wallet/walletutil.cpp \
  wallet/coinselection.cpp \
  $(ton_CORE_H)

libton_wallet_tool_a_CPPFLAGS = $(AM_CPPFLAGS) $(ton_INCLUDES)
libton_wallet_tool_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libton_wallet_tool_a_SOURCES = \
  wallet/wallettool.cpp \
  $(ton_CORE_H)

# crypto primitives library
crypto_libton_crypto_base_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libton_crypto_base_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libton_crypto_base_a_SOURCES = \
  crypto/aes.cpp \
  crypto/aes.h \
  crypto/chacha_poly_aead.h \
  crypto/chacha_poly_aead.cpp \
  crypto/chacha20.h \
  crypto/chacha20.cpp \
  crypto/common.h \
  crypto/hkdf_sha256_32.cpp \
  crypto/hkdf_sha256_32.h \
  crypto/hmac_sha256.cpp \
  crypto/hmac_sha256.h \
  crypto/hmac_sha512.cpp \
  crypto/hmac_sha512.h \
  crypto/poly1305.h \
  crypto/poly1305.cpp \
  crypto/ripemd160.cpp \
  crypto/ripemd160.h \
  crypto/sha1.cpp \
  crypto/sha1.h \
  crypto/sha256.cpp \
  crypto/sha256.h \
  crypto/sha512.cpp \
  crypto/sha512.h \
  crypto/siphash.cpp \
  crypto/siphash.h

if USE_ASM
crypto_libton_crypto_base_a_SOURCES += crypto/sha256_sse4.cpp
endif

crypto_libton_crypto_sse41_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libton_crypto_sse41_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libton_crypto_sse41_a_CXXFLAGS += $(SSE41_CXXFLAGS)
crypto_libton_crypto_sse41_a_CPPFLAGS += -DENABLE_SSE41
crypto_libton_crypto_sse41_a_SOURCES = crypto/sha256_sse41.cpp

crypto_libton_crypto_avx2_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libton_crypto_avx2_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libton_crypto_avx2_a_CXXFLAGS += $(AVX2_CXXFLAGS)
crypto_libton_crypto_avx2_a_CPPFLAGS += -DENABLE_AVX2
crypto_libton_crypto_avx2_a_SOURCES = crypto/sha256_avx2.cpp

crypto_libton_crypto_shani_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libton_crypto_shani_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libton_crypto_shani_a_CXXFLAGS += $(SHANI_CXXFLAGS)
crypto_libton_crypto_shani_a_CPPFLAGS += -DENABLE_SHANI
crypto_libton_crypto_shani_a_SOURCES = crypto/sha256_shani.cpp

# consensus: shared between all executables that validate any consensus rules.
libton_consensus_a_CPPFLAGS = $(AM_CPPFLAGS) $(ton_INCLUDES)
libton_consensus_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libton_consensus_a_SOURCES = \
  amount.h \
  arith_uint256.cpp \
  arith_uint256.h \
  consensus/merkle.cpp \
  consensus/merkle.h \
  consensus/params.h \
  consensus/tx_check.cpp \
  consensus/validation.h \
  hash.cpp \
  hash.h \
  prevector.h \
  primitives/block.cpp \
  primitives/block.h \
  primitives/transaction.cpp \
  primitives/transaction.h \
  pubkey.cpp \
  pubkey.h \
  script/tonconsensus.cpp \
  script/interpreter.cpp \
  script/interpreter.h \
  script/script.cpp \
  script/script.h \
  script/script_error.cpp \
  script/script_error.h \
  serialize.h \
  span.h \
  tinyformat.h \
  uint256.cpp \
  uint256.h \
  util/strencodings.cpp \
  util/strencodings.h \
  version.h

# common: shared between tond, and ton-qt and non-server tools
libton_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(ton_INCLUDES)
libton_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libton_common_a_SOURCES = \
  base58.cpp \
  bech32.cpp \
  bloom.cpp \
  chainparams.cpp \
  coins.cpp \
  compressor.cpp \
  core_read.cpp \
  core_write.cpp \
  key.cpp \
  key_io.cpp \
  merkleblock.cpp \
  netaddress.cpp \
  netbase.cpp \
  outputtype.cpp \
  policy/feerate.cpp \
  policy/policy.cpp \
  protocol.cpp \
  psbt.cpp \
  rpc/rawtransaction_util.cpp \
  rpc/util.cpp \
  scheduler.cpp \
  script/descriptor.cpp \
  script/sign.cpp \
  script/signingprovider.cpp \
  script/standard.cpp \
  versionbitsinfo.cpp \
  warnings.cpp \
  $(ton_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libton_util_a_CPPFLAGS = $(AM_CPPFLAGS) $(ton_INCLUDES)
libton_util_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libton_util_a_SOURCES = \
  support/lockedpool.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  compat/strnlen.cpp \
  fs.cpp \
  interfaces/handler.cpp \
  logging.cpp \
  random.cpp \
  rpc/request.cpp \
  support/cleanse.cpp \
  sync.cpp \
  threadinterrupt.cpp \
  util/bip32.cpp \
  util/bytevectorhash.cpp \
  util/error.cpp \
  util/fees.cpp \
  util/system.cpp \
  util/moneystr.cpp \
  util/rbf.cpp \
  util/threadnames.cpp \
  util/strencodings.cpp \
  util/time.cpp \
  util/url.cpp \
  util/validation.cpp \
  $(ton_CORE_H)

if GLIBC_BACK_COMPAT
libton_util_a_SOURCES += compat/glibc_compat.cpp
AM_LDFLAGS += $(COMPAT_LDFLAGS)
endif

# cli: shared between ton-cli and ton-qt
libton_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(ton_INCLUDES)
libton_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libton_cli_a_SOURCES = \
  rpc/client.cpp \
  $(ton_CORE_H)

nodist_libton_util_a_SOURCES = $(srcdir)/obj/build.h
#

# tond binary #
tond_SOURCES = tond.cpp
tond_CPPFLAGS = $(AM_CPPFLAGS) $(ton_INCLUDES)
tond_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
tond_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
tond_SOURCES += tond-res.rc
endif

# Libraries below may be listed more than once to resolve circular dependencies (see
# https://eli.thegreenplace.net/2013/07/09/library-order-in-static-linking#circular-dependency)
tond_LDADD = \
  $(LIBton_SERVER) \
  $(LIBton_WALLET) \
  $(LIBton_SERVER) \
  $(LIBton_COMMON) \
  $(LIBUNIVALUE) \
  $(LIBton_UTIL) \
  $(LIBton_ZMQ) \
  $(LIBton_CONSENSUS) \
  $(LIBton_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBLEVELDB_SSE42) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

tond_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS) $(ZMQ_LIBS)

# ton-cli binary #
ton_cli_SOURCES = ton-cli.cpp
ton_cli_CPPFLAGS = $(AM_CPPFLAGS) $(ton_INCLUDES) $(EVENT_CFLAGS)
ton_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
ton_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
ton_cli_SOURCES += ton-cli-res.rc
endif

ton_cli_LDADD = \
  $(LIBton_CLI) \
  $(LIBUNIVALUE) \
  $(LIBton_UTIL) \
  $(LIBton_CRYPTO)

ton_cli_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS) $(EVENT_LIBS)
#

# ton-tx binary #
ton_tx_SOURCES = ton-tx.cpp
ton_tx_CPPFLAGS = $(AM_CPPFLAGS) $(ton_INCLUDES)
ton_tx_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
ton_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
ton_tx_SOURCES += ton-tx-res.rc
endif

ton_tx_LDADD = \
  $(LIBUNIVALUE) \
  $(LIBton_COMMON) \
  $(LIBton_UTIL) \
  $(LIBton_CONSENSUS) \
  $(LIBton_CRYPTO) \
  $(LIBSECP256K1)

ton_tx_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS)
#

# ton-wallet binary #
ton_wallet_SOURCES = ton-wallet.cpp
ton_wallet_CPPFLAGS = $(AM_CPPFLAGS) $(ton_INCLUDES)
ton_wallet_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
ton_wallet_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
ton_wallet_SOURCES += ton-wallet-res.rc
endif

ton_wallet_LDADD = \
  $(LIBton_WALLET_TOOL) \
  $(LIBton_WALLET) \
  $(LIBton_COMMON) \
  $(LIBton_CONSENSUS) \
  $(LIBton_UTIL) \
  $(LIBton_CRYPTO) \
  $(LIBton_ZMQ) \
  $(LIBLEVELDB) \
  $(LIBLEVELDB_SSE42) \
  $(LIBMEMENV) \
  $(LIBSECP256K1) \
  $(LIBUNIVALUE)

ton_wallet_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(CRYPTO_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS) $(MINIUPNPC_LIBS) $(ZMQ_LIBS)
#

# tonconsensus library #
if BUILD_ton_LIBS
include_HEADERS = script/tonconsensus.h
libtonconsensus_la_SOURCES = support/cleanse.cpp $(crypto_libton_crypto_base_a_SOURCES) $(libton_consensus_a_SOURCES)

if GLIBC_BACK_COMPAT
  libtonconsensus_la_SOURCES += compat/glibc_compat.cpp
endif

libtonconsensus_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined $(RELDFLAGS)
libtonconsensus_la_LIBADD = $(LIBSECP256K1)
libtonconsensus_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(builddir)/obj -I$(srcdir)/secp256k1/include -DBUILD_ton_INTERNAL
libtonconsensus_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)

endif
#

CTAES_DIST =  crypto/ctaes/bench.c
CTAES_DIST += crypto/ctaes/ctaes.c
CTAES_DIST += crypto/ctaes/ctaes.h
CTAES_DIST += crypto/ctaes/README.md
CTAES_DIST += crypto/ctaes/test.c

CLEANFILES = $(EXTRA_LIBRARIES)

CLEANFILES += *.gcda *.gcno
CLEANFILES += compat/*.gcda compat/*.gcno
CLEANFILES += consensus/*.gcda consensus/*.gcno
CLEANFILES += crypto/*.gcda crypto/*.gcno
CLEANFILES += policy/*.gcda policy/*.gcno
CLEANFILES += primitives/*.gcda primitives/*.gcno
CLEANFILES += script/*.gcda script/*.gcno
CLEANFILES += support/*.gcda support/*.gcno
CLEANFILES += univalue/*.gcda univalue/*.gcno
CLEANFILES += wallet/*.gcda wallet/*.gcno
CLEANFILES += wallet/test/*.gcda wallet/test/*.gcno
CLEANFILES += zmq/*.gcda zmq/*.gcno
CLEANFILES += obj/build.h

EXTRA_DIST = $(CTAES_DIST)


config/ton-config.h: config/stamp-h1
	@$(MAKE) -C $(top_builddir) $(subdir)/$(@)
config/stamp-h1: $(top_srcdir)/$(subdir)/config/ton-config.h.in $(top_builddir)/config.status
	$(AM_V_at)$(MAKE) -C $(top_builddir) $(subdir)/$(@)
$(top_srcdir)/$(subdir)/config/ton-config.h.in:  $(am__configure_deps)
	$(AM_V_at)$(MAKE) -C $(top_srcdir) $(subdir)/config/ton-config.h.in

clean-local:
	-$(MAKE) -C secp256k1 clean
	-$(MAKE) -C univalue clean
	-rm -f leveldb/*/*.gcda leveldb/*/*.gcno leveldb/helpers/memenv/*.gcda leveldb/helpers/memenv/*.gcno
	-rm -f config.h
	-rm -rf test/__pycache__

.rc.o:
	@test -f $(WINDRES)
	## FIXME: How to get the appropriate modulename_CPPFLAGS in here?
	$(AM_V_GEN) $(WINDRES) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(CPPFLAGS) -DWINDRES_PREPROC -i $< -o $@

check-symbols: $(bin_PROGRAMS)
if GLIBC_BACK_COMPAT
	@echo "Checking glibc back compat..."
	$(AM_V_at) READELF=$(READELF) CPPFILT=$(CPPFILT) $(PYTHON) $(top_srcdir)/contrib/devtools/symbol-check.py < $(bin_PROGRAMS)
endif

check-security: $(bin_PROGRAMS)
if HARDEN
	@echo "Checking binary security..."
	$(AM_V_at) READELF=$(READELF) OBJDUMP=$(OBJDUMP) $(PYTHON) $(top_srcdir)/contrib/devtools/security-check.py < $(bin_PROGRAMS)
endif

if ENABLE_BIP70
%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(<D) $<
endif

if EMBEDDED_LEVELDB
include Makefile.leveldb.include
endif

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_BENCH
include Makefile.bench.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
