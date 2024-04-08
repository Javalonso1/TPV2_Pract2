// This file is part of the course TPV2@UCM - Samir Genaim

#include "CollisionsSystem.h"

#include "../components/Transform.h"
#include "../components/Fruit.h"
#include "../ecs/Manager.h"
#include "../utils/Collisions.h"
#include "../sdlutils/SDLUtils.h"

CollisionsSystem::CollisionsSystem() {
	// TODO Auto-generated constructor stub

}

CollisionsSystem::~CollisionsSystem() {
	// TODO Auto-generated destructor stub
}

void CollisionsSystem::initSystem() {
}

void CollisionsSystem::update() {

	// the PacMan's Transform
	auto pm = mngr_->getHandler(ecs::hdlr::PACMAN);
	auto pTR = mngr_->getComponent<Transform>(pm);

	// For safety, we traverse with a normal loop until the current size. In this
	// particular case we could use a for-each loop since the list stars is not
	// modified.
	//
	auto& fruit = mngr_->getEntities(ecs::grp::FRUIT);
	auto n = fruit.size();

	for (auto i = 0u; i < n; i++) {
		auto e = fruit[i];
		if (mngr_->isAlive(e)) { // if the fruit is active

			// the fruit's Transform
			auto fTR = mngr_->getComponent<Transform>(e);

			// check if PacMan collides with the fruit
			if (Collisions::collides(			//
				pTR->pos_, pTR->width_, pTR->height_, //
				fTR->pos_, fTR->width_, fTR->height_)) {

				sdlutils().soundEffects().at("pacman_eat").play();
				Message m;
				m.id = _PACMAN_FOOD_COLLISION;
				m.fruit_data.e = e;
				m.fruit_data.activada = mngr_->getComponent<Fruit>(e)->getActivada();
				mngr_->send(m);
			}
		}
	}

	auto &ghost = mngr_->getEntities(ecs::grp::GHOST);
	n = ghost.size();

	for (auto i = 0u; i < n; i++) {
		auto e = ghost[i];
		if (mngr_->isAlive(e)) { // if the ghost is active (it might have died in this frame)

			// the ghost's Transform
			auto gTR = mngr_->getComponent<Transform>(e);

			// check if PacMan collides with the ghost
			if (Collisions::collides(			//
					pTR->pos_, pTR->width_, pTR->height_, //
					gTR->pos_, gTR->width_, gTR->height_)) {				
				Message m;
				m.id = _PACMAN_GHOST_COLLISION;
				m.ghost_data.e = e;
				mngr_->send(m);
			}
		}
	}

}

