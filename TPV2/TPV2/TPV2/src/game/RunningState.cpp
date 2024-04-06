// This file is part of the course TPV2@UCM - Samir Genaim

#include "RunningState.h"

#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"
#include "../systems/PacManSystem.h"
#include "../systems/CollisionsSystem.h"
#include "../systems/GameCtrlSystem.h"
#include "../systems/GhostSystem.h"
#include "../systems/RenderSystem.h"


#include "Game.h"

RunningState::RunningState(PacManSystem* pac_sys, RenderSystem* render_sys, CollisionsSystem* col_sys, GameCtrlSystem* gamectrl_sys, GhostSystem* ghost_sys) :
	ihdlr(ih()), //
	pac_sys_(pac_sys),
	render_sys_(render_sys),
	colision_sys_(col_sys),
	gameCtrl_sys_(gamectrl_sys),
	ghost_sys_(ghost_sys)	
{
	ghost_sys_->addGhost();
}

RunningState::~RunningState() {
}

void RunningState::leave() {
}

void RunningState::update() {

	auto mngr = Game::instance()->getMngr();

	// check if pacman won
	if (true == false) {
		Game::instance()->setState(Game::GAMEOVER);
		return;
	}

	// move to pause if P pressed
	if (ihdlr.keyDownEvent() && ihdlr.isKeyDown(SDL_SCANCODE_P)) {
		Game::instance()->setState(Game::PAUSED);
		return;
	}

	// update
	pac_sys_->update();
	ghost_sys_->update();
	gameCtrl_sys_->update();

	// check collisions
	colision_sys_->update();

	// render
	sdlutils().clearRenderer();
	render_sys_->update();
	sdlutils().presentRenderer();

	/*
	//Ghosts
	if (sdlutils().virtualTimer().currTime() > lastTimeGeneratedGhost_ + 5000) {
		//ast_mngr_->create_asteroids(1);
		lastTimeGeneratedGhost_ = sdlutils().virtualTimer().currTime();
	}*/
}

void RunningState::enter() {
	
}/*
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
	
}*/

