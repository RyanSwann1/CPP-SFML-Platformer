#include "EntityManager.h"
#include <math.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

EntityManager::EntityManager(SharedContext* sharedContext)
	: m_entityID(0)
{
	loadInEntityTypes("EntityTypes.txt");
}

EntityManager::~EntityManager()
{
	purgeFactory();
	purgeEntities();
}

void EntityManager::add(Entity* entity)
{
	m_entities.emplace_back(std::make_pair(m_entityID, entity));
	m_entities.back().second->setID(m_entityID);

	++m_entityID;
}

void EntityManager::add(Entity * entity, const sf::Vector2f & pos)
{
	entity->setPosition(pos);
	m_entities.emplace_back(std::make_pair(m_entityID, entity));
	++m_entityID;
}

//Will change name of function
void EntityManager::addExisting(const EntityType entityType, const sf::Vector2i& pos)
{
	auto iter = m_entityFactory.find(entityType);
	if (iter != m_entityFactory.cend())
	{
		m_entities.emplace_back(m_entityID, iter->second());
		//m_entities.back().second->setPos(pos); Set the position here instead
		++m_entityID;
	}
}

void EntityManager::removeEntity(const unsigned int id)
{
	if (std::find(m_removals.cbegin(), m_removals.cend(), id) == m_removals.cend())
	{
		m_removals.push_back(id);
	}
}

void EntityManager::update(const float deltaTime)
{
	auto entitesCopy = m_entities;
	for (auto &i : entitesCopy)
	{
		i.second->update(deltaTime);
	}

	processRemovals();
}

void EntityManager::draw(sf::RenderWindow & window)
{
	for (const auto &i : m_entities)
	{
		i.second->draw(window);
	}
}

Entity * EntityManager::findEntity(const std::string & name)
{
	for (auto cIter = m_entities.cbegin(); cIter != m_entities.cend(); ++cIter)
	{
		if (cIter->second->getName() == name)
		{
			return cIter->second;
		}
	}
	return nullptr;
}

Entity * EntityManager::getEntityAtPosition(const sf::Vector2i & pos)
{
	for (auto cIter = m_entities.cbegin(); cIter != m_entities.cend(); ++cIter)
	{
		if (cIter->second->getPosition() == pos)
		{
			return cIter->second;
		}
	}
	return nullptr;
}

void EntityManager::sortCollisions()
{

}

void EntityManager::processRemovals()
{
	for (const auto &i : m_removals)
	{
		removeActiveEntity(i);
	}

	m_removals.clear();
}

void EntityManager::removeActiveEntity(unsigned int entityID)
{
	for (auto iter = m_entities.begin(); iter != m_entities.end(); ++iter)
	{
		if (iter->second->getID() == entityID)
		{
			delete iter->second;
			iter->second = nullptr;
			m_entities.erase(iter);
			return;
		}
	}
}

void EntityManager::loadInEntityTypes(const std::string& fileName)
{
	std::ifstream file;
	file.open(fileName);
	if (!file.is_open())
	{
		std::cerr << "Unable to open file: " << fileName << "\n";
	}

	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream keyStream(line);
		std::string entityName;
		std::string entityTypeLocation;
		keyStream >> entityName >> entityTypeLocation;

		if (!m_entityTypes.emplace(entityName, entityTypeLocation).second)
		{
			std::cerr << "Unable to open EntityName: " << entityName << ". EntityTypeLocation: " << entityTypeLocation << "\n";
			continue;
		}
	}
	file.close();
}

void EntityManager::purgeFactory()
{
	for (auto &i : m_entityFactory)
	{
		delete i.second();
		i.second = nullptr;
	}
	m_entityFactory.clear();
}

void EntityManager::purgeEntities()
{
	for (auto &i : m_entities)
	{
		delete i.second;
		i.second = nullptr;
	}
	m_entities.clear();
}

std::string EntityManager::getEntityTypeLocation(const std::string & name) const
{
	auto cIter = m_entityTypes.find(name);
	if (cIter != m_entityTypes.cend())
	{
		return cIter->second;
	}
}