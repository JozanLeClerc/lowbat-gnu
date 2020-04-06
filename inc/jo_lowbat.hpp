#ifndef JO_LOWBAT_HPP
#define JO_LOWBAT_HPP

#include <string>
#include <cstdint>

using namespace std;

enum retvals {
	JO_RET_FINE,
	JO_RET_MISS_DEP,
	JO_RET_OPEN_FAILED,
	JO_RET_NOTIFY_FAILED
};

class Lowbat {
public:
	uint8_t			jo_testNotifySend(void);
	uint8_t			jo_testEspeak(void);
	int				jo_fetchBatlvl(void);
	uint8_t			jo_fetchAcstat(void);
	int				jo_notify(void);
	int				jo_speak(void);
	void			jo_setMsg(const char *);
	void			jo_delMsg(void);

private:
	string	m_batlvl;
	string	*m_msg;
};

#endif
