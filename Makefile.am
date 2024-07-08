SUBDIRS = src po

EXTRA_DIST =  \
	DEPENDENCIES \
	EXTERNAL \
	IDEAS \
	LICENSE.DEJAVU \
	QUOTES \
	archiveinfo.sh \
	buildinfo.sh

ACLOCAL_AMFLAGS = -I m4

dist-hook: ChangeLog.hg .hg_archival.txt

ChangeLog.hg:
	hg log -R $(srcdir) -f --style changelog > $(distdir)/$@

.hg_archival.txt:
	$(srcdir)/archiveinfo.sh > $(distdir)/$@

buildinfo.h:
	$(srcdir)/buildinfo.sh $(srcdir) $(builddir) $@

.PHONY: buildinfo.h

BUILT_SOURCES = buildinfo.h
