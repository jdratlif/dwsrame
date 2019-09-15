SUBDIRS = source
EXTRA_DIST = apidocs docs/*.txt Doxyfile sav \
	vstudio/dwsrame.sln vstudio/dwsrame.vcxproj \
	vstudio/dwsrame.vcxproj.filters vstudio/dwsrame.vcxproj.user
    
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
	-find -iname "*.cpp" -exec touch {} \;
	-find -iname "*.hh" -exec touch {} \;
	-find -iname "*.xrc" -exec touch {} \;
