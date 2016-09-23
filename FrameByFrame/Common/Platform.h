#pragma once


namespace Common {
#ifdef _WIN32
#define WINDOWS true
#define SLASH '\\'
#else
#define WINDOWS false
#define SLASH '/'

#endif // _WIN32

}


#ifdef _DEBUG
const bool DEBUG = true;
#else
const bool DEBUG = false;
#endif
