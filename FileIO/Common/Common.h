#pragma once

#include <vector>
#include <functional>
#include <algorithm>

#include "StringBuilder.h"
#include "NiceHelper.hpp"
#include "BurpPointer.hpp"
#include "Tree.hpp"
#include "Platform.h"


#ifdef FILEIO_PROJECT
	#define FILEIO_API __declspec( dllexport )
#else
	#define FILEIO_API __declspec( dllimport )
#endif 


