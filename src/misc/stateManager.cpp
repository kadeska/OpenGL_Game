#include "stateManager.hpp"

using namespace StateManager;

void GameStateManager::setState(GameState newState)
{
    // Prevent redundant transitions
    if (currentState == newState)
        return;

    switch (currentState)
    {
    case GameState::None:
        if (newState == GameState::MainMenu)
            currentState = newState;
        break;

    case GameState::MainMenu:
        if (newState == GameState::Playing)
            currentState = newState;
        break;

    case GameState::Playing:
        if (newState == GameState::Paused || newState == GameState::GameOver)
            currentState = newState;
        break;

    case GameState::Paused:
        if (newState == GameState::Playing || newState == GameState::MainMenu)
            currentState = newState;
        break;

    case GameState::GameOver:
        if (newState == GameState::MainMenu)
            currentState = newState;
        break;
    }
}


GameState GameStateManager::getState() const
{
    return currentState;
}

bool GameStateManager::is(GameState state) const
{
    return currentState == state;
}
