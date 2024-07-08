entrydir = $(datadir)/applications/

entry_DATA = \
	clanbomber.desktop

EXTRA_DIST = \
	clanbomber.desktop.in

clanbomber.desktop: clanbomber.desktop.in
	$(SED) \
		-e 's|[@]PACKAGE_NAME[@]|$(PACKAGE_NAME)|g' \
		-e 's|[@]bindir[@]|$(bindir)|g' \
		-e 's|[@]PACKAGE[@]|$(PACKAGE)|g' \
		< "$<" > "$@"
