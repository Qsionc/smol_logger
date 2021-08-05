# `smol::logger` - logging made terrible

This small static library provides type-safe and thread-safe logging capability using `std::ostream` based message
sinks.

---

## Table of contents

1. [Supported Platforms](#supported-platforms)
2. [Requirements](#requirements)
3. [Information](#information)
4. [Motivation](#motivation)
5. [Installation](#installation)
6. [Example usage](#example-usage)
7. [Conclusion](#conclusion)

## Supported Platforms

Currently, only linux is supported. I plan adding Windows support once i learn how to use CMake properly on Windows.<br>

## Information

The implemented logger creates independent thread to fetch messages and push them to bound sinks.<br>
Please, <b>consider this in your multi-thread applications</b> as this will reduce number of available threads by one,
moment instance of logger is created.

Logger itself is not a singleton, but it uses `smol::singleton` internally to store references to `smol::logger_queue` 
and `smol::logger_reader`. So, it is <b>required</b> to be wrapped in `smol::singleton` for safety:
```c++
smol::singleton<smol::logger> logger;
logger.init();
// ... some work ...
logger.destroy();
```
Calling `smol::singleton::init` is safe and can be called in any thread any number of times, since it controls 
if the target was already initiated. To create fresh instance, you need to call `smol::singleton::destroy` first. <br>

This way you can control lifetime of "Singleton". Note, that in case of logger it is wise to init it once and destroy it 
once, so logger is present throughout whole duration of your program. 

## Requirements

This library requires for [smol::singleton](https://github.com/Qsionc/smol_singleton)
and [smol::format](https://github.com/Qsionc/smol_format) to be installed, as the library uses both.<br>
Those are header-only libraries created by yours truly.

## Motivation

This small library is part of my C++ learning journey, to become proper C++ game developer. This is part of my future
smol-engine project, custom OpenGL Engine I plan to create in order to learn more about gamedev.<br>
`smol-repositories` are collection of things I plan to use during smol::engine development.

## Installation

After cloning or after downloading and extracting `.zip` file, create additional `build` directory.

```shell
mkdir build
cd build
```

Once inside call cmake to configure project to allow building and installation of static smogger library, `libsmogger.a`
. In order to not pollute your system libraries, I recommend installing the library in safe location, like `~/.local`
directory, in your home directory.

```shell
cmake .. -DCMAKE_INSTALL_PREFIX:STRING="${HOME}/.local" -DCMAKE_BUILD_TYPE:STRING="Release"
cmake --build . --target install
```

Unit Tests are implemented using Google Test framework. If you want to run tests, you need to configure your project in
Debug mode.<br>
I recommend creating two different folders, for debug and release configuration, and
calling `cmake --build . --target install` only on `Release`
configuration, due to optimisation flags passed to compiler.

If you want, you can tweak files in `cmake` directory to your needs.

## Example usage

Once library is installed, pass `CMAKE_PREFIX_PATH` to your project pointing to custom install location, if any, and
use `find_package` to add library to your project. It is worth noting, that this library requires header libraries
created by me, to be installed (links are provided in [Requirements](#requirements) section). If the libraries are
installed, `smogger` will find those and link them automatically to your project. 

```cmake
find_package( smogger REQUIRED ) # yes - the library is called smogger
# ...
add_executable(some_program some_source.cpp)
target_link_libraries(some_program PRIVATE smogger::smogger) # links singleton::singleton and smormat::smormat
```

All it takes now is to use it:

```c++
#include <iostream>
#include <smogger/smogger.h>

using Logger = smol::singleton<smol::logger>;

int main() {
    Logger logger;
    logger.init() // For reference, how does smol::singleton work, refer to the repository, links above
    logger->bind_sink("std::cout", std::cout); // You can bind any class derived from std::ostream as sinks.
    // String is unique Key given to sink to store it, for later easier call to smol::logger::unbind_sink.
    smol::jthread thread([](Logger logger) {
        logger->info("some important data: {}", 42); // look into smol::format to know more about type-safe formatting
    }, logger); // smol::jthread is small class around std::thread that ensures automatic joining of thread, does not support detach
    
    logger.destroy();
    return 0;
}
```

---

# Conclusion

`smol::logger` made terrible is simple logging library which will be part of `smol::engine` in the future. All of this
is made to practice C++/CMake and learn OpenGL/Vulkan.

I do not claim to be good programmer, so any insight and constructive criticism is appreciated!