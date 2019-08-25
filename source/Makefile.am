AUTOMAKE_OPTIONS = subdir-objects
CLEANFILES = res/dwsrame.cc
EXTRA_DIST = res/dwsrame.xrc res/windows.rc

bin_PROGRAMS = dwsrame

dwsrame_SOURCES = dwsrame.cc dwsrame.hh \
	exception/invalidsramfileexception.cc \
	exception/invalidsramfileexception.hh \
	model/sramfile.cc model/sramfile.hh \
	view/mainframe.cc view/mainframe.hh

nodist_dwsrame_SOURCES = res/dwsrame.cc

if WINDOWS
dwsrame_SOURCES += res/windows.rc
endif

.rc.o:
	windres @WX_INCLUDES@ -o $@ $<

.xrc.cc:
	wxrc -c -o $@ $<

