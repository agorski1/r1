#include "Projectile.h"
#include "DataTables.h"
#include "Utility.h"

namespace
{
	const std::vector<ProjectileData> Table = initializeProjectileData();
}

Projectile::Projectile(WeaponType weaponType, Type type, const TextureHolder& textures)
	: Entity(1)
	, mType(type)
	, mWeaponType(weaponType)
	, mSprite(textures.get(Table[weaponType].texture))
	, mTargetDirection()
{
	centerOrigin(mSprite);
}

void Projectile::guideTowards(sf::Vector2f position)
{
	assert(isGuided());
	mTargetDirection = unitVector(position - getWorldPosition());
}

bool Projectile::isGuided() const
{
	return mWeaponType == Missile;
}

unsigned int Projectile::getCategory() const
{
	if (mType == EnemyBullet)
		return Category::EnemyProjectile;
	else
		return Category::PlayerProjectile;
}

sf::FloatRect Projectile::getBoundingRect() const
{
	return getWolrdTranform().transformRect(mSprite.getGlobalBounds());
}

float Projectile::getMaxSpeed() const
{
	return Table[mWeaponType].speed;
}

int Projectile::getDamage() const
{
	return Table[mWeaponType].damage;
}

void Projectile::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	if (isGuided())
	{
		const float approachRate = 200.f;
		sf::Vector2f newVelocity = unitVector(approachRate * dt.asSeconds() * mTargetDirection + getVelocity());

		newVelocity *= getMaxSpeed();
		float angle = std::atan2(newVelocity.y, newVelocity.x);

		setRotation(toDegree(angle) + 90.f);
		setVelocity(newVelocity);
	}
	Entity::updateCurrent(dt, commands);
}

void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}
