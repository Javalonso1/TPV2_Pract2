// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/System.h"

struct Transform;
class Health;

class PacManSystem: public ecs::System {
public:

	__SYSID_DECL__(ecs::sys::PACMAN)

	PacManSystem();
	virtual ~PacManSystem();

	void initSystem() override;
	void reset_pacman();

	void update() override;
	void recieve(const Message&) override;

	Transform* getTransform() { return pmTR_; }
	int update_lives(int);
	void reset_lives();
private:
	Transform *pmTR_;	
	Health* pmHL_;
};

