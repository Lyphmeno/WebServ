<!DOCTYPE html>
<html>
<body>
  <h1>WebServ Project : <a href="https://github.com/JaeSeoKim/badge42"><img src="https://badge42.vercel.app/api/v2/cljbd5ceo007308mltneinai5/project/2956659" alt="hlevi's 42 webserv Score" /></a></h1>
  <p>Welcome to the WebServ project !</p>
  <p>This project involves creating an HTTP server in C++98 with various features and functionalities.</p>
    
  <h2>Project Requirements</h2>
  <ul>
    <li>Implement an HTTP server in C++98.</li>
    <li>Server must never block or hang forever on a request.</li>
    <li>Use only one `poll()` (or equivalent) for all I/O operations.</li>
    <li>Support HTTP 1.1 standards and behavior.</li>
    <li>Serve static websites and handle file uploads.</li>
    <li>Execute CGI scripts based on file extensions (only one needed).</li>
    <li>Support multiple ports for listening.</li>
  </ul>

  <h2>Getting Started</h2>
  <ol>
    <li>
      <strong>Configure server settings via a configuration file :</strong>
        <ul>
        <li>I made it similar to nginx rules to make it easier to use</li>
        <li>Don't forget to setup default values that you can explain</li>
        <li>The parsing is long so do it properly</li>
        </ul>
    </li>
    <li>
      <strong>Setup the server :</strong>
        <ul>
        <li>We used Epoll here</li>
        <li>Binding to the same address right after shutting it down won't work so change the address</li>
        </ul>
    </li>
    <li>
      <strong>HTML request :</strong>
        <ul>
        <li>This is the biggest part, a lot of parsing and html coding</li></li>
        <li>Default error pages must not be forgotten</li>
        <li>Support GET, POST, and DELETE methods.</li>
        </ul>
    </li>
  </ol>

  <h2>Resources</h2>
  <ul>
    <li>C++98 Documentation in legacy : https://legacy.cplusplus.com/</li>
    <li>HTTP 1.1 Specification : https://datatracker.ietf.org/doc/html/rfc2616</li>
    <li>NGINX Documentation for configuration files : http://nginx.org/en/docs/beginners_guide.html</li>
  </ul>
</body>
</html>
