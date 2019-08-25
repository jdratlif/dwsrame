# $Id: Makefile.am,v 1.10 2008/12/17 03:51:04 jdratlif Exp $

SUBDIRS = source
EXTRA_DIST = apidocs docs/*.txt Doxyfile sav \
	vstudio/dwsrame/dwsrame.sln vstudio/dwsrame/dwsrame.vcproj
    
sav:
	-mkdir sav
	-cp source/res/Dragon\ Warrior\ \(U\)\ \(PRG1\).sav sav

.PHONY: allclean apidocs bundle touch

allclean: clean
	-rm -rf source/dwsrame.app
	-rm -rf apidocs
	-rm -f *.bz2
	-find -iname "*~" -exec rm -f {} \;

apidocs: Doxyfile
	@doxygen

bundle:
	-cd source && make dwsrame.app

touch:
	-find -iname "*.cc" -exec touch {} \;
	-find -iname "*.hh" -exec touch {} \;
	-find -iname "*.xrc" -exec touch {} \;

