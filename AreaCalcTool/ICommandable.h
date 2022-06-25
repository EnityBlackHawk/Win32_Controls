#pragma once
#include <Windows.h>
#include <unordered_map>
#include "Element.h"


typedef void (__stdcall* EVENT)(Element*);

class ICommandable
{
public:
	virtual void AddEvent(int windowMessage, EVENT pEvent)
	{
		commands[windowMessage] = pEvent;
	}
	virtual void RaiseEvent(int windowMessage) = 0;

protected:
	std::unordered_map<int, EVENT> commands;
};