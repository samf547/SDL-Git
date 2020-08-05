#include "FpsText.h"
#include<string>
#include<sstream>
#include "../essential/constants.h"

FpsText::FpsText(Font& font, Point position, SDL_Color color) : position(position), color(color) {
	font = font;
	this->fpsTimer.start();
	this->frameTimer.start();
}

FpsText::~FpsText() {}

double FpsText::getFps() const {
	return this->fpsTimer.getFps();
}

void FpsText::draw(SDL_Renderer* renderer) {
	this->fpsTimer.tick();
	std::stringstream fpsStr;
	fpsStr.str("");
	fpsStr << "FPS: " << int(this->fpsTimer.getFps());
	this->font.drawText(this->position, fpsStr.str(), renderer, this->color);
}

void FpsText::drawFrameTime(SDL_Renderer* renderer) {
	std::stringstream fpsStr;
	fpsStr.str("");
	fpsStr << "Frame Time: " << this->frameTimer.getTicks() << " ms";
	this->font.drawText(this->position + Point(0, 20), fpsStr.str(), renderer, this->color);
	this->frameTimer.start();
}
