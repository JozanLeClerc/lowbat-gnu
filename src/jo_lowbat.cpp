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

string
jo_exec(const char* cmd) {
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

string
Lowbat::jo_fetchBatlvl(void) {
	string	batlvl;
	uint8_t batlvlint;

	cout << "Fetching batlvl: ";
	batlvl = Lowbat::jo_exec("acpi | awk '{print $4}' | rev | cut -c 3- | rev");
	batlvl.erase(remove(batlvl.begin(), batlvl.end(), '\n'), batlvl.end());
	batlvlint = stoi(batlvl);
	cout << batlvlint << "%" << endl;
	return (batlvl);
}
