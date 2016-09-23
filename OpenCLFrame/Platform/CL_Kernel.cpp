#include <OpenCLFrame\Platform\Platform.h>
#include <stdarg.h>
#include <string>
#include <vector>
#include <algorithm>
using namespace OpenCLFrame::Platform;
CL_Kernel& CL_Kernel::arg(CL_BufferBase& buffer, int argIndex)
{
	assert(buffer.IsOperational());
	cl_int err = clSetKernelArg(*this, argIndex, sizeof(cl_mem), (void *)buffer.getMem());
	m_state = err == 0 ? m_state : err;
	return *this;
}

