###Nebula Draw

Nebula Draw is a Terminal User Interface (TUI) drawing application, created by the Nebula Centre Project with moderate collaboration from Shreda5 and licensed under the GPL V3 License. Nebula Draw strives to be a high quality method to create ASCII graphics on low-resource systems.

####Installation and Execution Instructions

**Note**: Nebula Draw currently only supports Linux based operating systems. A macOS version is planned for future release.

Verify the ncurses library is present on your system. Most major Linux distributions come with the library preinstalled.
Installation from Source
Installing from source is the preferred way to install Nebula Draw. Compiling a binary from the source code ensures that it will perform the best on your system and allows you to check the validity of the application.

**Note**: Verify the gcc compiler is installed on your system. Most major Linux distributions come with it preinstalled.

    1. Download the source code (nebula\_draw.c) and the Makefile (Makefile).
    2. Open your favorite terminal emulator and enter the following command:
    	`cd ~/Downloads; make` **
    3. Then launch Nebula Draw by entering the following command:
    	`./ndraw`
    4. Press the "?" key to view help for getting started with the application.
    5. * 

####Binary Installation

Installing from binary results in potentially lower performance than installing from source. However this method is slightly less complex for the average user.

    1. Download the compiled binary (ndraw).
    2. Open your favorite terminal emulator and enter the following command:
    	`cd ~/Downloads` **
    3. Then launch Nebula Draw by entering the following command:
    	`./ndraw`
    4. Press the "?" key to view help for getting started with the application.
    5. * 

######\* Optional: If you would like to launch Nebula Draw without having to change your working directory, copy ndraw to /usr/bin/ by running the following command as superuser (su, sudo):
`cp ~/Downloads/ndraw /usr/bin` *

######\*\* If the download directory on your web browser is different, substitute ~/Downloads with the correct path.

Contact (https://nebulacentre.net/contact.html) the administrator in regard to any inquiries about Nebula Draw. 
