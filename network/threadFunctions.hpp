#ifndef THREAD_FUNCTIONS_HPP
#define THREAD_FUNCTIONS_HPP

#include "server.hpp"
#include "client.hpp"
#include <iostream>
#include <chrono>

void * clientThread(void * server_client);

void * gameThread(void * srv);

#endif