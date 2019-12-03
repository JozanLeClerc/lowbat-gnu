#ifndef JO_LOWBAT_HPP
#define JO_LOWBAT_HPP

#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <memory>
#include <stdexcept>
#include <array>

using namespace std;
using namespace this_thread;
using namespace chrono;

int		jo_notify(const string);
int		jo_speak (const string);
string	jo_exec  (const char*);

#endif
