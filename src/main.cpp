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
	int		batlvlint;

	if (system("acpi > /dev/null 2>&1")) {
		cout << "acpi is not installed. Please install it in order to run lowbat." << endl;
		return 1;
	}
	while (true) {
		cout << "Fetching batlvl: ";
		batlvl = jo_exec("acpi | awk '{print $4}' | rev | cut -c 3- | rev");
		batlvl.erase(remove(batlvl.begin(), batlvl.end(), '\n'), batlvl.end());
		batlvlint = stoi(batlvl);
		cout << batlvlint << "%" << endl;
		while (batlvlint < 25 && !system("acpi | grep -q Discharging")) {
			jo_notify(batlvl);
			if (argc > 1 && strcmp(argv[1], "--silent")) {
				if (argc > 2 && !strcmp(argv[1], "--say")) {
					msg = new string(argv[2]);
				}
				else {
					msg = new string("beep beep - low battery");
				}
				jo_speak(*msg);
				delete msg;
			}
			cout << "Sleep for 20s" << endl;
			sleep_for(seconds(20));
			batlvl.clear();
			batlvl = jo_exec("acpi | awk '{print $4}' | rev | cut -c 3- | rev");
			batlvl.erase(remove(batlvl.begin(), batlvl.end(), '\n'), batlvl.end());
		}
		cout << "Sleep for 4m" << endl;
		sleep_for(seconds(240));
	}

	return 0;
}
