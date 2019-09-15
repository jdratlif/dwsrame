dnl Initialize autoconf
AC_INIT([dwsrame], [0.91b], [webmaster@technoplaza.net])

dnl require autoconf >= 2.69
AC_PREREQ([2.69])

dnl use the config.h header
AC_CONFIG_HEADERS([config.h])

dnl initialize automake
AM_INIT_AUTOMAKE([1.16.1 dist-bzip2])

dnl host system check
AC_CANONICAL_HOST

dnl AM_CONDITIONAL([WINDOWS], test x$host_os = xmingw32)
AM_CONDITIONAL([WINDOWS],
               [case $host_os in
               mingw32 | cygwin ) test x = x ;;
               * ) test 0 = 1 ;;
               esac])

dnl check for c++ compiler and BSD install
AC_PROG_CXX
AC_PROG_INSTALL

AC_ARG_WITH(macosx-version-min,    [  --with-macosx-version-min=VER   build binaries which require at least this OS X version], [
        USE_MACOSX_VERSION_MIN=$withval
    ])

if test "x$USE_MACOSX_VERSION_MIN" = "xno"; then
    USE_MACOSX_VERSION_MIN=
elif test "x$USE_MACOSX_VERSION_MIN" = "xyes"; then
    USE_MACOSX_VERSION_MIN=
fi

if test "x$USE_MACOSX_VERSION_MIN" != "x"; then
    MACOSX_VERSION_MIN_OPTS="-mmacosx-version-min=$USE_MACOSX_VERSION_MIN"
    CPPFLAGS="$CPPFLAGS $MACOSX_VERSION_MIN_OPTS"
    CFLAGS="$CFLAGS $MACOSX_VERSION_MIN_OPTS"
    CXXFLAGS="$CXXFLAGS $MACOSX_VERSION_MIN_OPTS"
    LDFLAGS="$LDFLAGS $MACOSX_VERSION_MIN_OPTS"
fi

dnl tests for wxWidgets
AM_OPTIONS_WXCONFIG
AM_PATH_WXCONFIG([2.8.0], HAVE_WXWIDGETS=1, HAVE_WXWIDGETS=0)

if test $HAVE_WXWIDGETS -eq 1; then
    CPPFLAGS="$CPPFLAGS $WX_CPPFLAGS"
    CFLAGS="$CFLAGS $WX_CFLAGS_ONLY"
    CXXFLAGS="$CXXFLAGS $WX_CXXFLAGS_ONLY"
    LIBS="$LIBS $WX_LIBS"
else
    AC_MSG_ERROR([wxWidgets 2.8 is required.
                  Please install wxWidgets from http://www.wxwidgets.org.
                  
                  This error could also be the result of a non-standard install
                  path or a missing wx-config program.])
fi

dnl configure files to produce
AC_CONFIG_FILES([Makefile source/Makefile])
AC_OUTPUT
