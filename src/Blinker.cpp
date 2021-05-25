#include "Arduino.h"
#include <Blinker.h>
#include <elapsedMillis.h>

Blinker :: Blinker(long interval){
	_interval = interval;
	_active = false;
	_finished = false;
	_rose = false;
	_fell = false;
	_newCommand = false;
	_timeout = 0;
};

void Blinker :: start(int timeout){
	if (!_newCommand && !_active){
		_timeout = timeout * _interval * 2;
		_active = true;
		_state = false;
		_newCommand = true;
	}
};

void Blinker :: restart(int timeout){ 
	_timeout = timeout * _interval * 2;
	_runTimer = 0;
}

void Blinker :: stop(){
	if (!_newCommand){	
		_active = false;
		_newCommand = true;
	}
};

void Blinker :: update(){
	
	//Reset new command bit
	_newCommand = false;
	
	//Edge detection for active bit
	if (_active && !_activePrev){
		//Reset timers
		_blinkTimer = 0;
		_runTimer = 0;
	}
	
	//Keep run timer 0 if not active
	if (!_active) _runTimer = 0;
	
	//Stop blinker on timeout
	if (_runTimer > _timeout && _timeout > 0) {
		_active = false;
		_finished = true;
	}
	
	//Blink timer
	if (_blinkTimer >= _interval && (_active || _state)){
		_blinkTimer = 0;
		_state = !_state;
	}
		
	//Rising edge
	_rose = (_state && !_statePrev);
	
	//Falling edge
	_fell =  (_statePrev && !_state);
	
	//Store previous
	_activePrev = _active;
	_statePrev = _state;
}

bool Blinker :: active(){
	return _active;
}

bool Blinker :: finished(){
	if (_finished){
		_finished = false;
		return true;
	} else {
		return false;		
	}
}	

bool Blinker :: tick(){
	return _rose;
}

bool Blinker :: tock(){
	return _fell;
}

bool Blinker :: state(){
	return _state;
}
