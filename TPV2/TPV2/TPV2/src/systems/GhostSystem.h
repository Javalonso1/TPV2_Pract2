#pragma once

#include "../ecs/System.h"
#include "../utils/Vector2D.h"

struct Transform;

class GhostSystem : public ecs::System
{
public:

	__SYSID_DECL__(ecs::sys::GHOST)

		GhostSystem(Transform*);
	virtual ~GhostSystem();
	void initSystem() override;
	void update() override;
private:
	Transform* gTR_;
	Transform* pmTR_;	
};

