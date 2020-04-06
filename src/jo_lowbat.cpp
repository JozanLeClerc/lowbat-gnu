#include <jo_lowbat.hpp>
#include <iostream>
#include <fstream>
#include <cstring>
#include <array>
#include <memory>
#include <algorithm>

using namespace std;

uint8_t
Lowbat::jo_testNotifySend(void) {
	if (system("type notify-send > /dev/null 2>&1")) {
		cerr << "notify-send is not installed. Please install it in order to run lowbat" << endl;
		return (1);
	}
	cout << "notify-send is installed" << endl;
	return (0);
}

uint8_t
Lowbat::jo_testEspeak(void) {
	if (system("type espeak > /dev/null 2>&1")) {
		cerr << "espeak is not installed. Please install it in order to run --say option" << endl;
		return (1);
	}
	cout << "espeak is installed" << endl;
	return (0);
}

int
Lowbat::jo_fetchBatlvl(void) {
	ifstream	bat;

	cout << "Fetching batlvl: ";
	bat.open("/sys/class/power_supply/BAT0/capacity");
	if (!bat.is_open()) {
		cerr << "Failed to open battery info file" << endl;
		exit(JO_RET_OPEN_FAILED);
	}
	getline(bat, m_batlvl);
	bat.close();
	cout << m_batlvl << endl;
	m_batlvl.erase(remove(m_batlvl.begin(), m_batlvl.end(), '\n'), m_batlvl.end());
	cout << m_batlvl << "%" << endl;
	return (stoi(m_batlvl));
}

uint8_t
Lowbat::jo_fetchAcstat(void) {
	ifstream	stat;
	string		l;
	uint8_t		ret;

	cout << "Fetching acstat: ";
	stat.open("/sys/class/power_supply/BAT0/status");
	if (!stat.is_open()) {
		cerr << "Failed to open battery info file" << endl;
		exit(JO_RET_OPEN_FAILED);
	}
	getline(stat, l);
	cout << l << endl;
	if (!strcmp("Discharging", l.c_str())) {
		ret = 0;
	}
	else {
		ret = 1;
	}
	stat.close();
	return (ret);
}

int
Lowbat::jo_notify(void) {
	string		str;

	str = "notify-send \"Low battery: ";
	str += m_batlvl;
	str += "%\" \"Please plug in computer\" -u critical -t 15000";
	cout << "Notifying" << endl;
	return (system(str.c_str()));
}

int
Lowbat::jo_speak(void) {
	string		str;

	str = "echo \"";
	str += m_msg->c_str();
	str += "\" | espeak";
	cout << "Speaking: " << m_msg->c_str() << endl;
	return (system(str.c_str()));
}

void
Lowbat::jo_setMsg(const char *msg) {
	m_msg = new string(msg);
}

void
Lowbat::jo_delMsg(void) {
	delete m_msg;
}
