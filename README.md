# Sanity Cpp library
## Building and installing
* Make sure you have the `curl` development files and the [nlohmann/json](https://github.com/nlohmann/json) library installed
* Create a `build/` directory and `cd` into it
* Run `cmake ..` to generate the makefile(s). You can disable building tests by disabling `DBUILD_TESTS`.
* Run `make -j8` to build the library
* Run `sudo make install`

## Documentation
Use [Doxygen](http://www.doxygen.nl/index.html) to generate the documentation. A default config file is provided (`.doxygen`)

## Changelog
[Changelog](https://changelogfy.com/sanity-cpp/announcements)