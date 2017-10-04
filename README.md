# MysteryDots
##DESCRIPTION:
A very simple Dots game made with the SFML library (http://www.sfml-dev.org/).

##PURPOSE:
This game was created to demo the use of SFML on the Raspberry Pi.  Since the Raspbian OS added an experimental GL driver, games running on SFML can run on the RPi 2 or 3.  The code was designed to make it easy to change certain characteristics of the game.  When demonstrating the RPi to non-coders or beginners, this game illustrates and promotes how easy it is to make modification to code.

##DESCRIPTION:
Player controls a little dot and needs to stay away from enemy dots for the longest time possible.  
NOTE: MysteryDots needs a gamepad controller to play.

##CODE DETAILS:
The Launcher.cpp can be used to show non-coders what C++ source code looks like.  It was made to be easy and intuitive for someone to make small configuration changes to the game.

##INSTALLATION:
Before building the MysteryDots game, you need to download the SFML source code and build it on the RPi.  First, you need to install tools and dependencies required to build SFML.

Tools :
  - sudo apt-get install cmake

sfml-window dependencies :
  - sudo apt-get install libx11-dev libxcb1-dev libx11-xcb-dev libxrandr-dev libxcb-randr0-dev libxcb-image0-dev libgl1-mesa-dev libudev-dev -y

sfml-graphics dependencies :
  - sudo apt-get install libfreetype6-dev libjpeg-dev -y

sfml-audio dependencies :
  - sudo apt-get install libopenal-dev libflac-dev libvorbis-dev -y

Now, download the latest stable release source code (from http://www.sfml-dev.org/download.php) and extract the zip file.
From a terminal window, navigate into the extracted SFML source code directory and type the following commands:
  - cmake ./
  - sudo make install
  - sudo ldconfig

Finally, download the MysteryDots source code, navigate into the MysteryDots directory and type the following commands:
  - make all

The executable should be ready in the bin directory.
