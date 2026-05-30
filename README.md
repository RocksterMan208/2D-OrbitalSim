This project is made for Hackclub and the Horizons Berlin event.

# What is the project?
The project will aim to show a window which will present the user with an interface of creating some objects with presets where physics will then be applied using Newtonian physics. Other features may be added, however this is the planned course of the project at the current moment.
# Requirements
## To compile the project yourself, you will need to install the raylib package.
### On Arch Linux, this can be done by:
Running the following command into your terminal
```
sudo pacman -S raylib
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
- The programme will create a white window which displays a central planet (which may represent the sun or whatever you want because it is a placeholder) and an orbiting planet/moon with a path.
- The programme does involve movement and a time warp function (beware with the time warp function as it is unstable at high speeds.)
- I aim to add some features to the programme which mean the user can interact properly with each object without changing any code.
