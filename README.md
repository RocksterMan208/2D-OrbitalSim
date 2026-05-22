This project is made for Hackclub and the Horizons Berlin event.

# What is the project?
This project is what I am using to learn a new rendering library, SDL2, and it will render a 2D impression of orbital simulation of some objects.

The project will aim to show a window which will present the user with an interface of creating some objects with presets where physics will then be applied using Newtonian physics. Other features may be added, however this is the planned course of the porject at the current moment.
# How is the project made?
The project is made using SDL2 and is being used mainly as a learning process, as stated before, so I can create further projects using the library. I am using a linux machine to code the project and I ahev no means as of now to test the project for Windows computers.
# Requirements
## To compile the project yourself, you will need to install the SDL2 package.
### On Arch Linux, this can be done by:
Running the following command into your terminal
```
sudo pacman -S sdl2
```
## You must also ensure that you have make installed (Please note that a CMAKE preset has not been made currently and will NOT work)
# Compiling the code
Once you have cloned the repository, to compile it you must first cd into the folder, then do the following command inside of your terminal to compile and then run the program:
```
make run
```
Otherwise, if you just want to compile the code:
```
make
```
# Current progress of the project:
- The program only creates a window when run
