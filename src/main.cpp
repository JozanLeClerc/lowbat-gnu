#include <jo_lowbat.hpp>

int main(int argc, const char *argv[]) {
	string			msg       = nullptr;
	string			acstat    = nullptr;
	string			batlvl    = nullptr;
	int				batlvlint = 0;

	if (argc > 1) {
		if (memcmp(argv[1], "--say", strlen(argv[1])))
			msg = "beep beep - low battery";
		else
			msg = argv[2];
	}

	while (true) {
		acstat = jo_exec("acpi | awk '{print $3}' | rev | cut -c 2- | rev");
		batlvl = jo_exec("acpi | awk '{print $4}' | rev | cut -c 3- | rev");
		batlvlint = stoi(batlvl);
		if (batlvlint < 15) {
			while (!memcmp(acstat, "Discharging", strlen(acstat))) {
				jo_notify(batlvl);
				if (memcmp(argv[1], "--silent", strlen(argv[1])))
					jo_speak(msg);
				sleep_for(seconds(20));
				acstat = jo_exec("acpi | awk '{print $3}' | rev | cut -c 2- | rev");
				batlvl = jo_exec("acpi | awk '{print $4}' | rev | cut -c 3- | rev");
				if (!memcmp(acstat, "Charging", strlen(acstat)))
					break ;
			}
		}
		sleep_for(seconds(240));
	}
	return 0;
}
