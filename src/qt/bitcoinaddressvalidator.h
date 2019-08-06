// Copyright (c) 2011-2014 The ton Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ton_QT_tonADDRESSVALIDATOR_H
#define ton_QT_tonADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class tonAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit tonAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** ton address widget validator, checks for a valid ton address.
 */
class tonAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit tonAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // ton_QT_tonADDRESSVALIDATOR_H
