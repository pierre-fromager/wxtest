
SET CPP_FILES=".\src\*.cpp"
SET BUILD_OUPUT=".\build\wxtest"
SET LOCAL_INC=".\include"
SET WX_BASE_PATH=C:\Users\pierre\Downloads\wxWidget\
SET MQTT_BASE_PATH=C:\Users\pierre\Downloads\mosquitto-2.0.14
SET MOSQ_LIB="%MQTT_BASE_PATH%\include"
SET MQTT_LIB="%MQTT_BASE_PATH%\lib"
SET MQTT_LIB_CPP="%MQTT_BASE_PATH%\lib\cpp"
SET MOSQ_BUILD_LIB_CPP="%MQTT_BASE_PATH%\build\lib\cpp"
SET WX_HEADERS_INC="%WX_BASE_PATH%wxWidgets-3.1.5-headers\include"
SET WX_DLL_DEV=wxMSW-3.1.5_gcc1020_x64_Dev\lib\gcc1020_x64_dll
SET WX_MSWUD="%WX_BASE_PATH%%WX_DLL_DEV%\mswud"
SET WX_DLL_PATH="%WX_BASE_PATH%%WX_DLL_DEV%"

g++ %CPP_FILES% ^
    -mwindows ^
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