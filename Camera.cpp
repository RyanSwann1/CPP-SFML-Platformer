#include "Camera.h"
#include "SharedContext.h"
#include "StateManager.h"
#include "Window.h"
#include "Entity.h"
#include <SFML\Graphics.hpp>

Camera::Camera(SharedContext* sharedContext)
	: m_sharedContext(sharedContext)
{
}


Camera::~Camera()
{
}

void Camera::update(Entity* player)
{
	sf::View* viewSpace = &m_sharedContext->m_stateManager->getCurrentState()->getView();
	if (player->getActualPosition().x >= viewSpace->getCenter().x)
	{
		viewSpace->setCenter(player->getActualPosition().x, viewSpace->getCenter().y);
	}

	m_sharedContext->m_window->getWindow().setView(*viewSpace);
}

void Camera::reset()
{
	Window* window = m_sharedContext->m_window;
	sf::FloatRect defaultViewSpace = window->getViewSpace();
	window->getWindow().setView(sf::View(defaultViewSpace));
}
