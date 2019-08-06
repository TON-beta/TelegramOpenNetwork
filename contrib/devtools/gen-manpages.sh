#!/usr/bin/env bash

export LC_ALL=C
TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
BUILDDIR=${BUILDDIR:-$TOPDIR}

BINDIR=${BINDIR:-$BUILDDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

tonD=${tonD:-$BINDIR/tond}
tonCLI=${tonCLI:-$BINDIR/ton-cli}
tonTX=${tonTX:-$BINDIR/ton-tx}
WALLET_TOOL=${WALLET_TOOL:-$BINDIR/ton-wallet}
tonQT=${tonQT:-$BINDIR/qt/ton-qt}

[ ! -x $tonD ] && echo "$tonD not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
read -r -a BTCVER <<< "$($tonCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }')"

# Create a footer file with copyright content.
# This gets autodetected fine for tond if --version-string is not set,
# but has different outcomes for ton-qt and ton-cli.
echo "[COPYRIGHT]" > footer.h2m
$tonD --version | sed -n '1!p' >> footer.h2m

for cmd in $tonD $tonCLI $tonTX $WALLET_TOOL $tonQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${BTCVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${BTCVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
