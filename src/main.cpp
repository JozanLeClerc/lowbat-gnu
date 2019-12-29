#include <jo_lowbat.hpp>
#include <iostream>
#include <cstring>
#include <cstdint>
#include <thread>
#include <chrono>

using namespace this_thread;
using namespace chrono;

int main(int argc, const char *argv[]) {
	Lowbat	lowbat;
	uint8_t	speaks;

	speaks = 0;
	if (lowbat.jo_testAcpi()) {
		return 1;
	}
	if (lowbat.jo_testNotifySend()) {
		return 2;
	}
	if (argc > 2 && !strcmp(argv[1], "--say")) {
		if (!lowbat.jo_testEspeak()) {
			lowbat.jo_setMsg(argv[2]);
			speaks = 1;
		}
	}
	while (true) {
		while (lowbat.jo_fetchBatlvl() < 15 && !lowbat.jo_fetchAcstat()) {
			if (lowbat.jo_notify()) {
				cout << "Error: could not use notify-send" << endl;
				return 3;
			}
			if (speaks && lowbat.jo_speak()) {
				cout << "Error: could not use espeak" << endl;
			}
			cout << "Sleep for 20s" << endl;
			sleep_for(seconds(20));
		}
		cout << "Sleep for 4m" << endl;
		sleep_for(seconds(240));
	}
	return 0;
}
