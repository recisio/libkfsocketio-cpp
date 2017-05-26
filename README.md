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
