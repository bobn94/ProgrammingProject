//GlobalConfig.cpp

#include "GlobalConfig.h"

struct GlobalConfigVariables {
	int musicVolume;
}GlobalConfig;

int getMusicVolume(){
	return GlobalConfig.musicVolume;
}

void setMusicVolume(int vol) {
	GlobalConfig.musicVolume = vol;
}