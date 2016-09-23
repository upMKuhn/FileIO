#pragma once
#include <OpenCLFrame\Platform\Platform.h>

namespace OpenCLFrame::Platform {

	class CL_Context : public IOperational
	{
	public:
		CL_Context(CL_Device& deviceUsed);
		CL_Context(std::vector<CL_Device*> devicesUsed);


		~CL_Context();

		bool IsOperational() override;
		operator std::vector<CL_Device*>() { return m_devices; }
		operator cl_context() const {
			return m_context;
		}
	private:

		std::vector<CL_Device*> m_devices;
		cl_context m_context;
		cl_int m_contextState = CL_SUCCESS ;
	};

}

