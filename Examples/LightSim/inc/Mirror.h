#pragma once

#include "OpticalElement.h"

class Mirror : public OpticalElement
{
public:
	Mirror(const std::string& name = "Mirror");
	Mirror(const Mirror& other);
	~Mirror();
	OBJECT_DECL(Mirror);

	void setColor(const sf::Color& c);
	const sf::Color& getColor() const;

	void setPos(const sf::Vector2f& pos);
	const sf::Vector2f& getPos() const;

	void setRotation(float angle);
	float getRotation() const;

	void setWidth(float w);
	float getWidth();

private:
	void updateLine();

	void update() override;

	class MirrorShape : public Shape
	{
	public:
		bool getCollisionData(const LightRay& ray,
			float& outCollisionFactor, float& outNormalAngle, bool& rayStartsInsideShape) const override;

		float m_width;
		float m_angle;
		sf::Vector2f m_pos;
		QSFML::Utilities::Ray m_mirrorRay;
	};

	MirrorShape m_shape;
	QSFML::Components::LinePainter* m_mirrorLine;
	
	float m_rotationSpeed;
};
