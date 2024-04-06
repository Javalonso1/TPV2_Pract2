// This file is part of the course TPV2@UCM - Samir Genaim

#include "PausedState.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Game.h"

PausedState::PausedState() :
		msg_(sdlutils().msgs().at("paused")), //
		ihdlr(ih()) {
	float x = (sdlutils().width() - msg_.width()) / 2;
	float y = (sdlutils().height() - msg_.height()) / 2;
	dest_ = build_sdlrect(x, y, msg_.width(), msg_.height());
}

PausedState::~PausedState() {
}

void PausedState::enter() {
	sdlutils().virtualTimer().pause();
}

void PausedState::leave() {
	sdlutils().virtualTimer().resume();
}

void PausedState::update() {
	if (ihdlr.keyDownEvent()) {
		Game::instance()->setState(Game::RUNNING);
	}
	
	if (ihdlr.keyDownEvent() && ihdlr.isKeyDown(SDL_SCANCODE_M)) {
		if (!mute_) {
			/*
			sdlutils().soundEffects().at("explosion").setVolume(0);
			sdlutils().soundEffects().at("fire").setVolume(0);
			sdlutils().soundEffects().at("gunshot").setVolume(0);
			sdlutils().soundEffects().at("thrust").setVolume(0);*/
			mute_ = true;
		}
		else {
			/*
			sdlutils().soundEffects().at("fire").setVolume(10);
			sdlutils().soundEffects().at("gunshot").setVolume(10);
			sdlutils().soundEffects().at("explosion").setVolume(10);
			sdlutils().soundEffects().at("thrust").setVolume(10);*/
			mute_ = false;
		}
	}
	
	sdlutils().clearRenderer();
	msg_.render(dest_);
	sdlutils().presentRenderer();
}

