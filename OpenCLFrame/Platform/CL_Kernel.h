#pragma once
#pragma once
#include <OpenCLFrame\Platform\Platform.h>
#include <functional>
namespace OpenCLFrame::Platform {

	class CL_Kernel : public IOperational
	{
	public:
		CL_Kernel(const char* name, CL_Program& program): m_program(program)
		{
			assert(program);
			NAME = name;
			m_kernel = clCreateKernel(program, name, &m_state);
		}

		~CL_Kernel() { clReleaseKernel(m_kernel); }

		CL_Kernel& arg(CL_BufferBase& buffer, int argIndex);


		inline operator cl_kernel() {return m_kernel;}

		bool IsOperational() override { return m_state == CL_SUCCESS; }
		const char* NAME;
	private:
		cl_int m_state;
		cl_kernel m_kernel;
		CL_Program& m_program;
	};

}
