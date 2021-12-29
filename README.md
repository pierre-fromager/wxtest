# WxTest Mqtt

Basic ranking c++17 wxWidget App starter kit.  
[wxWidget](https://www.wxwidgets.org/) GUI lib is cross-platform compliant.  
This branch(mqtt) let app to pubsub through mqtt, up to you to change topics according to your requirements.  

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
* **wxCommandEvent** subclassing for custom event design (MyMqttEvent).
* **wxListCtrl** for list management with XPM icons design.
* **wxTimer** for timestamp management.
* Most common widgets like wxMenuBar,wxMenu,wxStatusBar,wxButton,wxRadio,etc... 

## Requirements

### Compiler
* g++

### wxWidget
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

### Mqtt

#### Requirements

Mosquitto dev lib (mosquittopp) c++ wrapper is required.

```
sudo apt-get install mosquitto-dev libmosquitto-dev libmosquittopp-dev
```

Thus, a mqtt data broker([Mosquitto](https://mosquitto.org)) is required, change mqtt config in [Mqtt config broker](include/mqttbroker.h) according to your need.  
If you are not using credentials to broker remove them from myMqtt ctor initialization.  
Keep in mind mqtt mid(pseudo) should be unique (one by App instance) otherwise side effects (connect/disconnect) will occur.  
Relevant broker definitions can be found [there](include/mqttbroker.h).    
Mqtt(myMqtt) main class can be found [there](include/mymqtt.h) instanciated by App.  
When mqtt subscription event is triggered we generate a [**MyMqttEvent**](include/mqttevent.h) event sending both topic and payload to the frame.  
We listen to event from frame (topic related) then we apply feature to the matching topic.  
So we keep loose coupling app, mqtt and frame.

#### Topics

(PUB/SUB) : in [topics](./include/mqtttopics.h) definition.  

### Doxygen 
* doc generator.

### Cppcheck 
* C++ code checker.  
* Hereby used with std c++11 but should be c++17.  

## Fixtures

In fixtures folder you can find 2 folders:

* bash : to let you pubsub from bash (change config according to your infra).
* node-red : to load node red script to pubsub according to wxtest topics (change mqtt setup according to your infra).

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
Doc will be generated in doc/html folder.

### Clean doc

```
make cleandoc
```

## Code check

```
make check
```

## Test

* Testing UI is evil because most of members and props are privates.
* Separate logic from UI is recommended to achieve this.
* May be using [boost test lib](https://www.boost.org/doc/libs/1_52_0/libs/test/doc/html/index.html) let you doing so.

## Links

* [wxWidget](https://docs.wxwidgets.org/3.0/) doc.
* For Microsoft users, [setup vscode](https://stackoverflow.com/questions/30269449/how-do-i-set-up-visual-studio-code-to-compile-c-code) for cpp project.
* [Mosquitto](https://mosquitto.org/) official.
* [Mqtt](https://www.hivemq.com/blog/mqtt-essentials-part-5-mqtt-topics-best-practices/) best practices.
