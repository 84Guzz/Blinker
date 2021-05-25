#ifndef Blinker_h
#define Blinker_h

#include "Arduino.h"
#include <elapsedMillis.h>

class Blinker{
	
	public:
		Blinker(long interval);
		void start(int timeout);
		void restart (int timeout);
		void stop();
		void update();
		bool active();
		bool finished();
		bool tick();
		bool tock();
		bool state();
	private:
		bool _active, _activePrev, _finished, _newCommand;
		bool _state, _statePrev;
		bool _rose, _fell;
		long _interval, _timeout;
		elapsedMillis _blinkTimer, _runTimer;
};

#endif
