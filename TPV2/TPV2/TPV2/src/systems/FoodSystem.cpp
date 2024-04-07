#include "FoodSystem.h"

#include "../components/ImageWithFrames.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../components/Fruit.h"
#include "../components/Health.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/Game.h"

const int NUM_FRUTAS_X = 8;
const int NUM_FRUTAS_Y = 6;

FoodSystem::FoodSystem() : numFruts(0){
}

FoodSystem::~FoodSystem() {
}

void FoodSystem::initSystem() {

}
void FoodSystem::resetFruit() {
	numFruts = 0;
	auto fruits = mngr_->getEntities(ecs::grp::FRUIT);
	for (int i = 0; i < fruits.size(); i++) {
		removeFruit(fruits[i]);
	}
	createFruits();
}
void FoodSystem::resetFruitTimers() {

	auto fruits = mngr_->getEntities(ecs::grp::FRUIT);
	for (int i = 0; i < fruits.size(); i++) {
		mngr_->getComponent<Fruit>(fruits[i])->resetTimer();
	}	
}
void FoodSystem::createFruits() {	
	int s = 40;
	int distX = sdlutils().width()/(NUM_FRUTAS_X);
	int x_ = (distX / 2)-(s/2);
	int distY = sdlutils().height() / (NUM_FRUTAS_Y);
	int y_;

	for (int i = 0; i < NUM_FRUTAS_X; i++) {
		y_ = (distY / 2)-(s/2);
		for (int j = 0; j < NUM_FRUTAS_Y; j++) {
			auto fruit = mngr_->addEntity(ecs::grp::FRUIT);
			auto fTR_ = mngr_->addComponent<Transform>(fruit);
			fTR_->init(Vector2D(x_, y_), Vector2D(), s, s, 0.0f);
			auto imag = mngr_->addComponent<ImageWithFrames>(fruit, &sdlutils().images().at("pacman"),
				8, 8,
				0, 0,
				128, 128,
				1, 4,
				1, 1);
			mngr_->addComponent<Fruit>(fruit, imag);

			numFruts++;
			y_ += distY;
		}
		x_ += distX;
	}
}
void FoodSystem::removeFruit(ecs::entity_t e) {
	mngr_->setAlive(e, false);	
	numFruts--;
}
void FoodSystem::recieve(const Message& m)
{	
	switch (m.id) {
	case _NEW_GAME:
		resetFruit();
		break;
	case _ROUND_OVER:
		resetFruitTimers();
		break;
	case _PACMAN_FOOD_COLLISION:
		removeFruit(m.fruit_data.e);
		break;
	default:
		break;
	}
}

void FoodSystem::update() {
	auto& rand_ = sdlutils().rand();

	auto currTime = sdlutils().currRealTime();
	auto frutes = mngr_->getEntities(ecs::grp::FRUIT);
	auto n = frutes.size();

	for (auto i = 0u; i < n; i++) {
		auto fru = mngr_->getComponent<Fruit>(frutes[i]);
		fru->update();
	}
	if (numFruts <= 0) {
		Message m;
		m.id = _ROUND_OVER;
		mngr_->send(m);
		Game::instance()->setState(Game::GAMEOVER);
	}
}
