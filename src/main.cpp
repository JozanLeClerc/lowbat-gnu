#include <jo_lowbat.hpp>
#include <algorithm>

int main(int argc, const char *argv[]) {
	string			msg;
	string			acstat;
	string			batlvl;
	int				batlvlint;

	if (argc > 1 && !memcmp(argv[1], "--say", strlen(argv[1])))
		msg = argv[2];

	while (true) {
		acstat = jo_exec("acpi | awk '{print $3}' | rev | cut -c 2- | rev");
		batlvl = jo_exec("acpi | awk '{print $4}' | rev | cut -c 3- | rev");
		acstat.erase(remove(acstat.begin(), acstat.end(), '\n'), acstat.end());
		batlvl.erase(remove(batlvl.begin(), batlvl.end(), '\n'), batlvl.end());
		batlvlint = stoi(batlvl);
		if (batlvlint < 90) {
			while (!memcmp(acstat.c_str(), "Discharging", strlen(acstat.c_str()))) {
				jo_notify(batlvl);
				if (memcmp(argv[1], "--silent", strlen(argv[1])))
					jo_speak(msg);
				sleep_for(seconds(20));
				acstat = jo_exec("acpi | awk '{print $3}' | rev | cut -c 2- | rev");
				batlvl = jo_exec("acpi | awk '{print $4}' | rev | cut -c 3- | rev");
				acstat.erase(remove(acstat.begin(), acstat.end(), '\n'), acstat.end());
				batlvl.erase(remove(batlvl.begin(), batlvl.end(), '\n'), batlvl.end());
				if (!memcmp(acstat.c_str(), "Charging", strlen(acstat.c_str())))
					break ;
			}
		}
		sleep_for(seconds(240));
	}
	return 0;
}
