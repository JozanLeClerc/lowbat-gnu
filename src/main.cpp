#include <jo_lowbat.hpp>

int main(int argc, const char *argv[]) {
	string			msg;
	string			acstat;
	string			batlvl;
	int				batlvlint = 0;
	int val1;
	int val2;

	acstat = jo_exec("acpi | awk '{print $3}' | rev | cut -c 2- | rev");
	val1 = strlen(acstat.c_str());
	val2 = strlen("Discharging");
	msg = "beep beep - low battery";
	if (argc > 1) {
		if (!memcmp(argv[1], "--say", strlen(argv[1]))) {
			msg = argv[2];
		}
	}

	while (true) {
		acstat = jo_exec("acpi | awk '{print $3}' | rev | cut -c 2- | rev");
		batlvl = jo_exec("acpi | awk '{print $4}' | rev | cut -c 3- | rev");
		batlvlint = stoi(batlvl);
		if (batlvlint < 90) {
			while (!memcmp(acstat.c_str(), "Discharging", strlen(acstat.c_str()))) {
				jo_notify(batlvl);
				if (memcmp(argv[1], "--silent", strlen(argv[1])))
					jo_speak(msg);
				sleep_for(seconds(20));
				acstat = jo_exec("acpi | awk '{print $3}' | rev | cut -c 2- | rev");
				batlvl = jo_exec("acpi | awk '{print $4}' | rev | cut -c 3- | rev");
				if (!memcmp(acstat.c_str(), "Charging", strlen(acstat.c_str())))
					break ;
			}
		}
		sleep_for(seconds(240));
	}
	return 0;
}
