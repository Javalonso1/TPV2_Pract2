// This file is part of the course TPV2@UCM - Samir Genaim

#include "NewRoundState.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "../systems/PacManSystem.h"
#include "Game.h"
NewRoundState::NewRoundState(PacManSystem* pac_sys) :
		msg_(sdlutils().msgs().at("newround")), //
		ihdlr(ih()), //
		pac_sys_(pac_sys) {
	float x = (sdlutils().width() - msg_.width()) / 2;
	float y = (sdlutils().height() - msg_.height()) / 2;
	dest_ = build_sdlrect(x, y, msg_.width(), msg_.height());
}

NewRoundState::~NewRoundState() {
}

void NewRoundState::leave() {
}

void NewRoundState::update() {
	if (ihdlr.keyDownEvent() && ihdlr.isKeyDown(SDL_SCANCODE_RETURN)) {
		//Reiniciar todo (nave, frutas, pacman, etc)
		pac_sys_->reset_pacman();
		//TO DO

		Game::instance()->setState(Game::RUNNING);
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
	msg_.render(dest_);
	sdlutils().presentRenderer();
}

void NewRoundState::enter() {
}
