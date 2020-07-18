#include "EnemyBase.h"
#include "../../PositionLock.h"

EnemyBase::EnemyBase(Point position, int flags) : ThingBase(flags | DRAW), maxVelocity(200) {
	this->position = position;
	this->timer.start();
	this->pathTimer.start();
}

EnemyBase::~EnemyBase() {}

void EnemyBase::draw(SDL_Renderer* renderer, Point offset) {
	if (this->texture.isLoaded()) {
		this->texture.draw(renderer, this->position - offset);
	}
}

// TODO: Make this generic
void EnemyBase::move(Point velocity) { 
	double tickRatio = this->movement.getValue();
	if (!tickRatio) return;
	Point px = velocity.getUnitVector() * tickRatio * this->maxVelocity;
	if (!px.isReal()) return;
	
	PositionLock lock(this->position);	
	Point modified = px / 4.0;
	for (int i = 0; i < 4; i++) {
		this->position += modified;
		if (this->parent->collision.isPositionOpen(this->shared_from_this())) {
			lock.update();
		} else break;
	}
	lock.revert();
	if (!this->turning) {
		this->angle = atan2(px.y, px.x);
	}
}

std::ostream& operator<<(std::ostream& output, const EnemyBase& base) {
	output << base.position;
	return output;
}

Point EnemyBase::pathFindTo(Point target) {
	return target * 2;
}

void EnemyBase::turn(double delta) {
	if (this->turning) {
		this->angle += delta;
	}
}

void EnemyBase::toggleTurn() {
	this->turning = !this->turning;
}

double EnemyBase::getAngle() const {
	return this->angle;
}


