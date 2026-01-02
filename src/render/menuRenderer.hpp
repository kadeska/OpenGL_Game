#pragma once
class MenuRenderer
{
public:
	MenuRenderer();
	~MenuRenderer() = default;

	void renderMainMenu();
	void renderPauseMenu();
	void renderLoadingScreen();
	void renderGameOverScreen();
};

