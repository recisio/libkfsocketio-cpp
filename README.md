# LibKfSocketIO socket.io client and Websocket server DLL binding

This project is meant to provide a DLL binding of the socket.io c++ client library with the minimum export.

It also provides a websocket server binding.

This project is made as an internal DLL binding for our own needs, it may or may not be what you're looking for.

⚠️ This project is under development, all the features may not be available yet ⚠️

## Project install

* OpenSSL
    * Install OpenSSL in C:\OpenSSL-Win64 for x64 and C:\OpenSSL-Win32 for x86
* socket.io C++ client
    * cd libkfsocketio-cpp/lib/socket.io-client-cpp11-non-boost
    * git submodule init
    * git submodule update
    * open cmake-gui on libkfsocketio-cpp/lib/socket.io-client-cpp11-non-boost folder and generate msvc solution for each architecture (in build/x64 & build/x86)
    * open msvc generated solutions and compile
* Open project in Visual Studio and compile
* Link your project with the DLL and add <your_libkfsocketio_path>/include/ to your project path

## TLS with websocket++

If the fix for [websocketpp#599](https://github.com/zaphoyd/websocketpp/issues/599) is not yet in the master branch, apply this patch to enable TLS for websockets :

```
--- websocketpp-0.7.0.orig/websocketpp/transport/asio/security/tls.hpp
+++ websocketpp-0.7.0/websocketpp/transport/asio/security/tls.hpp
@@ -355,8 +355,13 @@ protected:
     template <typename ErrorCodeType>
     lib::error_code translate_ec(ErrorCodeType ec) {
         if (ec.category() == lib::asio::error::get_ssl_category()) {
+#if defined SSL_R_SHORT_READ
             if (ERR_GET_REASON(ec.value()) == SSL_R_SHORT_READ) {
                 return make_error_code(transport::error::tls_short_read);
+#else
+            if (ERR_GET_REASON(ec.value()) == boost::asio::ssl::error::stream_truncated) {
+                return make_error_code(transport::error::tls_short_read);
+#endif
```

## Read access violation in websocketpp

If you happen to have an access violation when a new connection is made on a WebSocket Server, apply this patch in websocketpp/transport/asio/security/none.hpp :
* include \<functional>
* Change socket_init_handler type from lib::function to std::function 

## FAQ

* Why headers located in the include/ directory contain an include guard while those contained in src/ use #pragme once ?
    * The include/ directory is (as advised) meant to be included in external project while the src/ folder is only for internal DLL use. As this project must be compiled with an MSVC C++11 compiler, we can use #pragma once for internal calls, but as we want to maximize the compiler compatibility for included files, they must use the more classic #ifndef/#define include guard
* Can I compile it with \<name your favorite compiler> ? Can I compile it for \<name your favorite architecture> ?
    * Maybe, I don't know, it's untested. This project is mainly compiled and proved to work for the x86 32bit architecture with the vc141/vc150 compiler. However, if you'd like to see more IDE/compiler/architecture included, and you've been successful at building the project with it, feel free to create a ticket and send your project files + the compilation procedure.
* Dude ! Boost is built with the --with-regex flag while you explicitly use the _WEBSOCKETPP_CPP11_REGEX_ , is it a mistake ?
    * Nope, it's not a mistake, don't ask me, ask the VS linker ;)
* Hi, my name is \<your name>, I'd love to use your project, but I don't want to build it, can I find a compiled version of the DLL somewhere ?
    * Yes, \<your name>, you'll be able to find the x86 release version DLL with every project release created on Github.
* Hi, my name is \<your name>, and I have this idea for this new feature, can you implement it ?
    * Hi again, \<your name>, feel free to submit a ticket on Github, however, as stated earlier, this project is mainly built around our internal needs (at least for now), so, please, don't get mad if your idea is not accepted in our development flow. You can still freely fork the project for your own needs, it's MIT-licensed !
    
