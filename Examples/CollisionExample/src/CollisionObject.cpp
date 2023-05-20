#include "CollisionObject.h"

CLONE_FUNC_IMPL(CollisionObject);
CollisionObject::CollisionObject(const std::string& name, CanvasObject* parent)
	: CanvasObject(name)
{
	m_collider = new QSFML::Components::Collider();
	m_collider->setVertecies({
			sf::Vector2f(0,0),
			sf::Vector2f(10,10),
			sf::Vector2f(5,20)
		});

	addComponent(m_collider);
	addComponent(m_collider->createPainter());
}
CollisionObject::~CollisionObject()
{

}