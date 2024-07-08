#!/bin/sh
# This file is part of ClanBomber <http://www.nongnu.org/clanbomber>.
# Copyright (C) 2008-2011, 2017 Rene Lopez <rsl@member.fsf.org>
#
# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.  This file is offered as-is,
# without any warranty.

ARCH=$1/.hg_archival.txt
OUT=$2/$3

if test -e $ARCH; then
    CHANGESET=$(sed -n -e "s/^node: \(.*\)$/\1/p" $ARCH | tr -d "\n")
    BRANCH=$(sed -n -e "s/^branch: \(.*\)$/\1/p" $ARCH | tr -d "\n")
else
    CHANGESET=$(hg id -R "$1" --debug -i | tr -d "\n")
    BRANCH=$(hg id -R "$1" -b | tr -d "\n")
fi
if test -e $OUT; then
    OLD_CHANGESET=$(sed -n -e "s/^#define HG_CHANGESET \"\(.*\)\"$/\1/p" "$OUT" | tr -d "\n")
    OLD_BRANCH=$(sed -n -e "s/^#define HG_BRANCH \"\(.*\)\"$/\1/p" "$OUT" | tr -d "\n")
    if test x$CHANGESET = x$OLD_CHANGESET -a "x$BRANCH" = "x$OLD_BRANCH" ; then
        exit
    fi
fi
echo \#define HG_CHANGESET \"$CHANGESET\" > "$OUT"
echo \#define HG_BRANCH \"$BRANCH\" >> "$OUT"
