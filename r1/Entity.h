#pragma once
#include "SFML/System/Time.hpp"
#include "SFML/System/Vector2.hpp"
#include "SceneNode.h"
#include "ResourceIdentifiers.h"


class CommandQueue;

class Entity : public SceneNode
{
public:	
	explicit Entity(int hitpoints);
	void damage(int points);
	void destroy();
	void remove();

	int getHitpoints() const;
	virtual bool isDestroyed() const;

	void setVelocity(sf::Vector2f velocity);
	void setVelocity(float vx, float vy);

	void accelerate(sf::Vector2f velocity);
	void accelerate(float vx, float vy);


	sf::Vector2f getVelocity() const;

protected:
	virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Vector2f mVelocity;
	int mHitpoints;
};

