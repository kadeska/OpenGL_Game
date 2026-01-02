#pragma once

namespace StateManager
{
    enum class GameState
    {
        NONE,
        LOADING,
        MAIN_MENU,
        PLAYING,
        PAUSED,
        GAME_OVER
    };

    class GameStateManager
    {
    private:
		void proccessStateTransition();
    public:
        bool registerRenderLoadingScreenCallback(void(*func)());
        bool registerRenderMainMenuCallback(void(*func)());
        bool registerRenderWorldCallback(void(*func)());

        void setState(GameState newState);
        GameState getState() const;

        bool is(GameState state) const;
		void stateTransitionError(GameState fromState, GameState toState);
        

    };
}
