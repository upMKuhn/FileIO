#pragma once
#include <OpenCLFrame\Platform\Platform.h>

namespace OpenCLFrame::Platform
{
	class CL_Platform
	{
	public:
		CL_Platform();
		CL_Platform(cl_platform_id platformId);
		~CL_Platform();

		cl_uint set_PlatformId(cl_platform_id platformId);
		cl_platform_id getPlatformId();

		CL_Device& GetFirstDevice();
		CL_Device& GetFirstDevice(DeviceType type);


		bool hasDeviceType(DeviceType type) 
		{
			for (CL_Device* dev : m_devices)
				if (dev->getType() == type)
					return true;
			return false;
		}

		int numDevices() { return sizeof(m_devices[0]) * sizeof(m_devices); }

		std::string getName();
		std::string getVersion();
		std::string getVendor();
		std::string getProfile();
		std::string getExtensions();
		
		std::string tostring();
		
	protected:

		cl_platform_id m_id;
		cl_uint fetchPlatformInfo(cl_platform_id id);
		cl_uint populateDeviceVector(cl_platform_id id);

		std::vector<CL_Device*> m_devices;
		std::string m_name;
		std::string m_version;
		std::string m_vendor;
		std::string m_profile;
		std::string m_extensions;
	};

}

