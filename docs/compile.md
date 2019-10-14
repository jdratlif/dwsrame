# emuWorks Software Compilation Guide v2.0 (October 19, 2019)

## Overview

This is a guide to building emuWorks C++ software with wxWidgets or Qt toolkits.

All of our software is designed to run on Windows, Linux, and macOS.
We have tested these compilation instructions on Windows 10, Ubuntu 16.04 (Xenial Xerus), and macOS 10.14 Mojave.

To build our software, you will need three things.

1. A C++ compiler
1. CMake 3.5 or newer
1. wxWidgets >= 3.1 or Qt 5, depending on which software you are building

## Platform Specifics

### Windows

#### Compiler

For the C++ compiler, we recommend Visual Studio for Windows.
As of this writing, the current edition is Visual Studio 2019.
The community edition is free, though you will need to register it with a Microsoft account to keep it activated.
Although MinGW should work, it has not been tested.

#### CMake

CMake is available from [their website](https://cmake.org).

#### wxWidgets

We were not able to use the pre-built wxWidgets 3.1.2 binaries with cmake.
We suggest you compile wxWidgets from source.

You can download the source code from [their website](https://www.wxwidgets.org).
You can use the installer, or grab one of the compressed archives and extract it.

Create a directory somewhere to use as the build directory.
It can be on your desktop, or anywhere else you choose.
Open a PowerShell prompt in this directory and use cmake to create the Visual Studio project files.

Replace WX_SOURCE_DIR with the path to the wxWidgets source code (e.g. C:\wxWidgets-3.1.2).
Replace WX_INSTALL_DIR with the path you want wxWidgets installed (e.g. c:\wxWidgets-3.1.2\release-static).
wxWidgets does not work in paths that have spaces, so avoid those.

You can leave off the -DwxBUILD_SHARED=Off part if you want to build wxWidgets as shared library, but you will have to put the libraries in the Windows path.
This document does not cover doing that.

```powershell
cmake [WX_SOURCE_DIR] -DCMAKE_INSTALL_PREFIX=[WX_INSTALL_DIR] -DwxBUILD_SHARED=Off
```

This will create a wxWidgets Visual Studio solution in your build directory.
Open it in Visual Studio.
Change the Solution Configuration is `Release`, and build the solution.
Once it is done building, select the `INSTALL` target from the Solution Explorer and build it.

Now you should have a ready to use wxWidgets libary in \[WX_INSTALL_DIR\] (e.g. c:\wxWidgets-3.1.2\release-static).

#### Building emuWorks software with wxWidgets and cmake

Create a directory to build the program in.
Open a terminal (e.g. PowerShell) in this directory and run the following commands.
Replace \[PROGRAM_SOURCE_DIR\] with the path to the source code you downloaded (e.g. c:\Users\john\Downloads\dwsrame-1.0).
Replace \[WX_INSTAL_DIR\] with the path you installed wxWidgets into (e.g. c:\wxWidgets-3.1.2\release-static).

```powershell
cmake [PROGRAM_SOURCE_DIR] -DwxWidgets_ROOT_DIR=[WX_INSTALL_DIR]
```

This will create a Visual Studio solution in your build directory.
Open the solution.
Change the Solution Configuration to `Release` and build the solution.
There should now be an executable in the Release directory of your build folder.

### Linux

#### Compiler

For Linux, we suggest g++.
clang should also work, but it has not been tested.
Gentoo includes g++ by default.

* `sudo apt install build-essential` (Debian / Ubuntu)
* `sudo yum groupinstall 'Development Tools'` (RedHat)
* `sudo pacman -S base-devel` (Arch)

#### CMake

CMake should be available from your package manager.
On CentOS 7 cmake3 is in epel.

* `sudo apt install cmake` (Debian / Ubuntu)
* `sudo yum install cmake3` (CentOS 7)
* `sudo dnf install cmake` (Fedora / CentOS 8)
* `sudo pacman -S cmake` (Arch)
* `sudo emerge dev-util/cmake` (Gentoo)

#### wxWidgets

Your distribution might include wxGTK development packages.
Although they may work, we have not tested them.
We suggest compiling wxWidgets from source.

You can download the wxWidgets source from [their website](https://wxwidgets.org/downloads).
Version 3.1.2 or later is recommended.

Once you have the source, extract it into a directory.
Run the following commands in a terminal to build the library.

Replace \[WX_SOURCE_DIR\] with the path where you extracted the wxWidgets source (e.g. $HOME/wxWidgets/3.1.2/source).
Replace \[WX_INSTALL_DIR\] with the path where you want to install the wxWidgets libraries (e.g. $HOME/wxWidgets/3.1.2/release-static).

If you want to speed up compilation, you can utilize multiple CPU cores.
To do this, add a -j# option to the nice make part, where # is how many CPU cores you have (e.g. 4).
If you want to install wxWidgets to a central location (like /usr/local), you might need to prefix the make install command with `sudo` or run it as root.

```bash
mkdir /tmp/build-wx && cd /tmp/build-wx
[WX_SOURCE_DIR]/configure --prefix [WX_INSTALL_DIR] --disable-shared --enable-stl --enable-utf8 --enable-cxx11 --with-cxx=14
nice make
make install
cd && rm -rf /tmp/build-wx
```

#### Building emuWorks software with wxWidgets and cmake

Open a terminal and go to the path where you copied the source code.
Run the following commands.

Replace \[WX_INSTALL_DIR\] with the path where you installed wxWidgets.

```bash
mkdir build
export PATH=[WX_INSTALL_DIR]/bin:$PATH
cmake ..
nice make
```

### macOS

#### Compiler

On macOS, you will need the Xcode command line tools for your version of macOS.
You can download them from the Apple developer site.

#### CMake

CMake is available from [their website](https://cmake.org).

#### wxWidgets

See the Linux directions for building wxWidgets from source on macOS.

#### Building emuWorks software with wxWidgets

The macOS build directions are nearly identical to the Linux directions.
You will need to make sure the CMake command line binaries are in your path.
You can do this by running `export PATH=/Applications/CMake.app/Contents/bin:$PATH`.
After that, just follow the Linux instructions.

For Qt based programs, you'll need Qt 5. Most of our software was built with
Qt 4 originally, so any version of Qt 5 should work, but we have only tested
version 5.12.5, the most recent stable version as of this writing.
