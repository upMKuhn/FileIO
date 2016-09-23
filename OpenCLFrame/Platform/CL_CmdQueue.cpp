#include <OpenCLFrame\Platform\Platform.h>


namespace OpenCLFrame::Platform {
	
	CL_CmdQueue::CL_CmdQueue(CL_Device & device, CL_Context & context)
	{
		m_queue = clCreateCommandQueue(context, device, 0, &m_QueueState);
	}

	CL_CmdQueue::~CL_CmdQueue()
	{
		clReleaseCommandQueue(m_queue);
	}

	bool CL_CmdQueue::IsOperational() { return m_QueueState == CL_SUCCESS; }

	cl_int CL_CmdQueue::enqueueKernel(CL_Kernel & kernel, const size_t globalworkSize)
	{
		assert(kernel);
		size_t globalWorkSize[2] = { 10, 10 };
		size_t localWorkSize[2] = { 1, 1 };
		cl_int err = clEnqueueNDRangeKernel(this->m_queue, kernel, 2, NULL, globalWorkSize, 0, 0, NULL, NULL);
		clFinish(m_queue);
		return err;
	} 

	
}