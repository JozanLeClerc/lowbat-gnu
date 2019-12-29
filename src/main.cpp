#include <jo_lowbat.hpp>
#include <iostream>
#include <cstring>
#include <thread>
#include <chrono>

using namespace this_thread;
using namespace chrono;

int main(int argc, const char *argv[]) {
	string*	msg;
	string	acstat;
	string	batlvl;
	int		batlvlint;
	(void)argc;
	(void)argv;
	(void)msg;
	(void)batlvl;
	(void)batlvlint;
	(void)acstat;

	Lowbat lowbat;
	if (lowbat.jo_testAcpi())
		return (1);
	while (true) {
		while (lowbat.jo_fetchBatlvl() < 115 && !system("acpi | grep -q Discharging")) {
			lowbat.jo_notify();
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
		}
		cout << "Sleep for 4m" << endl;
		sleep_for(seconds(240));
	}

	return 0;
}
