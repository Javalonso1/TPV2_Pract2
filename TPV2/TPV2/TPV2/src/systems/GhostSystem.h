#pragma once

#include "../ecs/System.h"
#include "../utils/Vector2D.h"

class Transform;

class GhostSystem : public ecs::System
{
public:

	__SYSID_DECL__(ecs::sys::GHOST)

	GhostSystem(Transform*);
	virtual ~GhostSystem();
	void initSystem() override;
	void update() override;
	void addGhost();
	void recieve(const Message& m) override;
private:	
	Transform* pmTR_;
	int numGhosts;
	int maxGhosts;
	bool inmunity_;
};
