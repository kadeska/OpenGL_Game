#pragma once

namespace StateManager {
    enum class GameState {
        NONE,
        LOADING,
        MAIN_MENU,
        PLAYING,
        PAUSED,
        GAME_OVER,
        COUNT
    };

    const char* toString(GameState state);

    class GameStateManager {
    public:
        using StateCallback = void (*)();

        void setState(GameState newState);
        GameState getState() const;
        GameState getPreviousState() const;
        bool is(GameState state) const;

        void onEnter(GameState state, StateCallback callback);
        void onExit(GameState state, StateCallback callback);

    private:
        GameState currentState = GameState::NONE;
        GameState previousState = GameState::NONE;

        StateCallback enterCallbacks[(int)GameState::COUNT] = {};
        StateCallback exitCallbacks[(int)GameState::COUNT] = {};

        bool isValidTransition(GameState from, GameState to);
    };

}
