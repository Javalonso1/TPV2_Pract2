// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_stdinc.h>

#include "GameState.h"

class InputHandler;

class PacManSystem;
class RenderSystem;
class CollisionsSystem;
class GameCtrlSystem;

class RunningState: public GameState {
public:
	RunningState(PacManSystem *pac_sys, RenderSystem* render_sys, CollisionsSystem* colision_sys, GameCtrlSystem* gamectrl_sys);
	virtual ~RunningState();
	void leave() override;
	void update() override;
	void enter() override;
	void setMute(bool m) { mute_ = m; }
private:
	//void checkCollisions();
	//void onFigherDeath();

	InputHandler &ihdlr;

	PacManSystem* pac_sys_;
	RenderSystem* render_sys_;
	CollisionsSystem* colision_sys_;
	GameCtrlSystem* gameCtrl_sys_;

	bool mute_;
};

