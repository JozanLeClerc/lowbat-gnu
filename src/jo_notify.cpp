#include <jo_lowbat.hpp>

int
jo_notify(const string batlvl) {
	string		str;

	str = "notify-send \"Low battery: ";
	str += batlvl;
	str += "%\" \"Please plug in computer\" -u critical -t 15000";
	return system(str.c_str());
}

int
jo_speak(const string msg) {
	string		str;

	str = "echo \"";
	str += msg;
	str += "\" | espeak";
	return system(str.c_str());
}
