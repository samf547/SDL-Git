#include "EntityBase.h"

EntityBase::EntityBase(int flags, double maxVelocity, double friction) : flags(flags) {
	this->acceleration = Point(0, 0);
	this->angle = 0;
	this->frictionAmount = friction * ((friction > 0) ? 1 : -1);
	this->velocity = PointDelta(0, 0, maxVelocity);
}

EntityBase::~EntityBase() {}

void EntityBase::evalAngle(Point delta) {
	if (delta.getNonZero()) {	
		this->angle = atan2(delta.y(), delta.x());
	}
}

void EntityBase::accelerate(PointDelta delta) {
	this->timer.tick();
	if (abs(delta.x()) < 0.0001) {
		delta -= Point(this->velocity.x(), 0) / this->frictionAmount;
	}
	if (abs(delta.y()) < 0.0001) {
		delta -= Point(0, this->velocity.y()) / this->frictionAmount;
	}
	this->acceleration = delta * this->timer.getRatio();
	this->velocity += this->acceleration;
	this->evalAngle(this->velocity);
}
