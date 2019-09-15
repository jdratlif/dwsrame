AUTOMAKE_OPTIONS = subdir-objects
CLEANFILES = res/dwsrame.cc
EXTRA_DIST = res/dwsrame.icns res/dwsrame.xrc \
	res/icon32x32.ico res/icon32x32.xpm res/Info.plist res/windows.rc

bin_PROGRAMS = dwsrame

dwsrame_SOURCES = dwsrame.cc dwsrame.hh \
	exception/invalidsramfileexception.cc \
	exception/invalidsramfileexception.hh \
	model/sramfile.cc model/sramfile.hh \
	res/resource.cpp \
	view/mainframe.cc view/mainframe.hh \
	view/sramfiletarget.cc view/sramfiletarget.hh

if WINDOWS
dwsrame_SOURCES += res/windows.rc
endif

.rc.o:
	windres @WX_INCLUDES@ -o $@ $<

.xrc.cc:
	wxrc -c -o $@ $<

dwsrame.app: dwsrame res/dwsrame.icns res/Info.plist
	-mkdir dwsrame.app
	-mkdir dwsrame.app/Contents
	-mkdir dwsrame.app/Contents/MacOS
	-mkdir dwsrame.app/Contents/Resources
	cp dwsrame dwsrame.app/Contents/MacOS
	cp res/Info.plist dwsrame.app/Contents
	cp res/dwsrame.icns dwsrame.app/Contents/Resources
	echo -n 'APPL????' > dwsrame.app/Contents/PkgInfo
