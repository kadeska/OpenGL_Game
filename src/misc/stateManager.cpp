#include "stateManager.hpp"

#include "../misc/programLogger.hpp"
using ProgramLogger::log;
using ProgramLogger::LogLevel;
using LogLevel::STATE;


using namespace StateManager;

static bool success = false;
static GameState currentState = GameState::None;
static GameState previousState = GameState::None;

void GameStateManager::setState(GameState newState)
{
	// reset success flag to false
	success = false;

    // Prevent redundant transitions
    if (currentState == newState)
        return;

	

    switch (currentState)
    {
    case GameState::None:
        if (newState == GameState::MainMenu) 
        {
            currentState = newState;
			success = true;
        }
        break;

    case GameState::MainMenu:
        if (newState == GameState::Playing)
        {
            currentState = newState;
			success = true;
        }
        break;

    case GameState::Playing:
        if (newState == GameState::Paused || newState == GameState::GameOver)
        {
            currentState = newState;
            success = true;
        }
        break;

    case GameState::Paused:
        if (newState == GameState::Playing || newState == GameState::MainMenu)
        {
            currentState = newState;
            success = true;
        }
        break;

    case GameState::GameOver:
        if (newState == GameState::MainMenu)
        {
            currentState = newState;
            success = true;
        }
        break;
    }

    if (!success)
    {
        stateTransitionError(currentState, newState);
    }
    else 
    {
		log("Transitioned to GameState: " + std::to_string(static_cast<int>(newState)) + ", From GameState: " + std::to_string(static_cast<int>(previousState)), STATE);
    }

    previousState = newState;
}




GameState GameStateManager::getState() const
{
    return currentState;
}

bool GameStateManager::is(GameState state) const
{
    return currentState == state;
}

void StateManager::GameStateManager::stateTransitionError(GameState fromState, GameState toState)
{
    log("Unable to transition from GameState: " + std::to_string(static_cast<int>(fromState)) + ", to GameState: " + std::to_string(static_cast<int>(toState)), STATE);
}
