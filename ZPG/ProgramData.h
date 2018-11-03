#pragma once
#include "Dictionary.h"
#include "Shader.h"

template <typename T>
class ProgramData
{
public:
	ProgramData()
	{
		Values = new Generic::Dictionary<ProgramData*, T>();
	}
	~ProgramData()
	{
		delete Values;
	}
	Generic::Dictionary<ProgramData*, T>* Values;
};

