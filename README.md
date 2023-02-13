# qmk_userspace
Holds all code for QMK keyboards in one place, rather than split across seperate folders

## Userspace Inspiration
- filterpaper's [tutorial](https://filterpaper.github.io/qmk/userspace) and [repo](https://github.com/filterpaper/qmk_userspace) 
- jbar21's [repo](https://github.com/jbarr21/qmk_userspace) was also used for reference

# Makefile
Used to easily compile keymaps with `make`. \
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

# Features
## Andrewjrae's Case Modes
Uses [@Andrewjrae](https://github.com/andrewjrae)'s extention of Caps Word (called X-Case) for easy snake case and directory case
[Link to his X-Case Documentation](https://github.com/andrewjrae/kyria-keymap/tree/e3ad77dc4d48b8e6a842c9136c76c1021ab5976b#x-case)
[Link to his X-Case Files](https://github.com/andrewjrae/kyria-keymap/tree/master/features)


# linkers folder
contains raw qmk files for keyboards that are not mergered with qmk master or private qmk repos (that i could not find)
this is needed to compile the firmwares for these boards

| Keyboard             | Keyboard Website                                                  | Firmware Location                                                    | Notes                                                                                                                                                                                                                           |
|----------------------|-------------------------------------------------------------------|----------------------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| rainkeebs/orymoron   | [Oxymoron Website](https://www.cbkbd.com/product/oxymoron-extras) | files found in discord                                               |                                                                                                                                                                                                                                 |
| rainkeebs/orthomoron | [Oxymoron Website](https://www.cbkbd.com/product/oxymoron-extras) | files found in discord                                               |                                                                                                                                                                                                                                 |
| tsquash/willy        | [Willy Website](https://www.squashkb.com/product/gb-willy)        | https://github.com/Tsquash/vial-qmk/tree/free_willy/keyboards/willy  | Personally modified to be up to date with QMK 26 NOV 2022 Update <br /> See here: [QMK Breaking Changes - 2022 November 26 Changelog](https://github.com/qmk/qmk_firmware/blob/master/docs/ChangeLog/20221126.md#data-driven-usb-ids-refactoring-18152-idusb-ids-refactoring)for more info  |
