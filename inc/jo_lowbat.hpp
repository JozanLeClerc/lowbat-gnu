#ifndef JO_LOWBAT_HPP
#define JO_LOWBAT_HPP

#include <string>
#include <cstdint>

using namespace std;

class Lowbat {
public:
	uint8_t	jo_testAcpi(void);
	string	jo_exec(const char*);
	string	jo_fetchBatlvl(void);
	int		jo_notify(const string);
	int		jo_speak(const string);

private:
};

int		jo_notify(const string);
int		jo_speak (const string);
string	jo_exec  (const char*);

#endif
