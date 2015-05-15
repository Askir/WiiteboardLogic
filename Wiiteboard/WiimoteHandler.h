#include "wiimote.h"
class WiimoteHandler{

private:
	wiimote *wiimotes[8];
	void on_state_change(wiimote &remote,
		state_change_flags  changed,
		const wiimote_state &new_state);
public:
	void connectFirstWiimote();
	int connectWiimotes();
	void setLEDs(int);
};