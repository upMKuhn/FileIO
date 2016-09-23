#include <OpenCLFrame\Platform\Platform.h>


namespace OpenCLFrame::Platform {


	CL_Context::CL_Context(CL_Device& deviceUsed)
	{
		cl_device_id ar[1] = { deviceUsed };
		m_devices.push_back(&deviceUsed);
		m_context = clCreateContext(0, 1, &ar[0], NULL, NULL, &m_contextState);
	}

	CL_Context::CL_Context(std::vector<CL_Device*> devicesUsed)
		: m_devices(devicesUsed)
	{
		int i = 0;
		cl_device_id* arr = new cl_device_id[m_devices.size()];
		for (CL_Device* id : m_devices)
			arr[i++] = *id;
			
		m_context = clCreateContext(0, m_devices.size(), &arr[0], NULL, NULL, &m_contextState);
	}

	CL_Context::~CL_Context()
	{
		clReleaseContext(m_context);
	}

	bool CL_Context::IsOperational()
	{
		return m_contextState == CL_SUCCESS;
	}
	

}
