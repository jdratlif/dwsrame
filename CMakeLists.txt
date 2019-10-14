# minimum cmake version
cmake_minimum_required(VERSION 3.5)

# set the project name and version
project(dwsrame VERSION 1.0)

# create config file
configure_file(config.h.in config.h)
add_definitions(-DHAVE_CONFIG_H)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# enable compiler warnings
if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

# setup the module path
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}")

# locate and add wxWidgets
set(wxWidgets_ROOT_DIR "C:/wxWidgets-3.1.2")
set(wxWidgets_LIB_DIR "C:/wxWidgets-3.1.2/lib/vc_x64_lib")
set(wxWidgets_CONFIGURATION "mswu")

find_package(wxWidgets COMPONENTS core base adv html xml xrc REQUIRED)
include( "${wxWidgets_USE_FILE}" )
link_libraries(${wxWidgets_LIBRARIES})

# add include directories
include_directories("${PROJECT_BINARY_DIR}" "source")

# add the sources
set(SRCS source/dwsrame.cc source/dwsrame.hh
    source/exception/invalidsramfileexception.cc
    source/exception/invalidsramfileexception.hh
    source/model/sramfile.cc source/model/sramfile.hh
    source/view/mainframe.cc source/view/mainframe.hh
    source/view/sramfiletarget.cc source/view/sramfiletarget.hh
    source/res/resource.cpp)

# add the resource file on Windows
if(WIN32)
  set(SRCS ${SRCS} source/res/windows.rc)
endif(WIN32)

# add the icon file for macOS
set(MACOSX_BUNDLE_ICON_FILE dwsrame.icns)

set(APP_ICON "${PROJECT_SOURCE_DIR}/source/res/dwsrame.icns")
set_source_files_properties("${APP_ICON}" PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

# add the executable
add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE "${APP_ICON}" ${SRCS})
