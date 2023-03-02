# Project
This project aims to create a version of the game "Flappy Bird", which functions on the PIC32 Chipkit, as a part of the IS1200 VT23 Computer Hardware Engineering course at KTH. 
This is done in collaberation between Erik Paulinder and Mohammed Louai Alayoubi, and built upon previous exercises in the course. 

Prerequisites for installation:

    Chipkit Uno32 with bootloader. The bootloader is already installed on a stock unit. If you need to install a bootloader, see the document Installing the bootloader
    Pic32 Toolchain installed on your computer.
    Drivers for the FTDI usb to serial chip
        Linux: The drivers are already installed on your system.
        Windows: The drivers should download automatically from Windows update when you plug your Uno32 into your computer.
        Mac: Drivers should install automatically. If they don't, download the drivers from the FTDI website for your version of MacOS X.

Building the sources:

    To build the sources, first enter the cross compiling environment. This is done by sourcing the environment file in your shell.

    Entering the toolchain environment on MSYS2 or Linux:

      If your toolchain is installed in the default location, you can source the cross compiling environment by typing
      . /opt/pic32-toolchain/environment in your shell. Note the space between the dot and the slash.

    Entering the toolchain environment on MacOS X:

      Launch the toolchain environment app and it will give you a terminal window with your command line marked
      [PIC32 CROSS], this indicates you're using the PIC32 toolchain.
      Building in the environment

    Next, enter the directory with the source code. To start the compilation, type make in the shell.
    Installing

    To install hello leds to your Uno32, you need to first figure out the name of the usb serial port. You can do this by looking at /dev as you plug and unplug the Uno32 to your computer.

        Linux: This is normally /dev/ttyUSB0
        Windows: In MSYS2, this is normally /dev/ttyS2
        Mac: This is normally /dev/cu.usbserial-*

    When you know the path to your serial device, issue the command
    make install TTYDEV=/dev/ttyUSB0, substituting the correct path of the device.

    During the flashing process, the LEDs LD4 and LD5 on the Uno32 should start blinking. When the process in done, the program should 
