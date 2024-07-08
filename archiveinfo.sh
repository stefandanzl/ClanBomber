#!/bin/sh
# This file is part of ClanBomber <http://www.nongnu.org/clanbomber>.
# Copyright (C) 2008-2011, 2017 Rene Lopez <rsl@member.fsf.org>
#
# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.  This file is offered as-is,
# without any warranty.

command -v hg > /dev/null 2>&1 || {
    echo Missing hg command \(mercurial\)
    exit 1
}

SRCDIR=$(dirname "$0")

REPO=$(hg id -R "$SRCDIR" --debug -i -r 0 | tr -d "\n")
CHANGESET=$(hg id -R "$SRCDIR" --debug -i | tr -d "\n")
BRANCH=$(hg id -R "$SRCDIR" -b | tr -d "\n")
LATESTTAG=$(hg log -R "$SRCDIR" -r "." --template "{latesttag}")
LATESTTAGDISTANCE=$(hg log -R "$SRCDIR" -r "." --template "{latesttagdistance}")
CHANGESSINCELATESTTAG=$(hg log -R "$SRCDIR" -r "." --template "{changessincelatesttag}")

echo repo: $REPO
echo node: $CHANGESET
echo branch: $BRANCH
echo latesttag: $LATESTTAG
echo latesttagdistance: $LATESTTAGDISTANCE
echo changessincelatesttag: $CHANGESSINCELATESTTAG
