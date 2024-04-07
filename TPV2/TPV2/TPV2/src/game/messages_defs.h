// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <cstdint>
#include "../ecs/ecs.h"

using msgId_type = uint8_t;
enum msgId : msgId_type {
	_NEW_GAME, //
	_ROUND_START,
	_ROUND_OVER,
	_GAME_OVER,
	_PACMAN_FOOD_COLLISION,
	_PACMAN_GHOST_COLLISION,
	_IMMUNITY_START,
	_IMMUNITY_END,
};


struct Message {
	msgId_type id;

	// if we use union we save memory, but then use only primitive
	// types, otherwise you will need to define constructors almost
	// every where.

	union {

		//_PACMAN_GHOST_COLLISION
		struct {
			ecs::entity_t e;
		} ghost_data;
		//_PACMAN_FRUIT_COLLISION
		struct {
			ecs::entity_t e;
			bool activada;
		} fruit_data;
		
	};
};
