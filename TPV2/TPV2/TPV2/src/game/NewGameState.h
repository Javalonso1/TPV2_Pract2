// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_rect.h>

#include "GameState.h"

class Texture;
class InputHandler;
class PacManSystem;

class NewGameState : public GameState {
public:
	NewGameState(PacManSystem* pac_sys);
	virtual ~NewGameState();
	void leave() override;
	void update() override;
	void enter() override;
	void setMute(bool m) { mute_ = m; }
	bool getMute() { return mute_; };
private:
	Texture& msg_;
	SDL_Rect dest_;
	InputHandler& ihdlr;
	PacManSystem* pac_sys_;
	bool mute_;
};