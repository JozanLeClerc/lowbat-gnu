#ifndef JO_LOWBAT_HPP
#define JO_LOWBAT_HPP

#include <string>
#include <cstdint>

using namespace std;

class Lowbat {
public:
	uint8_t			jo_testAcpi(void);
	uint8_t			jo_testNotifySend(void);
	uint8_t			jo_testEspeak(void);
	int				jo_fetchBatlvl(void);
	int				jo_fetchAcstat(void);
	int				jo_notify(void);
	int				jo_speak(void);
	void			jo_setMsg(const char *msg);
	static string	jo_exec(const char*);

private:
	string	m_batlvl;
	string	m_msg;
};

#endif
