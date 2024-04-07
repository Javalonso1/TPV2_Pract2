#pragma once

#include "../ecs/Component.h"

class ImageWithFrames;


class Fruit : public ecs::Component
{
public:
	__CMPID_DECL__(ecs::cmp::FRUITCOMPONENT)
	Fruit(ImageWithFrames*);
	virtual ~Fruit();
	void initComponent() override;
	void update() override;
	void resetTimer();
	void Activate();
	void DisActivate();

	bool getActivada() { return activada; }
private:
	bool milagroso;
	bool activada;
	int N;
	int M;
	int timeToChange;
	ImageWithFrames* im_;
};

