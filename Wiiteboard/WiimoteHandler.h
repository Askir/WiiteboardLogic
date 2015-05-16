#include "wiimote.h"
#include <vector>
class WiimoteHandler{

private:
	std::vector<wiimote*> wiimotes;
	void on_state_change(wiimote &remote,
		state_change_flags  changed,
		const wiimote_state &new_state);
public:
	void connectFirstWiimote();
	int connectWiimotes();
	void setLEDs(int);
	void disconnectWiimotes();
	bool getIRData(unsigned, unsigned, float*);
	void refreshWiimotes();
};