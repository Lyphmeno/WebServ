WebServ Project :
=================

Welcome to the WebServ project !

This project involves creating an HTTP server in C++98 with various features and functionalities.

Project Requirements
--------------------

* Implement an HTTP server in C++98.
* Server must never block or hang forever on a request.
* Use only one \`poll()\` (or equivalent) for all I/O operations.
* Support HTTP 1.1 standards and behavior.
* Serve static websites and handle file uploads.
* Execute CGI scripts based on file extensions (only one needed).
* Support multiple ports for listening.

Getting Started
---------------

1.  **Configure server settings via a configuration file :**
    * I made it similar to nginx rules to make it easier to use
    * Don't forget to setup default values that you can explain
    * The parsing is long so do it properly
2.  **Setup the server :**
    * We used Epoll here
    * Binding to the same address right after shutting it down won't work so change the address
3.  **HTML request :**
    * This is the biggest part, a lot of parsing and html coding
    * Default error pages must not be forgotten
    * Support GET, POST, and DELETE methods.

Resources
---------

* C++98 Documentation in legacy : https://legacy.cplusplus.com/
* HTTP 1.1 Specification : https://datatracker.ietf.org/doc/html/rfc2616
* NGINX Documentation for configuration files : http://nginx.org/en/docs/beginners_guide.html
