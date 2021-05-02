# Server and client for Agar.io game

![CI status](https://github.com/dziulek/AgarioServer/actions/workflows/build.yml/badge.svg)
![CI status](https://github.com/dziulek/AgarioServer/actions/workflows/server_tests.yml/badge.svg)
---

## Overview
Project includes:
* simple C++ server
* python client

The aim of the project was to write multithreaded server using BSD sockets in C/C++. Server uses my own engine for this purpose (you can find it [here](https://github.com/dziulek/AgarioEngine)) and [json library](https://github.com/nlohmann/json) for modern C++.

![](AgarioServerDemo.gif)

## Setup 
To build the project clone repository with all submodules (`recurse-submodules` option). 
Go to main directory of the project, to build server:
```
$ mkdir build
$ cd build/
$ cmake ..
$ make
$ ./AgarioServer_run
```
To run client:
```
$ cd src/pythonClient/
$ python agario.py <ip address> <port number>
```
You should replace `<ip address>` with your ip, and `<port number>` with outcome of  <img src="https://latex.codecogs.com/png.image?\dpi{110}&space;\bg_white&space;floor&space;\left&space;[&space;\int_{2}^{3}\frac{e^{3x}}{2.017}sin(\frac{x}{2})dx&space;\right&space;]&space;&space;" title="\bg_white floor \left [ \int_{2}^{3}\frac{e^{3x}}{2.017}sin(\frac{x}{2})dx \right ] " />
