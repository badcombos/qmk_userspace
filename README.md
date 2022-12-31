# qmk_userspace
Holds all code for QMK keyboards in one place, rather than split across seperate folders

## Userspace Inspiration
- filterpaper's tutorial [tutorial](https://filterpaper.github.io/qmk/userspace) and [repo](https://github.com/filterpaper/qmk_userspace) 
- jbar21's [repo](https://github.com/jbarr21/qmk_userspace) was also used for reference

# Makefile
Used to easily compile keymaps with `make`
Makefile adapted from [Patrick Elmquist's repo](https://github.com/patrick-elmquist/keymaps)

## Make Commands
1. `make setup`
Clones qmk:master through git submodules
2. `make <keyboard>`
Compiles specific keyboard
3. `make all`
Compiles all keyboards
3. `make clean`
Removes qmk submodules and `./build` folder
