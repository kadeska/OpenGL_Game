#pragma once

namespace StateManager
{
    enum class GameState
    {
        None,
        MainMenu,
        Playing,
        Paused,
        GameOver
    };

    class GameStateManager
    {
    public:
        void setState(GameState newState);
        GameState getState() const;

        bool is(GameState state) const;

    private:
        GameState currentState = GameState::None;
    };
}
