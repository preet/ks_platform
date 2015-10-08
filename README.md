### What is ks?
ks is a small cross platform c++ library that can be used to help create applications and libraries.

### What is ks_platform?
The platform module abstracts platform specific functionality through other libraries.

### License
This module is licensed under the Apache License, version 2.0. For more information see the LICENSE file.

### Dependencies

* [**SDL2**](https://www.libsdl.org/) (zlib license)

### Building
The provided pri file can be added to a qmake project. Ensure the dependent ks modules are included in any project that uses this module.

Currently ks_platform requires SDL2 (the latest nightly build; 2.0.3 is too old) to be built for the target platform. The ks_platform.pri file expects the following variables to be defined, specifying the location of the SDL libs:

PATH_SDL_LIB

PATH_SDL_INCLUDE

### Documentation
TODO
