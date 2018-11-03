#pragma once
#include <string>
#include "Shader.h"
#include "MaterialValueType.h"
#include "Observer.h"
#include "Observable.h"

namespace Engine
{
	namespace Components
	{
		namespace Graphics
		{
			template<class T>
			class MaterialBindedValue : public Observer<T>
			{
			public:
				MaterialBindedValue(Shader* shader, const GLchar* property, MaterialValueType type, Observable<T> *observable, void* value)
				{
					Shader = shader;
					Property = property;
					Type = type;
					Observable = observable;
					Value = value;
				}
				Shader* Shader;
				const GLchar* Property;
				MaterialValueType Type;
				Observable<T>* Observable;
				void* Value;
			};
		}
	}
}

