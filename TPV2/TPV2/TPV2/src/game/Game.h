// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <vector>
#include "../ecs/ecs.h"
#include "GameState.h"
#include "../utils/Singleton.h"

class InputHandler;
class PacManSystem;
class GameCtrlSystem;
class CollisionsSystem;
class GhostSystem;
class RenderSystem;
class FoodSystem;

class Game : public Singleton<Game> {
	friend Singleton<Game>;
	Game();
public: 
	enum State {
		RUNNING, PAUSED, NEWGAME, NEWROUND, GAMEOVER
	};
	virtual ~Game();

	void init();
	void start();	

	inline ecs::Manager* getMngr() {
		return mngr_;
	}

	inline void setState(State s) {
		GameState *new_state = nullptr;
		switch (s) {
		case RUNNING:
			new_state = runing_state_;
			break;
		case PAUSED:
			new_state = paused_state_;
			break;
		case NEWGAME:
			new_state = newgame_state_;			
			break;
		case NEWROUND:
			new_state = newround_state_;
			break;
		case GAMEOVER:
			new_state = gameover_state_;
			break;
		default:
			break;
		}
		bool m = current_state_->getMute();
		current_state_->leave();
		current_state_ = new_state;
		current_state_->enter();
		current_state_->setMute(m);
	}
private:
	ecs::Manager *mngr_;
	InputHandler& ihdlr;

	PacManSystem *pacmanSys_;	
	GameCtrlSystem *gameCtrlSys_;
	ecs::System *startsSys_;
	RenderSystem *renderSys_;
	CollisionsSystem *collisionSys_;
	GhostSystem *ghostSys_;
	FoodSystem* foodSys_;
	
	GameState* current_state_;
	GameState* paused_state_;
	GameState* runing_state_;
	GameState* newgame_state_;
	GameState* newround_state_;
	GameState* gameover_state_;
};

