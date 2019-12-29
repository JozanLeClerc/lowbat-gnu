#include <jo_lowbat.hpp>
#include <iostream>
#include <array>
#include <memory>
#include <algorithm>

using namespace std;

uint8_t
Lowbat::jo_testAcpi(void) {
	if (system("acpi > /dev/null 2>&1")) {
		cout << "acpi is not installed. Please install it in order to run lowbat." << endl;
		return 1;
	}
	return 0;
}

int
Lowbat::jo_fetchBatlvl(void) {
	cout << "Fetching batlvl: ";
	m_batlvl = Lowbat::jo_exec("acpi | awk '{print $4}' | rev | cut -c 3- | rev");
	m_batlvl.erase(remove(m_batlvl.begin(), m_batlvl.end(), '\n'), m_batlvl.end());
	cout << m_batlvl << "%" << endl;
	return(stoi(m_batlvl));
}

string
Lowbat::jo_exec(const char* cmd) {
    array<char, 128> buffer;
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

int
Lowbat::jo_notify(void) {
	string		str;

	str = "notify-send \"Low battery: ";
	str += m_batlvl;
	str += "%\" \"Please plug in computer\" -u critical -t 15000";
	cout << "Notifying" << endl;
	return system(str.c_str());
}
