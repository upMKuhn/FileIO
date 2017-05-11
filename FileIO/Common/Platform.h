#pragma once


#ifdef _WIN32
	#define FILEIO_WINDOWS true
	#define FILEIO_SLASH '\\'
#else
	#define FILEIO_WINDOWS false
	#define FILEIO_SLASH '/'
#endif //windows

#ifdef _DEBUG
const bool DEBUG = true;
#else
const bool DEBUG = false;
#endif
