#ifndef THREAD_FUNCTIONS_HPP
#define THREAD_FUNCTIONS_HPP

#include "server.hpp"
#include "client.hpp"
#include <iostream>
#include <chrono>

#include "jsonSendFormat.hpp"

void * clientThread(void * server_client);

void * gameThread(void * srv);

void * serverInfoRoutine(void * args);

std::string addHeader(std::string s, int header_len=10);

#endif