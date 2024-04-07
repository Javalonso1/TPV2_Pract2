// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_rect.h>

#include "GameState.h"
#include "..\systems\PacManSystem.h"

class Texture;
class InputHandler;

class GameOverState: public GameState {
public:
	GameOverState(PacManSystem* pacmanSys);
	virtual ~GameOverState();
	void leave() override;
	void update() override;
	void enter() override;
	void setMute(bool m) { mute_ = m; }
	bool getMute() { return mute_; };
private:
	Texture *msg_;
	SDL_Rect dest_;
	InputHandler &ihdlr;
	PacManSystem* pacmanSys_;
	bool mute_;
};

