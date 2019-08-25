SUBDIRS = source
EXTRA_DIST = apidocs docs/*.txt vc.net/dwsrame/dwsrame.sln \
	vc.net/dwsrame/dwsrame.vcproj

.PHONY: allclean apidocs touch

allclean: clean
	-rm -rf apidocs
	-rm -f *.bz2 *.gz
	-find -iname "*~" -exec rm -f {} \;

apidocs: Doxyfile
	@doxygen

touch:
	-find -iname "*.cc" -exec touch {} \;
	-find -iname "*.hh" -exec touch {} \;
	-find -iname "*.xrc" -exec touch {} \;

