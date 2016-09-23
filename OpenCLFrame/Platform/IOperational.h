#pragma once
#include <OpenCLFrame\Platform\Platform.h>
class IOperational abstract
{
public:
	IOperational() {}
	virtual ~IOperational() {}

	virtual bool IsOperational() abstract;
	operator bool()
	{
		return IsOperational();
	}
};

