# ACTS-Sensor
This repository contains code for the ACTS sensor module.
The use of this repository is limited to the ACTS project.

--- New documentation ---
ACTS-Sensor

Brief explanation about project
### Required software
- Linux, Mac or Windows
- [ESP-IDF 2.1](http://esp-idf.readthedocs.io/en/v2.1/)

ACTS-Sensor

##Brief explanation about project
This project is meant to collect detailed data from cva patients. This can then be parsed by complex algorithms and scientists to study movement in these patients. The sensor module also creates a simple performance index that is sent to an aws backend server. These performance indexes are then parsed to provide feedback to therapists and cva patients on which they can improve.

###Technical description
This project can be run on a esp32 with ESP-iDF (2.1). It collects data sensor data from a BMP280 and MPU9250.
This data is sampled at (currently) 100Hz and stored in an sd card. It also creates a performance index counter based on intensity of sampling data. This is then send to an aws backend server. The results can be retrieved from the backend server to generate statistics.

Project Setup
	Requirements
	Installation
Project features
Software how to guide
	Models + description
	setup own project types
Known bugs/issues
Future version features/fixes

--- End of new documentation ---

## Project Setup
### Required software
- Linux, Mac or Windows
- [ESP-IDF 2.1](http://esp-idf.readthedocs.io/en/v2.1/)

![alt text](https://github.com/HU-ACTS/ACTS-Sensor/blob/master/sensorimg1.jpg)

### Required Hardware
- ESP32 Wifi enabled microcontroller
- SD Cardreader SPI
- BMP280 Pressure & Temperature sensor
- MPU-9250 9DOF Magneto, Gyro, Accel

### Installation
The installation instructions are split up in to two segments: Windows and Linux.
They consist out off a short installation instruction and a long version. 
The short version points to the manufactors instructions (this is to have the most accurate and up-to-date version). 
The long version is an extract from these pages as of 11-10-2017. 
As long as none of the manufactors have changed their procedures this should be accurate.
USE WITH CAUTION AND COMMON SENSE.

#### Windows: short version
1. Have a computer that has the latest version of Windows installed.
2. Install the ESP-IDF toolchain. For a very well written guide on how to this:
https://esp-idf.readthedocs.io/en/latest/get-started/windows-setup.html
3. Install Atom: 
https://flight-manual.atom.io/getting-started/sections/installing-atom/#platform-windows
4. Install the Platformio plugin on top of Atom: 
http://platformio.org/get-started/ide?install=atom
Note: Both Atom and Platformio might take a while to install.

#### Linux: short version
1. Have a computer with a up-to-date version of a Linux distro.
2. Install the ESP-IDF toolchain. For a very well written guide on how to this:
https://esp-idf.readthedocs.io/en/latest/get-started/linux-setup.html
3. Install Atom: 
https://flight-manual.atom.io/getting-started/sections/installing-atom/#platform-linux
4. Install the Platformio plugin on top of Atom: 
http://platformio.org/get-started/ide?install=atom
Note: Both Atom and Platformio might take a while to install.

#### Windows: long version
1. Download the ESP-IDF, https://dl.espressif.com/dl/esp32_win32_msys2_environment_and_toolchain-20170918.zip
2. Unzip the downloaded zip file to c:\.
3. Go into this newly created directory and run the C:\msys32\mingw32.exe.
4. In the newly opened terminal type:
```
cd ~/esp
git clone --recursive https://github.com/espressif/esp-idf.git
```
5. Close the terminal window and go to C:\msys32\etc\profile.d\ and create a file called export_idf_path.sh.
6. Open the file and write and save: 
``` export IDF_PATH="C:/msys32/home/**_USER-NAME_**/esp/esp-idf" ```
7. Install Atom, by downloading the installer https://atom.io/download/windows_x64
8. Execute the installer
9. Go to file -> settings -> install
10. Search and install platformio-ide
11. Your installation is now finished, clone the code from this repo and import it with platform io as a project.

#### Linux: long version
1. Install the prerequisites for IDF:
```
sudo apt-get install git wget make libncurses-dev flex bison gperf python python-serial
```
2. Download the esp toolchain, https://dl.espressif.com/dl/xtensa-esp32-elf-linux64-1.22.0-73-ge28a011-5.2.0.tar.gz (64 bit)
3. Unzip the downloaded tar with tar -xzf <tar>. and move to a new folder ~/esp.
4. Get the ESP-IDF from git with a recursive clone:
```
cd ~/esp
git clone --recursive https://github.com/espressif/esp-idf.git
```
5. Open ~/.profile and write and save with (nano, vim, atom, etc): 
``` export IDF_PATH="/home/**_USER-NAME_**/esp/esp-idf" 
    export PATH="$PATH:$HOME/esp/xtensa-esp32-elf/bin"
```
6. Download Atom .deb: https://atom.io/download/deb
7. For debian based distro's install using:
  ```
  sudo dpkg -i atom-amd64.deb
  sudo apt-get -f install
  ```
8. Start Atom and go to Edit -> preferences -> install
9. Search and install Platformio-ide
10. Your installation is now finished, clone the code from this repo and import it with platform io as a project. 

## Configuration
### Configuration of Atom/Platformio
When you try to launch Atom, it automagicly launches as platformio (since it is a plugin of atom).
To configure a project that builds for esp32 and runs on it, the platform.ini file requires the following config:
(REQUIRES MORE DETAILED CONFIGURATION EXPLAINATION)

```
platform = espressif32
board = featheresp32
framework = espidf
```

You could also head to the template branch and copy paste the project from there by going to the tab PlatformIO and then selecting open project from that page.

#### Installation of Platform IO

To see installed packages or install new packages, go to the tab ```File -> Settings ```. From there navigate to Packages.

The following packages are recommended to install in Atom:
Build (0.68.0+) by noseglid
Busy (0.7.0+) by noseglid 
file-icons (2.1.12+) by file-icons
language-ini (1.19.0+) by jacobbednarz
linter (2.2.0+) by steelbrain (Has cow powers!)
linter-gcc (0.7.1+) by hebaishi
linter-ui-default (1.6.10+) by steelbrain
markdown-preview-plus(2.4.10+) by atom-community
### Configuration of ESP-IDF
ESP-IDF should be configured correctly if it is installed correctly.

### Running your project
To run your project, a tab to the left should show an arrow pointing to the right. This button builds and runs. Upload ports and config are searched for by platformio when left on default settings. These can be changed in platformio.ini (REQUIRES LINK). To open the Serial Monitor for communication, a button to the left that resembles a wall plug can be selected or tab ```PlatformIO -> Serial Monitor ``` or ```Alt + Shift + M ```.
~Good luck developing more content from the ACTS Team and me ♥.
## More reads

## Links/References
* ESP32: http://espressif.com/en/products/hardware/esp32/overview
* ESP32 setup: http://espressif.com/en/products/hardware/esp32/overview
* Atom: https://atom.io/
* PlatformIO: http://platformio.org/
4. Install the Platformio plugin on top of Atom: 
http://platformio.org/get-started/ide?install=atom
Note: Both Atom and Platformio might take a while to install.
