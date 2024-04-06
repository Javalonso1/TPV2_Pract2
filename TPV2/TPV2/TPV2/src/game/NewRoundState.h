// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_rect.h>

#include "GameState.h"

class Texture;
class InputHandler;

class PacManSystem;

class NewRoundState: public GameState {
public:
	NewRoundState(PacManSystem* pac_sys);
	virtual ~NewRoundState();
	void enter() override;
	void leave() override;
	void update() override;
	void setMute(bool m) { mute_ = m; }
	bool getMute() { return mute_; };

private:
	Texture &msg_;
	SDL_Rect dest_;
	InputHandler &ihdlr;

	PacManSystem* pac_sys_;

	bool mute_;
};

