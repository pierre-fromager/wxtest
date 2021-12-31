# WxTest

Basic ranking c++17 wxWidget App starter kit.  
[wxWidget](https://www.wxwidgets.org/) GUI lib is cross-platform compliant.  
To go further, if you want to play with mqtt, checkout mqtt branch.  

## Screenshots

### UI
![ui](doc/assets/img/screenshot_ui.jpg)

### Log
![log](doc/assets/img/screenshot_log.jpg)

## Components

App uses :

* **wxApp** ready for wxGetApp feature as singleton pattern.
* **wxLog** as file logger with efficient log level managment.
* **wxFrame** inherited as single frame design.
* **wxPanel** multiple panels used by **wxSplitter**.
* **wxSplitter** & **wxSiser** for h/v auto layout adjustments.
* **wxCommandEvent** subclassing for custom event design (MyFooEvent).
* **wxListCtrl** for list management with XPM icons design.
* **wxTimer** for timestamp management.
* Most common widgets like wxMenuBar,wxMenu,wxStatusBar,wxButton,wxRadio,etc... 

## Requirements

### Compiler
* g++

### wxWidget dev lib
wWidget dev library (3.0) and above.
* Check installed version on debian.

```
dpkg -l | grep 'wxWidget' | grep dev
```

* Check all wWidget available dev lib to be installed.

```
apt-cache search 'wxWidget' | grep dev
```

* Minimal install on debian.

```
sudo apt-get install libwxbase3.0-dev libwxgtk-media3.0-dev libwxgtk3.0-dev  
```

### Doxygen 
* doc generator.

### Cppcheck 
* C++ code checker.  
* Hereby used with std c++11 but should be c++17.  

## Build

### Linux

#### Build app

```
make
```

#### Clean build

```
make clean
```

#### Build doc

```
make doc
```
Doc will be generated in doc/html folder.

#### Clean doc

```
make cleandoc
```

#### Code check

```
make check
```

### Win32

#### Build app
Install [mingw64 from MSYS2 with gcc/g++](https://www.youtube.com/watch?v=aXF4A5UeSeM) package using pacman.  
Download wxwidget prebuild ([Download Windows Binaries](https://www.wxwidgets.org/downloads/)) mathing your arch x86/x86_64 :
* Header Files.
* Development File.
* Release DLLs.  

Edit buildw32.cmd changing the base path.  
Create a build folder at project root.  
Then run the command below.  
```
buildw32.cmd
```
As non static built you should add 2 dlls to distribute the runtime :
* wxbase315u_gcc1020_x64.dll
* wxmsw315u_core_gcc1020_x64.dll

Both of them should be found in your prebuild.

## Test

* WIP but may be through boost tests.

## Links

* Official [wxWidget doc](https://docs.wxwidgets.org/3.0/)
* For Microsoft users, [setup vscode](https://stackoverflow.com/questions/30269449/how-do-i-set-up-visual-studio-code-to-compile-c-code) for cpp project.
