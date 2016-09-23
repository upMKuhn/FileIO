#pragma once
#include <OpenCLFrame\Platform\Platform.h>

namespace OpenCLFrame::Platform {

	class CL_Kernel;
	template<typename T> class CL_Buffer;
	class CL_CmdQueue : public IOperational
	{
	public:
		CL_CmdQueue(CL_Device& device, CL_Context& context);
		~CL_CmdQueue();
		
		bool IsOperational() override;
		operator cl_command_queue() { return m_queue; }
		cl_int enqueueKernel(CL_Kernel& kernel, const size_t globalworkSize);
		
		template<typename T>
		T* enqueueMapRead(CL_Buffer<T>& buffer, cl_int* error);

	private:
		cl_int m_QueueState = CL_SUCCESS;
		cl_command_queue m_queue;
	};

	template<typename T>
	inline T * CL_CmdQueue::enqueueMapRead(CL_Buffer<T>& buffer, cl_int * error)
	{
		cl_int reserve = 0;
		if (error == nullptr)
			error = &reserve;
		T *resultPtr = (T *)clEnqueueMapBuffer(*this, buffer, true, CL_MAP_READ, 0, buffer.size(), 0, NULL, NULL, error);
		clFinish(*this);
		return resultPtr;
	}

}

