@CLS
@SET CPPFLAGS=-O2 -Werror -Wall -Wextra -Wpedantic -std=c++17 ^
	-mwindows -g -s ^
	-Wno-unused-function -Wno-unused-parameter -Wno-unused-variable ^
	-lm ^
	-Wno-format-nonliteral ^
	-Wformat=2 -Wformat-security ^
	-Wnull-dereference -Wstack-protector -Wtrampolines -Wvla ^
	-Warray-bounds=2 ^
	-Wshift-overflow=2 -Wcast-qual ^
	-Wconversion -Wlogical-op -Wduplicated-cond ^
	-Wformat-signedness -Wshadow -Wstrict-overflow=4 ^
	-Wundef -Wswitch-enum ^
	-Wstack-usage=10000 ^
	-D_FORTIFY_SOURCE=2 ^
    -fstack-protector-strong -fPIE -fsanitize=address ^
	-fsanitize=leak -fno-omit-frame-pointer -fsanitize=undefined ^
	-fsanitize=bounds-strict -fsanitize=float-divide-by-zero ^
	-fsanitize=float-cast-overflow

@SET CPP_FILES=".\src\*.cpp"
@SET BUILD_OUPUT=".\build\wxtest"
@SET LOCAL_INC=".\include"
@SET WX_BASE_PATH=C:\Users\pierre\Downloads\wxWidget\
@SET MQTT_BASE_PATH=C:\Users\pierre\Downloads\mosquitto-2.0.14
@SET MOSQ_LIB="%MQTT_BASE_PATH%\include"
@SET MQTT_LIB="%MQTT_BASE_PATH%\lib"
@SET MQTT_LIB_CPP="%MQTT_BASE_PATH%\lib\cpp"
@SET MOSQ_BUILD_LIB_CPP="%MQTT_BASE_PATH%\build\lib\cpp"
@SET WX_HEADERS_INC="%WX_BASE_PATH%wxWidgets-3.1.5-headers\include"
@SET WX_DLL_DEV=wxMSW-3.1.5_gcc1020_x64_Dev\lib\gcc1020_x64_dll
@SET WX_MSWUD="%WX_BASE_PATH%%WX_DLL_DEV%\mswud"
@SET WX_DLL_PATH="%WX_BASE_PATH%%WX_DLL_DEV%"

@ECHO -- Build start --
@ECHO - Headers pathes :
@ECHO  * wxwidget : %WX_HEADERS_INC%
@ECHO  * mosquitto : %MOSQ_LIB%
@ECHO - Lib pathes :
@ECHO  * wxwidget : %WX_DLL_PATH%
@ECHO  * mosquitto : %MOSQ_BUILD_LIB_CPP%

@g++ %CPP_FILES% ^
    %CPPFLAGS% ^
    -o %BUILD_OUPUT% ^
    -I %LOCAL_INC% ^
    -I %MOSQ_LIB% ^
    -I %MQTT_LIB% ^
    -I %MQTT_LIB_CPP% ^
    -I %WX_HEADERS_INC% ^
    -I %WX_MSWUD% ^
    -L %WX_DLL_PATH% ^
    -l "wxbase31u" ^
    -l "wxmsw31u_core" ^
    -L %MOSQ_BUILD_LIB_CPP% ^
    -l "mosquittopp"

@ECHO -- Build end --
