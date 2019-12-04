#include <jo_lowbat.hpp>
#include <cstring>
#include <thread>
#include <chrono>
#include <algorithm>

using namespace this_thread;
using namespace chrono;

int main(int argc, const char *argv[]) {
	string	msg;
	string	acstat;
	string	batlvl;
	string	arg_one;
	string	arg_two;
	int		batlvlint;

	msg = "beep beep - low battery";
	if (argc > 1) {
		arg_one = argv[1];
		if (argc > 2)
		{
			arg_two = argv[2];
			if (!strcmp(arg_one.c_str(), "--say"))
				msg = arg_two;
		}
	}

	while (true) {
		acstat = jo_exec("acpi | awk '{print $3}' | rev | cut -c 2- | rev");
		batlvl = jo_exec("acpi | awk '{print $4}' | rev | cut -c 3- | rev");
		acstat.erase(remove(acstat.begin(), acstat.end(), '\n'), acstat.end());
		batlvl.erase(remove(batlvl.begin(), batlvl.end(), '\n'), batlvl.end());
		batlvlint = stoi(batlvl);
		if (batlvlint < 90) {
			while (!strcmp(acstat.c_str(), "Discharging")) {
				jo_notify(batlvl);
				if (strcmp(arg_one.c_str(), "--silent"))
					jo_speak(msg);
				sleep_for(seconds(20));
				acstat = jo_exec("acpi | awk '{print $3}' | rev | cut -c 2- | rev");
				batlvl = jo_exec("acpi | awk '{print $4}' | rev | cut -c 3- | rev");
				acstat.erase(remove(acstat.begin(), acstat.end(), '\n'), acstat.end());
				batlvl.erase(remove(batlvl.begin(), batlvl.end(), '\n'), batlvl.end());
			}
		}
		sleep_for(seconds(240));
	}
	delete batlvl;
	delete acstat;
	return 0;
}
