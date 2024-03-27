// This file is part of the course TPV2@UCM - Samir Genaim
/*
#pragma once
#include <SDL_rect.h>

#include "GameState.h"

class Texture;
class InputHandler;

class AsteroidsFacade;
class BlackHoleFacade;
class FighterFacade;
class MisilFacade;

class NewRoundState: public GameState {
public:
	NewRoundState(AsteroidsFacade *ast_mngr, FighterFacade *fighter_mngr, BlackHoleFacade*, MisilFacade* mis_mngr);
	virtual ~NewRoundState();
	void enter() override;
	void leave() override;
	void update() override;
	void setMute(bool m) { mute_ = m; }

private:
	Texture &msg_;
	SDL_Rect dest_;
	InputHandler &ihdlr;
	AsteroidsFacade *ast_mngr_;
	BlackHoleFacade *bh_mngr_;
	FighterFacade *fighter_mngr_;
	MisilFacade *misil_mngr_;
	bool mute_;
};

*/