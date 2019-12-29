#ifndef JO_LOWBAT_HPP
#define JO_LOWBAT_HPP

#include <string>
#include <cstdint>

using namespace std;

class Lowbat {
public:
	uint8_t			jo_testAcpi(void);
	int				jo_fetchBatlvl(void);
	int				jo_notify(void);
	int				jo_speak(const string);
	static string	jo_exec(const char*);

private:
	string	m_batlvl;
};

#endif
