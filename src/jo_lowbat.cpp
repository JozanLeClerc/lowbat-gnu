#include <jo_lowbat.hpp>
#include <iostream>

using namespace std;

uint8_t
Lowbat::jo_testAcpi(void) {
	if (system("acpi > /dev/null 2>&1")) {
		cout << "acpi is not installed. Please install it in order to run lowbat." << endl;
		return 1;
	}
	return 0;
}
