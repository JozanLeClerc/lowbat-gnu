#include <jo_lowbat.hpp>

int
jo_notify(const string batlvl) {
	string		str  = nullptr;
	const char	*cmd = nullptr;

	str = "notify-send \"";
	str += batlvl;
	str += "%\" \"Please plug in computer\" -u critical -t 15000";

	cmd = str.c_str();
	return system(cmd);
}

int
jo_speak(const string msg) {
	string		str  = nullptr;
	const char	*cmd = nullptr;

	str = "echo \"";
	str += msg;
	str += "\" | espeak";
	cmd = str.c_str();
	return system(cmd);
}
