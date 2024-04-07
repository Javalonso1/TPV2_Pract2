// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameOverState.h"

#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "Game.h"
GameOverState::GameOverState(PacManSystem* pacmanSys) :
		msg_(nullptr), dest_(), ihdlr(ih()), pacmanSys_(pacmanSys) {
}

GameOverState::~GameOverState() {
}

void GameOverState::leave() {
}

void GameOverState::update() {
	if (ihdlr.keyDownEvent() && ihdlr.isKeyDown(SDL_SCANCODE_RETURN)) {
		Game::instance()->setState(Game::NEWGAME);
		pacmanSys_->NewGame();
	}
	if (ihdlr.keyDownEvent() && ihdlr.isKeyDown(SDL_SCANCODE_M)) {
		if (!mute_) {
			sdlutils().soundEffects().at("pacman_chomp").setVolume(0);
			sdlutils().soundEffects().at("pacman_death").setVolume(0);
			sdlutils().soundEffects().at("pacman_eat").setVolume(0);
			sdlutils().soundEffects().at("pacman_intro").setVolume(0);
			sdlutils().soundEffects().at("pacman_won").setVolume(0);
			mute_ = true;
		}
		else {
			sdlutils().soundEffects().at("pacman_chomp").setVolume(10);
			sdlutils().soundEffects().at("pacman_death").setVolume(10);
			sdlutils().soundEffects().at("pacman_eat").setVolume(10);
			sdlutils().soundEffects().at("pacman_intro").setVolume(10);
			sdlutils().soundEffects().at("pacman_won").setVolume(10);
			mute_ = false;
		}
	}
	sdlutils().clearRenderer();
	msg_->render(dest_);
	sdlutils().presentRenderer();
}

void GameOverState::enter() {
	auto mngr = Game::instance()->getMngr();
	/*if (mngr->getEntities(ecs::grp::ASTEROIDS).size() > 0) {
		msg_ = &sdlutils().msgs().at("gameover_lost");
	} else {*/
		msg_ = &sdlutils().msgs().at("gameover_won");
	//}
	float x = (sdlutils().width() - msg_->width()) / 2;
	float y = (sdlutils().height() - msg_->height()) / 2;
	dest_ = build_sdlrect(x, y, msg_->width(), msg_->height());
}
