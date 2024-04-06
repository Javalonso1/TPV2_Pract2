// This file is part of the course TPV2@UCM - Samir Genaim

#include "NewGameState.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "Game.h"

NewGameState::NewGameState(PacManSystem* pac_sys) :
		msg_(sdlutils().msgs().at("newgame")), //
		ihdlr(ih()), //
		pac_sys_(pac_sys)
		{
	float x = (sdlutils().width() - msg_.width()) / 2;
	float y = (sdlutils().height() - msg_.height()) / 2;
	dest_ = build_sdlrect(x, y, msg_.width(), msg_.height());
}

NewGameState::~NewGameState() {
}

void NewGameState::leave() {
}

void NewGameState::update() {
	if (ihdlr.keyDownEvent()) {
		//REINICIAR VIDAS DE PACOHOMBRE
		Game::instance()->setState(Game::NEWROUND);
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

void NewGameState::enter() {
}
