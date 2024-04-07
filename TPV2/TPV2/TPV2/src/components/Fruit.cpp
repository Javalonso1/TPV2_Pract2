#include "Fruit.h"
#include "../sdlutils/SDLUtils.h"
#include "ImageWithFrames.h"


const int MAX_TIEMPO_ESPERA = 21;
const int MIN_TIEMPO_ESPERA = 10;
const int MAX_TIEMPO_ACTIVA = 6;
const int MIN_TIEMPO_ACTIVA = 1;
const int PROB_EMPEZAR_ACTIVA = 10;

const int CUANTO_ES_UN_SEGUNDO = 1000;

Fruit::Fruit(ImageWithFrames* im):im_(im) {
	auto& rand_ = sdlutils().rand();
	N = rand_.nextInt(MIN_TIEMPO_ESPERA, MAX_TIEMPO_ESPERA);
	M = rand_.nextInt(MIN_TIEMPO_ACTIVA, MAX_TIEMPO_ACTIVA);
	int x = rand_.nextInt(0, PROB_EMPEZAR_ACTIVA);
	if (x == 0) milagroso = true;
	else milagroso = false;
	activada = false;
	timeToChange = sdlutils().currRealTime();
}
Fruit::~Fruit(){
}
void Fruit::initComponent() {
}
void Fruit::update(){	
	auto currTime = sdlutils().currRealTime();
	if (milagroso) {
		if (activada) {
			if (currTime > timeToChange + (M * CUANTO_ES_UN_SEGUNDO)) {
				DisActivate();
				timeToChange = currTime;
			}
		}
		else {
			if (currTime > timeToChange + (N * CUANTO_ES_UN_SEGUNDO)) {
				Activate();
				timeToChange = currTime;
			}
		}
	}
}
void Fruit::Activate() {	
	activada = true;	
	im_->changeFrame(1, 7);
}
void Fruit::DisActivate() {	
	activada = false;
	im_->changeFrame(1, 4);
}
void Fruit::resetTimer() {
	timeToChange = sdlutils().currRealTime();
}