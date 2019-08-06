// Copyright (c) 2009-2019 The ton Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ton_TEST_FUZZ_FUZZ_H
#define ton_TEST_FUZZ_FUZZ_H

#include <stdint.h>
#include <vector>


void test_one_input(std::vector<uint8_t> buffer);

#endif // ton_TEST_FUZZ_FUZZ_H
