#include "ImmunitySystem.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"

const int TIME_INMUNE = 10000;

ImmunitySystem::ImmunitySystem() :
	inmune(false) {
}

ImmunitySystem::~ImmunitySystem() {
}

void ImmunitySystem::initSystem() {	
}
void ImmunitySystem::update() {	
	if (inmune) {
		auto currTime = sdlutils().currRealTime();
		if (currTime > timeWithInmunity + TIME_INMUNE) {
			inmune = false;
			Message m;
			m.id = _IMMUNITY_END;
			mngr_->send(m);
		}
	}

}
void ImmunitySystem::timerInmunity() {
	if (!inmune) {
		inmune = true;
		timeWithInmunity = sdlutils().currRealTime();
	}
}

void ImmunitySystem::recieve(const Message& m) {
	switch (m.id) {
	case _PACMAN_FOOD_COLLISION:
		if (m.fruit_data.activada) {
			Message m2;
			m2.id = _IMMUNITY_START;
			mngr_->send(m2);
			timerInmunity();
		}
		break;
	default:
		break;
	}
}