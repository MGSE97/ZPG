#pragma once
#include "Dictionary.h"
#include "Object.h"
#include "Camera.h"
#include "Light.h"
#include "Mesh.h"

namespace Engine {
	class BaseEngine;
}

namespace Engine
{
	namespace Components
	{
		class Scene
		{
		protected:
			bool Loaded;
		public:
			Scene();
			~Scene();
			virtual void Load(BaseEngine* engine);
			virtual void Unload(BaseEngine* engine);
			virtual void BeginLoad(BaseEngine* engine);
			virtual void FrameUpdate(BaseEngine* engine);
			virtual void SetActiveCamera(Camera* camera = nullptr);
			Generic::Dictionary<std::string, Engine::Objects::Object*>* Objects;
			Generic::Dictionary<std::string, Objects::Mesh*>* Meshes;
			Generic::Dictionary<std::string, Camera*>* Cameras;
			Generic::Dictionary<std::string, Light*>* Lights;
			Camera* ActiveCamera;
		};
	}
}

