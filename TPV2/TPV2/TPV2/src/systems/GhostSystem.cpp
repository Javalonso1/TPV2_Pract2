#include "GhostSystem.h"

#include "../components/ImageWithFrames.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../components/Health.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

const float SPEED_ = -2.5f;

GhostSystem::GhostSystem(Transform* pm) :
	pmTR_(pm),gTR_(nullptr) {
}

GhostSystem::~GhostSystem() {
}

void GhostSystem::initSystem() {
	// create the ghost entity
	//
	auto ghost = mngr_->addEntity();
	//mngr_->setHandler(ecs::hdlr::PACMAN, pacman);

	gTR_ = mngr_->addComponent<Transform>(ghost);
	auto s = 50.0f;

	//Hacer que apñarezcan por las esquinas !!!!!!!!!!
	auto x = (sdlutils().width() - s) / 2.0f;
	auto y = (sdlutils().height() - s) / 2.0f;

	gTR_->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);
	mngr_->addComponent<ImageWithFrames>(ghost, &sdlutils().images().at("pacman"),
		8, 8,
		0, 0,
		128, 128,
		4, 4,
		1, 8);	

	//Inicializar el vector
	gTR_->vel_ = (pmTR_->getPos() - gTR_->getPos()).normalize() * 1.1f;

}

void GhostSystem::update() {

	

	// move the pacman
	gTR_->pos_ = gTR_->pos_ + gTR_->vel_;

	// check left/right borders
	if (gTR_->pos_.getX() < 0) {
		gTR_->pos_.setX(0.0f);
		gTR_->vel_.set(0.0f, 0.0f);
	}
	else if (gTR_->pos_.getX() + gTR_->width_ > sdlutils().width()) {
		gTR_->pos_.setX(sdlutils().width() - gTR_->width_);
		gTR_->vel_.set(0.0f, 0.0f);
	}

	// check upper/lower borders
	if (gTR_->pos_.getY() < 0) {
		gTR_->pos_.setY(0.0f);
		gTR_->vel_.set(0.0f, 0.0f);
	}
	else if (gTR_->pos_.getY() + gTR_->height_ > sdlutils().height()) {
		gTR_->pos_.setY(sdlutils().height() - gTR_->height_);
		gTR_->vel_.set(0.0f, 0.0f);
	}

}
