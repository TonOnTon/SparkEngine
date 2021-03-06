#include "Engine.hpp"

#include "World.hpp"
#include "Camera.hpp"

#include <cassert>

Engine g_engine;

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::init()
{
    assert(m_world, "set world");
    assert(m_camera, "set camera");

    m_window.create(sf::VideoMode(200, 200), "Engine");
    m_window.setFramerateLimit(144);

    m_world->init();
}

void Engine::run()
{
    while (m_window.isOpen())
    {
        m_dt = m_clock.restart();

        handleEvent();
        update();
        draw();
    }
}

void Engine::handleEvent()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::EventType::Closed)
            m_window.close();

        m_world->handleEvent(event);
    }
}

void Engine::update()
{
    m_world->update(m_dt.asSeconds());
}

void Engine::draw()
{
    m_window.clear();

    m_window.setView(m_camera->getView());

    m_world->draw(m_window, sf::RenderStates());

    m_window.display();
}
