#include "GhostSystem.h"

#include "../components/ImageWithFrames.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../components/Health.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

const float SPEED_ = -1.5f;
const int TIME_GHOST_GENERATION_ = 5000;
const int MAX_GHOSTS_ = 10;
const int TURN_CHANCE = 501;

GhostSystem::GhostSystem(Transform* pm) :
	pmTR_(pm), numGhosts(0), maxGhosts(MAX_GHOSTS_), timeGeneratingGhosts(sdlutils().currRealTime()){
}

GhostSystem::~GhostSystem() {
}

void GhostSystem::initSystem() {

}
void GhostSystem::resetGhosts() {
	
	auto ghosts = mngr_->getEntities(ecs::grp::GHOST);	
	for (int i = 0; i < numGhosts; i++) {
		removeGhost(ghosts[i]);
	}
}
void GhostSystem::addGhost() {
	if (numGhosts < maxGhosts && !inmunity_) {
		// Always use the random number generator provided by SDLUtils	
		auto& rand_ = sdlutils().rand();
		// create the ghost entity		
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

		auto color = rand_.nextInt(4, 9);

		gTR_->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);
		auto im = mngr_->addComponent<ImageWithFrames>(ghost, &sdlutils().images().at("pacman"),
			8, 8,
			0, 0,
			128, 128,
			color, 1,
			1, 7);
		//Inicializar el vector
		gTR_->vel_ = (pmTR_->getPos() - gTR_->getPos()).normalize() * 1.1f;

		//Add +1 to the number of ghosts
		numGhosts++;
	}	
}
void GhostSystem::removeGhost(ecs::entity_t e) {
	mngr_->setAlive(e, false);
	numGhosts--;
}
void GhostSystem::changeFrameAllGhosts(int a, int b) {
	auto ghosts = mngr_->getEntities(ecs::grp::GHOST);
	for (int i = 0; i < ghosts.size(); i++) {
		mngr_->getComponent<ImageWithFrames>(ghosts[i])->changeFrame(a, b);
	}
}
void GhostSystem::recieve(const Message& m)
{	
	auto& rand_ = sdlutils().rand();
	auto color = rand_.nextInt(4, 9);
	switch (m.id) {
	case _ROUND_START:		
		resetGhosts();
		timeGeneratingGhosts = sdlutils().currRealTime();
		break;
	case _IMMUNITY_START:
		inmunity_ = true;	
		changeFrameAllGhosts(3,5);
		break;
	case _IMMUNITY_END:
		inmunity_ = false;
		changeFrameAllGhosts(color, 1);
		break;
	case _PACMAN_GHOST_COLLISION:
		if (inmunity_) {
			removeGhost(m.ghost_data.e);
		}
		else {
			Message m;
			m.id = _ROUND_OVER;
			mngr_->send(m);
			resetGhosts();
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
		// move the ghost
		gTR_->pos_ = gTR_->pos_ + gTR_->vel_;
		
		//check if change direction with 0.005 of prob
		int a = rand_.nextInt(0, TURN_CHANCE);
		if (a <= 5) {
			if (inmunity_) gTR_->vel_ = (pmTR_->getPos() - gTR_->getPos()).normalize() * -1.1f;
			else gTR_->vel_ = (pmTR_->getPos() - gTR_->getPos()).normalize() * 1.1f;
		}

		// check left/right borders
		if (gTR_->pos_.getX() < 0) {
			gTR_->pos_.setX(0.0f);
			gTR_->vel_ = (pmTR_->getPos() - gTR_->getPos()).normalize() * 1.1f;
		}
		else if (gTR_->pos_.getX() + gTR_->width_ > sdlutils().width()) {
			gTR_->pos_.setX(sdlutils().width() - gTR_->width_);
			gTR_->vel_ = (pmTR_->getPos() - gTR_->getPos()).normalize() * 1.1f;
		}

		// check upper/lower borders
		if (gTR_->pos_.getY() < 0) {
			gTR_->pos_.setY(0.0f);
			gTR_->vel_ = (pmTR_->getPos() - gTR_->getPos()).normalize() * 1.1f;
		}
		else if (gTR_->pos_.getY() + gTR_->height_ > sdlutils().height()) {
			gTR_->pos_.setY(sdlutils().height() - gTR_->height_);
			gTR_->vel_ = (pmTR_->getPos() - gTR_->getPos()).normalize() * 1.1f;
		}
	}

	//Check if it generates a new ghost
	if (currTime > timeGeneratingGhosts + TIME_GHOST_GENERATION_) {		
		addGhost();
		timeGeneratingGhosts = currTime;
	}
}
