# LibKfSocketIO socket.io client and Websocket server DLL binding

This project is meant to provide a DLL binding of the socket.io c++ client library with the minimum export.

It also provides a websocket server binding.

This project is made as an internal DLL binding for our own needs, it may or may not be what you're looking for.

## Project install

* Download boost http://www.boost.org/
* Unpack boost into lib/
* Open a Visual Studio Developer command prompt
* Run either .\bootstrap.bat (on Windows), or ./bootstrap.sh (on other operating systems) under boost folder.
* bjam install address-model=32 architecture=x86 --prefix="build" --with-system --with-date_time --with-random link=static runtime-link=shared threading=multi
* Go to the lib output folder (build/lib)
* lib.exe /OUT:boost.lib *
* Go to the main lib folder
* git clone --recurse-submodules https://github.com/socketio/socket.io-client-cpp.git
* Open project in Visual Studio and compile

## Project configuration

* KFSIO_THREAD_SAFE if defined, make internal library calls thread safe