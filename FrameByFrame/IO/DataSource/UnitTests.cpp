#include <FrameByFrame\IO\FileTypes\Filetypes.h>
using namespace FrameByFrame::IO;
#ifdef UNIT_TESTS
std::function<FileSystem*()> FileSystem::filesystemFactory;
#endif