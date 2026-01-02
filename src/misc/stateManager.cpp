#include "stateManager.hpp"

#include "../misc/programLogger.hpp"
using ProgramLogger::log;
using ProgramLogger::LogLevel;
using LogLevel::STATE;


using namespace StateManager;

static bool success = false;
static GameState currentState = GameState::NONE;
static GameState previousState = GameState::NONE;


void(*func)();


bool StateManager::GameStateManager::registerRenderLoadingScreenCallback(void(*_func)())
{
    if (!_func) 
    {
        log("Failed to register loading screen render callback: function pointer is null", STATE);
		return false;
    }
	// Store the callback function pointer
	func = _func;
    func();
    return true;
}

void StateManager::GameStateManager::proccessStateTransition()
{
    // Handle any additional logic needed during state transitions here.
    // For example, initializing resources when entering PLAYING state,
    // or cleaning up when leaving it.

    switch (currentState)
    {
    case GameState::LOADING:
        // Initialize loading resources
        log("LOADING GAME DATA");
        func();
        break;
    case GameState::MAIN_MENU:
        // Setup main menu
        break;
    case GameState::PLAYING:
        // Start game logic
        break;
    case GameState::PAUSED:
        // Pause game logic
        break;
    case GameState::GAME_OVER:
        // Handle game over logic
        break;
    default:
        break;
	}
}

void GameStateManager::setState(GameState newState)
{
	// reset success flag to false
	success = false;

    // Prevent redundant transitions
    if (currentState == newState)
        return;

	

    switch (currentState)
    {
    case GameState::NONE:
        if (newState == GameState::MAIN_MENU || newState == GameState::LOADING) 
        {
            currentState = newState;
			success = true;
        }
        break;

    case GameState::LOADING:
        if (newState == GameState::MAIN_MENU || newState == GameState::PLAYING)
        {
            currentState = newState;
			success = true;
        }
        break;

    case GameState::MAIN_MENU:
        if (newState == GameState::PLAYING)
        {
            currentState = newState;
			success = true;
        }
        break;

    case GameState::PLAYING:
        if (newState == GameState::PAUSED || newState == GameState::GAME_OVER)
        {
            currentState = newState;
            success = true;
        }
        break;

    case GameState::PAUSED:
        if (newState == GameState::PLAYING || newState == GameState::MAIN_MENU)
        {
            currentState = newState;
            success = true;
        }
        break;

    case GameState::GAME_OVER:
        if (newState == GameState::MAIN_MENU)
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
        log("Transitioned from GameState: " + std::to_string(static_cast<int>(previousState)) + ", To GameState: " + std::to_string(static_cast<int>(newState)), STATE);
		proccessStateTransition();
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
