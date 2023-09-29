#!/bin/sh

PERL="$1"
top_srcdir="$2"
top_builddir="$3"

# Environment for the pdbgen.pl file.
destdir=`cd "$top_srcdir" && pwd`
export destdir
builddir=`cd "$top_builddir" && pwd`
export BUILD builddir

cd "$top_srcdir"/pdb
$PERL pdbgen.pl app lib
RET=$?
if [ $RET -eq 0 ]; then
  echo "/* Generated on `date`. */" > $top_builddir/pdb/stamp-pdbgen.h
fi
exit $RET
