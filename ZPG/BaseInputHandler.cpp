#include "BaseInputHandler.h"

bool Engine::Components::BaseInputHandler::HandleKeys(BaseEngine* engine, Window* window, Scene* scene, Generic::Dictionary<short, bool>& keys, int keysActive)
{
	return true;
}

bool Engine::Components::BaseInputHandler::HandleMouse(BaseEngine* engine, Window* window, Scene* scene, double x, double y, Generic::Dictionary<short, bool>& keys, int keysActive)
{
	return true;
}
