#pragma once
#include "../ecs/System.h"
class ImmunitySystem : public ecs::System {
public:
	__SYSID_DECL__(ecs::sys::IMMUNITY)
	ImmunitySystem();
	virtual ~ImmunitySystem();
	void initSystem() override;
	void update() override;
	void recieve(const Message&) override;
	void timerInmunity();
private:
	int timeWithInmunity;
	bool inmune;
};	

