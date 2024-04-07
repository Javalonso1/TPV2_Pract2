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
	void resetGhosts();
	void addGhost();
	void removeGhost(ecs::entity_t e);
	void changeFrameAllGhosts(int a, int b);
	void recieve(const Message& m) override;
private:	
	Transform* pmTR_;
	int numGhosts;
	int maxGhosts;
	int timeGeneratingGhosts;
	bool inmunity_;
};
