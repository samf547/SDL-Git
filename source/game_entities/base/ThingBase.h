#pragma once
#ifndef THING_BASE_H
#define THING_BASE_H
#include "../../primitives/Point.h"
#include "../../primitives/Rect.h"
#include<memory>
#include<SDL2/SDL.h>
#include<vector>

enum ENTITY_FLAGS {
	SOLID                   = 0x0001, // Other objects can collide with this
	NOCLIP                  = 0x0002, // This doesn't collide with others
	MOVEABLE                = 0x0004, // This Object Moves
	DRAW                    = 0x0008, // This is drawn
	BLOCKS_VISIBILTY        = 0x0010  // This blocks visibility
};

class ThingBase {
	protected:
		int flags;
		Point position;
	public:
		virtual ~ThingBase() = 0;
		virtual bool overlap(Rect other) = 0;
		virtual bool overlap(std::shared_ptr<ThingBase>& other) = 0;
		virtual int getFlags() const = 0;
		virtual int originDistance() const = 0;
		virtual Rect getRect() const = 0;
};
//bool operator<(const ThingBase* lhs, const ThingBase* rhs);
#endif
