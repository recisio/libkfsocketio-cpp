# LibKfSocketIO socket.io client and Websocket server DLL binding

This project is meant to provide a DLL binding of the socket.io c++ client library with the minimum export.

It also provides a websocket server binding.

This project is made as an internal DLL binding for our own needs, it may or may not be what you're looking for.

⚠️ This project is under development, all the features may not be available yet ⚠️

## Project install

* Boost
    * Download boost http://www.boost.org/
    * Unpack boost into lib/
    * Open a Visual Studio Developer command prompt
    * Run either .\bootstrap.bat (on Windows), or ./bootstrap.sh (on other operating systems) under boost folder.
    * bjam install address-model=32 architecture=x86 --prefix="build" --with-system --with-date_time --with-random --with-regex link=static runtime-link=shared threading=multi
    * Go to the lib output folder (build/lib)
    * lib.exe /OUT:boost.lib *-mt-1_64.lib
    * lib.exe /OUT:boost-dbg.lib *-mt-gd-1_64.lib
* socket.io C++ client
    * Into the main lib folder (<your_libkfsocketio_path>/lib) git clone --recurse-submodules https://github.com/socketio/socket.io-client-cpp.git
    * Go to the the socketio lib path and in websocketpp make sure head is at least at a99cccc17b1dac6c7dfa3f30cd9902f211463bfc
        * If head is before, git checkout HEAD && git pull in the directory
* OpenSSL
    * perl >= 5.10 is required (you can grab it here for instance http://strawberryperl.com/)
    * Into the main lib folder (<your_libkfsocketio_path>/lib) git clone --recurse-submodules https://github.com/openssl/openssl
    * Open a Visual Studio Developer command prompt
    * Go to the openssl folder
    * mkdir build
    * perl Configure VC-WIN32 --prefix=%cd%\build --openssldir=%cd%\build\ssl-common --release no-shared no-asm
    * nmake 
    * nmake install
* Open project in Visual Studio and compile
* Link your project with the DLL and add <your_libkfsocketio_path>/include/ to your project path

## Project configuration

* **KFSIO_THREAD_SAFE** if defined, make internal library calls thread safe
* **NO_VS4290_WARNING** if defined avoid C4290 for throw specification (see [Compiler Warning (level 3) C4290 on MSDN](https://msdn.microsoft.com/en-us/library/sa28fef8.aspx) )

## FAQ

* Why headers located in the include/ directory contain an include guard while those contained in src/ use #pragme once ?
    * The include/ directory is (as advised) meant to be included in external project while the src/ folder is only for internal DLL use. As this project must be compiled with an MSVC C++11 compiler, we can use #pragma once for internal calls, but as we want to maximize the compiler compatibility for included files, they must use the more classic #ifndef/#define include guard
* Can I compile it with <name your favorite compiler> ? Can I compile it for <name your favorite architecture> ?
    * Maybe, I don't know, it's untested. This project is mainly compiled and proved to work for the x86 32bit architecture with the vc141/vc150 compiler. However, if you'd like to see more IDE/compiler/architecture included, and you've been successful at building the project with it, feel free to create a ticket and send your project files + the compilation procedure.
* Dude ! Boost is built with the --with-regex flag while you explicitly use the _WEBSOCKETPP_CPP11_REGEX_ , is it a mistake ?
    * Nope, it's not a mistake, don't ask me, ask the VS linker ;)
* Hi, my name is <your name>, I'd love to use your project, but I don't want to build it, can I find a compiled version of the DLL somewhere ?
    * Yes, <your name>, you'll be able to find the x86 release version DLL with every project release created on Github.
* Hi, my name is <your name>, and I have this idea for this new feature, can you implement it ?
    * Hi again, <your name>, feel free to submit a ticket on Github, however, as stated earlier, this project is mainly built around our internal needs (at least for now), so, please, don't get mad if your idea is not accepted in our development flow. You can still freely fork the project for your own needs, it's MIT-licensed !
    