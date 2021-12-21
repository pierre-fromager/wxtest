# WxTest

Basic c++17 wxWidget App starter kit.  

## Components

App uses :

* **wxApp** ready for wxGetApp feature as singleton pattern.
* **wxLog** as file logger with efficient log level managment.
* **wxFrame** inherited as single frame design.
* **wxPanel** multiple panels used by **wxSplitter**.
* **wxSplitter** & **wxSiser** for h/v auto layout adjustements.
* **wxCommandEvent** subclassing for custom event design (MyFooEvent).
* **wxListCtrl** for list management with XPM icons design.
* **wxTimer** for timestamp management.
* Most common widgets like wxButton,wxRadio group,etc... 

## Requirements

* **g++** as compiler.
* **wxWidget dev lib** as wWidget dev library 3.0.
* **Doxygen** as doc generator.
* **Cppcheck** as code checker (hereby used with std c++11 but should c++17).

## Build

### Build app
```
make
```
### Clean build
```
make clean
```
### Build doc
```
make doc
```
### Clean doc
```
make doc
```

## Code checker
```
make check
```

## Test

* WIP but may be through boost tests.
