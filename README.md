# qmk_userspace
Holds all code for QMK keyboards in one place, rather than split across seperate folders

## Userspace Inspiration
- filterpaper's tutorial [tutorial](https://filterpaper.github.io/qmk/userspace) and [repo](https://github.com/filterpaper/qmk_userspace) 
- jbar21's [repo](https://github.com/jbarr21/qmk_userspace) was also used for reference

# Makefile
used to compile easily with `make`
Adapted from [Patrick Elmquist's repo](https://github.com/patrick-elmquist/keymaps)

## make commands
1. `make setup`
clones qmk:master through git submodules
2. `make <keyboard>`
compiles specific keyboard
3. `make all`
compiles all keyboard
3. `make clean`
removes qmk submodules and `./build` folder
