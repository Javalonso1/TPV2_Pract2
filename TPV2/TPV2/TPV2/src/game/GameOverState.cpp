// This file is part of the course TPV2@UCM - Samir Genaim
/*
#include "GameOverState.h"

#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "Game.h"
GameOverState::GameOverState() :
		msg_(nullptr), dest_(), ihdlr(ih()) {
}

GameOverState::~GameOverState() {
}

void GameOverState::leave() {
}

void GameOverState::update() {
	if (ihdlr.keyDownEvent() && ihdlr.isKeyDown(SDL_SCANCODE_RETURN)) {
		Game::instance()->setState(Game::NEWGAME, mute_);
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
	sdlutils().clearRenderer();
	msg_->render(dest_);
	sdlutils().presentRenderer();
}

void GameOverState::enter() {
	auto mngr = Game::instance()->getMngr();
	if (mngr->getEntities(ecs::grp::ASTEROIDS).size() > 0) {
		msg_ = &sdlutils().msgs().at("gameover_lost");
	} else {
		msg_ = &sdlutils().msgs().at("gameover_won");
	}
	float x = (sdlutils().width() - msg_->width()) / 2;
	float y = (sdlutils().height() - msg_->height()) / 2;
	dest_ = build_sdlrect(x, y, msg_->width(), msg_->height());
}
*/