#pragma once
#include "Window.h"
#include "Scene.h"
#define MK_L 0 
#define MK_R 1
#define MK_C 2

namespace Engine
{
	namespace Components
	{
		__interface IInputHandler
		{
		public:
			virtual bool HandleKeys(BaseEngine* engine, Window* window, Scene* scene, Generic::Dictionary<short,bool>& keys, int keysActive) = 0;
			virtual bool HandleMouse(BaseEngine* engine, Window* window, Scene* scene, double x, double y, Generic::Dictionary<short, bool>& keys, int keysActive) = 0;
		};
	}
}
