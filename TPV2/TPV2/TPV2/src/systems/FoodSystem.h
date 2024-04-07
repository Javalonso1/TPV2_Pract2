#pragma once
#include "../ecs/System.h"
class FoodSystem : public ecs::System
{
public:
	__SYSID_DECL__(ecs::sys::FRUIT)
	FoodSystem();
	virtual ~FoodSystem();
	void initSystem() override;
	void update() override;
	void resetFruit();
	void resetFruitTimers();
	void createFruits();
	void removeFruit(ecs::entity_t e);
	void recieve(const Message& m) override;
private:
	int numFruts;
};


