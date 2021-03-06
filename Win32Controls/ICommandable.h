#pragma once
#include <Windows.h>
#include <unordered_map>
#include "Element.h"


typedef void (__stdcall* EVENT)(Element*);

class ICommandable
{
public:
	/// <summary>
	/// Bind a function to be called when a message has been sent
	/// </summary>
	/// <param name="windowMessage">Window message identifier</param>
	/// <param name="pEvent">Event function pointer</param>
	virtual void AddEvent(int windowMessage, EVENT pEvent)
	{
		commands[windowMessage] = pEvent;
	}

	/// <summary>
	/// Remove a function binded
	/// </summary>
	/// <param name="windowMessage"> Window message identifier</param>
	virtual void RemoveEvent(int windowMessage)
	{
		commands.extract(windowMessage);
	}

	/// <summary>
	/// The function raised will overwrite the original
	/// </summary>
	/// <param name="value"></param>
	virtual void OverwriteProcedures(bool value)
	{
		overwriteProc = value;
	}

	/// <summary>
	/// Call the event function
	/// </summary>
	/// <param name="windowMessage">Window message identifier</param>
	virtual void RaiseEvent(int windowMessage) = 0;

protected:
	std::unordered_map<int, EVENT> commands;
	bool overwriteProc = false;
};