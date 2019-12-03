#ifndef JO_LOWBAT_HPP
#define JO_LOWBAT_HPP

#include <iostream>
#include <cstring>
#include <string>
#include <stream>
#include <thread>
#include <chrono>
#include <memory>
#include <stdexcept>
#include <array>

using namespace std;
using namespace this_thread;
using namespace chrono;

void	jo_notify(const string);
void	jo_speak (const string);
string	jo_exec  (const char*);

#endif
