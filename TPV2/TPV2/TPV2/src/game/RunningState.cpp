// This file is part of the course TPV2@UCM - Samir Genaim
/*
#include "RunningState.h"

#include "../components/Gun.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"
#include "AsteroidsFacade.h"
#include "FighterFacade.h"
#include "MisilFacade.h"
#include "BlackHoleUtils.h"

#include "Game.h"

RunningState::RunningState(AsteroidsFacade *ast_mngr,
		FighterFacade *fighter_mngr, MisilFacade* misil_manager) :
		ihdlr(ih()), //
		ast_mngr_(ast_mngr), //
		fighter_mngr_(fighter_mngr), //
		misl_mngr_(misil_manager),
		lastTimeGeneratedAsteroids_(), 
		lastTimeGeneratedMissile_(){
}

RunningState::~RunningState() {
}

void RunningState::leave() {
}

void RunningState::update() {

	auto mngr = Game::instance()->getMngr();

	// check if fighter won
	if (mngr->getEntities(ecs::grp::ASTEROIDS).size() == 0) {
		Game::instance()->setState(Game::GAMEOVER, mute_);
		return;
	}

	// move to pause if P pressed
	if (ihdlr.keyDownEvent() && ihdlr.isKeyDown(SDL_SCANCODE_P)) {
		Game::instance()->setState(Game::PAUSED, mute_);
		return;
	}

	auto fighter = mngr->getHandler(ecs::hdlr::FIGHTER);
	auto &asteroids = mngr->getEntities(ecs::grp::ASTEROIDS);
	auto &blackHoles = mngr->getEntities(ecs::grp::BLACK_HOLE);
	auto& misiles = mngr->getEntities(ecs::grp::MISILE);

	// update
	mngr->update(fighter);
	for (auto a : asteroids) {
		mngr->update(a);
	}
	for (auto a : blackHoles) {
		mngr->update(a);		
	}
	for (auto a : misiles) {
		mngr->update(a);
	}

	// check collisions
	checkCollisions();

	// render
	sdlutils().clearRenderer();
	for (auto a : asteroids) {
		mngr->render(a);
	}
	for (auto a : blackHoles) {
		mngr->render(a);
	}
	for (auto a : misiles) {
		mngr->render(a);
	}
	mngr->render(fighter);
	sdlutils().presentRenderer();

	mngr->refresh();

	if (sdlutils().virtualTimer().currTime() > lastTimeGeneratedAsteroids_ + 10000) {
		ast_mngr_->create_asteroids(1);
		lastTimeGeneratedAsteroids_ = sdlutils().virtualTimer().currTime();
	}
	if (sdlutils().virtualTimer().currTime() > lastTimeGeneratedMissile_ + 15000) {
		misl_mngr_->create_misile();
		lastTimeGeneratedMissile_ = sdlutils().virtualTimer().currTime();
	}
}

void RunningState::enter() {
	lastTimeGeneratedAsteroids_ = sdlutils().virtualTimer().currTime();
}

void RunningState::checkCollisions() {
	auto mngr = Game::instance()->getMngr();
	auto fighter = mngr->getHandler(ecs::hdlr::FIGHTER);
	auto &asteroids = mngr->getEntities(ecs::grp::ASTEROIDS);
	auto &blackHoles = mngr->getEntities(ecs::grp::BLACK_HOLE);
	auto &misiles = mngr->getEntities(ecs::grp::MISILE);
	auto fighterTR = mngr->getComponent<Transform>(fighter);
	auto fighterGUN = mngr->getComponent<Gun>(fighter);

	auto num_of_asteroids = asteroids.size();
	auto num_of_holes = blackHoles.size();
	auto num_of_misiles = misiles.size();
	for (auto i = 0u; i < num_of_asteroids; i++) {
		auto a = asteroids[i];
		if (!mngr->isAlive(a))
			continue;

		// asteroid with fighter
		auto aTR = mngr->getComponent<Transform>(a);
		if (Collisions::collidesWithRotation( //
				fighterTR->getPos(), //
				fighterTR->getWidth(), //
				fighterTR->getHeight(), //
				fighterTR->getRot(), //
				aTR->getPos(), //
				aTR->getWidth(), //
				aTR->getHeight(), //
				aTR->getRot())) {
			onFigherDeath();
			return;
		}

		// asteroid with bullets
		for (Gun::Bullet &b : *fighterGUN) {
			if (b.used) {
				if (Collisions::collidesWithRotation( //
						b.pos, //
						b.width, //
						b.height, //
						b.rot, //
						aTR->getPos(), //
						aTR->getWidth(), //
						aTR->getHeight(), //
						aTR->getRot())) {
					ast_mngr_->split_astroid(a);
					b.used = false;
					sdlutils().soundEffects().at("explosion").play();
					continue;
				}
			}
		}

		for (auto j = 0u; j < num_of_holes; j++) {
			auto b = blackHoles[j];
			auto bTR = mngr->getComponent<Transform>(b);
			if (Collisions::collidesWithRotation( //
				bTR->getPos(), //
				bTR->getWidth(), //
				bTR->getHeight(), //
				bTR->getRot(), //
				aTR->getPos(), //
				aTR->getWidth(), //
				aTR->getHeight(), //
				aTR->getRot())) {
				ast_mngr_->teleport(a);
				//sdlutils().soundEffects().at("explosion").play();
				continue;
			}
		}

		//asteroid with black holes
	}

	for (auto i = 0u; i < num_of_holes; i++) {
		auto b = blackHoles[i];
		if (!mngr->isAlive(b))
			continue;

		// asteroid with fighter
		auto bTR = mngr->getComponent<Transform>(b);
		if (Collisions::collidesWithRotation( //
			fighterTR->getPos(), //
			fighterTR->getWidth(), //
			fighterTR->getHeight(), //
			fighterTR->getRot(), //
			bTR->getPos(), //
			bTR->getWidth(), //
			bTR->getHeight(), //
			bTR->getRot())) {
			onFigherDeath();
			return;
		}
	}

	for (auto i = 0u; i < num_of_misiles; i++) {
		auto m = misiles[i];
		if (!mngr->isAlive(m))
			continue;

		// asteroid with fighter
		auto mTR = mngr->getComponent<Transform>(m);
		if (Collisions::collidesWithRotation( //
			fighterTR->getPos(), //
			fighterTR->getWidth(), //
			fighterTR->getHeight(), //
			fighterTR->getRot(), //
			mTR->getPos(), //
			mTR->getWidth(), //
			mTR->getHeight(), //
			mTR->getRot())) {
			onFigherDeath();
			return;
		}
		for (Gun::Bullet& b : *fighterGUN) {
			if (b.used) {
				if (Collisions::collidesWithRotation( //
					b.pos, //
					b.width, //
					b.height, //
					b.rot, //
					mTR->getPos(), //
					mTR->getWidth(), //
					mTR->getHeight(), //
					mTR->getRot())) {				
					misl_mngr_->delete_misil(m);
					b.used = false;
					sdlutils().soundEffects().at("explosion").play();
					continue;
				}
			}
		}

	}
	if (ihdlr.keyDownEvent() && ihdlr.isKeyDown(SDL_SCANCODE_M)) {
		if (!mute_) {
			sdlutils().soundEffects().at("explosion").setVolume(0);
			sdlutils().soundEffects().at("fire").setVolume(0);
			sdlutils().soundEffects().at("gunshot").setVolume(0);
			sdlutils().soundEffects().at("thrust").setVolume(0);
			mute_ = true;
		}
		else {
			sdlutils().soundEffects().at("fire").setVolume(10);
			sdlutils().soundEffects().at("gunshot").setVolume(10);
			sdlutils().soundEffects().at("explosion").setVolume(10);
			sdlutils().soundEffects().at("thrust").setVolume(10);
			mute_ = false;
		}
	}
	
}

void RunningState::onFigherDeath() {
	sdlutils().soundEffects().at("explosion").play();
	if (fighter_mngr_->update_lives(-1) > 0)
		Game::instance()->setState(Game::NEWROUND, mute_);
	else
		Game::instance()->setState(Game::GAMEOVER, mute_);
}
*/