#pragma once
//Like this in BOOK
//#include "TextureManager.h"
//#include "StateManager.h"
//#include "EntityManager.h"
//#include "EventManager.h"
//#include "Window.h"

class TextureManager;
class StateManager;
class EntityManager;
class EventManager;
class Window;
class AudioManager;
class Map;
struct SharedContext
{
	SharedContext()
		: m_map(nullptr),
		m_textureManager(nullptr),
		m_stateManager(nullptr),
		m_entityManager(nullptr),
		m_eventManager(nullptr),
		m_window(nullptr),
		m_audioManager(nullptr) {}

	Map* m_map;
	TextureManager* m_textureManager;
	StateManager* m_stateManager;
	EntityManager* m_entityManager;
	EventManager* m_eventManager;
	Window* m_window;
	AudioManager* m_audioManager;
};