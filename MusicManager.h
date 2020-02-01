#pragma once
#include <pa/portaudio.h>

// this is currently unused anywhere 
// deleting it will not impact anything
class MusicManager
{
public:
	// constructor
	MusicManager();

	// callback function may be used as an ISR
	int generateMusic( const void* input,
						void* outputBuffer, 
						unsigned long framesPerBuffer,
						const PaStreamCallbackTimeInfo* timeInfo, 
						PaStreamCallbackFlags statusFlags, 
						void* userData 
	);




};

