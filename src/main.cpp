#include <jo_lowbat.hpp>
#include <iostream>
#include <cstring>
#include <thread>
#include <chrono>
#include <algorithm>

using namespace this_thread;
using namespace chrono;

int main(int argc, const char *argv[]) {
	string*	msg;
	string	acstat;
	string	batlvl;
	string	arg_one;
	string	arg_two;
	int		batlvlint;

	if (system("acpi > /dev/null 2>&1")) {
		cout << "acpi is not installed. Please install it in order to run lowbat." << endl;
		return 1;
	}
	if (argc > 1) {
		arg_one = argv[1];
	}
	while (true) {
		acstat = jo_exec("acpi | awk '{print $3}' | rev | cut -c 2- | rev");
		batlvl = jo_exec("acpi | awk '{print $4}' | rev | cut -c 3- | rev");
		acstat.erase(remove(acstat.begin(), acstat.end(), '\n'), acstat.end());
		batlvl.erase(remove(batlvl.begin(), batlvl.end(), '\n'), batlvl.end());
		batlvlint = stoi(batlvl);
		if (batlvlint < 15) {
			while (!strcmp(acstat.c_str(), "Discharging")) {
				jo_notify(batlvl);
				if (strcmp(arg_one.c_str(), "--silent")) {
					if (argc > 2 && !strcmp(arg_one.c_str(), "--say")) {
						arg_two = argv[2];
						msg = new string(arg_two);
					}
					else {
						msg = new string("beep beep - low battery");
					}
					jo_speak(*msg);
					delete msg;
				}
				sleep_for(seconds(20));
				acstat.clear();
				batlvl.clear();
				acstat = jo_exec("acpi | awk '{print $3}' | rev | cut -c 2- | rev");
				batlvl = jo_exec("acpi | awk '{print $4}' | rev | cut -c 3- | rev");
				acstat.erase(remove(acstat.begin(), acstat.end(), '\n'), acstat.end());
				batlvl.erase(remove(batlvl.begin(), batlvl.end(), '\n'), batlvl.end());
			}
		}
		sleep_for(seconds(240));
	}

	return 0;
}
