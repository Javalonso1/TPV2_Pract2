// This file is part of the course TPV2@UCM - Samir Genaim

#include "PacManSystem.h"

#include "../components/ImageWithFrames.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../components/Health.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../game/Game.h"

const float SPEED = -2.5f;
const int MAX_LIVES = 3;
const int TIME_INMUNE = 10000;

PacManSystem::PacManSystem() :
		pmTR_(nullptr), inmune(false) {
}

PacManSystem::~PacManSystem() {
}

void PacManSystem::initSystem() {
	// create the PacMan entity
	auto pacman = mngr_->addEntity();
	mngr_->setHandler(ecs::hdlr::PACMAN, pacman);

	pmTR_ = mngr_->addComponent<Transform>(pacman);
	reset_pacman();
	mngr_->addComponent<ImageWithFrames>(pacman, &sdlutils().images().at("pacman"),
		8, 8, 
		0,0 , 
		128,128,
		0,0,
		1,4);
	pmHL_ = mngr_->addComponent<Health>(pacman, MAX_LIVES);
}

void PacManSystem::reset_pacman() {
	auto s = 50.0f;
	auto x = (sdlutils().width() - s) / 2.0f;
	auto y = (sdlutils().height() - s) / 2.0f;
	pmTR_->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);

	Message m;
	m.id = _ROUND_START;
	mngr_->send(m);
}
void PacManSystem::NewGame() {	
	auto pac = mngr_->getHandler(ecs::hdlr::PACMAN);
	auto health_ = mngr_->getComponent<Health>(pac);
	health_->set_lives(MAX_LIVES);


	Message m;
	m.id = _NEW_GAME;
	mngr_->send(m);
}
void PacManSystem::update() {

	auto &ihldr = ih();

	if (ihldr.keyDownEvent()) {

		if (ihldr.isKeyDown(SDL_SCANCODE_RIGHT)) { // rotate right
			pmTR_->rot_ = pmTR_->rot_ + 90.0f;

			pmTR_->vel_ = pmTR_->vel_.rotate(90.0f);
		} else if (ihldr.isKeyDown(SDL_SCANCODE_LEFT)) { // rotate left
			pmTR_->rot_ = pmTR_->rot_ - 90.0f;

			pmTR_->vel_ = pmTR_->vel_.rotate(-90.0f);
		} else if (ihldr.isKeyDown(SDL_SCANCODE_UP)) { // increase speed
			
			pmTR_->vel_ = Vector2D(0.0f, SPEED).rotate(pmTR_->rot_);

		} else if (ihldr.isKeyDown(SDL_SCANCODE_DOWN)) { // decrease speed
			
			pmTR_->vel_ = Vector2D(0.0f, 0.0f).rotate(pmTR_->rot_);

		}

	}

	// move the pacman
	pmTR_->pos_ = pmTR_->pos_ + pmTR_->vel_;

	// check left/right borders
	if (pmTR_->pos_.getX() < 0) {
		pmTR_->pos_.setX(0.0f);
		pmTR_->vel_.set(0.0f, 0.0f);
	} else if (pmTR_->pos_.getX() + pmTR_->width_ > sdlutils().width()) {
		pmTR_->pos_.setX(sdlutils().width() - pmTR_->width_);
		pmTR_->vel_.set(0.0f, 0.0f);
	}

	// check upper/lower borders
	if (pmTR_->pos_.getY() < 0) {
		pmTR_->pos_.setY(0.0f);
		pmTR_->vel_.set(0.0f, 0.0f);
	} else if (pmTR_->pos_.getY() + pmTR_->height_ > sdlutils().height()) {
		pmTR_->pos_.setY(sdlutils().height() - pmTR_->height_);
		pmTR_->vel_.set(0.0f, 0.0f);
	}
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
void PacManSystem::timerInmunity() {	
	if (!inmune) {
		inmune = true;
		timeWithInmunity = sdlutils().currRealTime();		
	}	
}

void PacManSystem::recieve(const Message& m) {
	switch (m.id) {
	case _ROUND_OVER:
		if (pmHL_->update_lives(-1) > 0)
			Game::instance()->setState(Game::NEWROUND);
		else
			Game::instance()->setState(Game::GAMEOVER);
		break;
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

int PacManSystem::update_lives(int mod) {
	return pmHL_->update_lives(mod);
}

void PacManSystem::reset_lives()
{
	pmHL_->set_lives(MAX_LIVES);
}
