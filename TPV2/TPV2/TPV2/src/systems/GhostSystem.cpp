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
	pmTR_(pm), numGhosts(0), maxGhosts(10) {
}

GhostSystem::~GhostSystem() {
}

void GhostSystem::initSystem() {

}
void GhostSystem::addGhost() {
	// Always use the random number generator provided by SDLUtils
	//
	auto& rand_ = sdlutils().rand();
	// create the ghost entity
	//
	auto ghost = mngr_->addEntity(ecs::grp::GHOST);
	auto gTR_ = mngr_->addComponent<Transform>(ghost);
	auto s = 50.0f;

	int a = rand_.nextInt(0, 2);
	int x_;
	int y_;
	if (a == 1) {
		x_ = sdlutils().width();
	}
	else
	{
		x_ = 0;
	}
	a = rand_.nextInt(0, 2);
	if (a == 1) {
		y_ = sdlutils().height();
	}
	else
	{
		y_ = 0;
	}

	auto x = x_ - s;
	auto y = y_ - s;

	gTR_->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);
	mngr_->addComponent<ImageWithFrames>(ghost, &sdlutils().images().at("pacman"),
		8, 8,
		0, 0,
		128, 128,
		4, 1,
		1, 7);

	//Inicializar el vector
	gTR_->vel_ = (pmTR_->getPos() - gTR_->getPos()).normalize() * 1.1f;
}

void GhostSystem::recieve(const Message& m)
{
	switch (m.id) {
	case _ROUND_START:
		//Borrar fantasmas en pantalla, instanciar uno nuevo
		break;
	case _IMMUNITY_START:
		inmunity_ = true;
		break;
	case _IMMUNITY_END:
		inmunity_ = false;
		break;
	case _PACMAN_GHOST_COLLISION:
		if (inmunity_) {

		}
		else {
			Message m;
			m.id = _ROUND_OVER;
			mngr_->send(m);
		}
		break;
	default:
		break;
	}
}

void GhostSystem::update() {
	auto& rand_ = sdlutils().rand();

	auto currTime = sdlutils().currRealTime();
	auto ghosts = mngr_->getEntities(ecs::grp::GHOST);
	auto n = ghosts.size();

	for (auto i = 0u; i < n; i++) {
		auto gTR_ = mngr_->getComponent<Transform>(ghosts[i]);
		//check if change direction with 0.005 of prob
		int a = rand_.nextInt(0, 1001);
		if (a <= 5) {
			gTR_->vel_ = (pmTR_->getPos() - gTR_->getPos()).normalize() * 1.1f;
		}

		// move the ghost
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
}
