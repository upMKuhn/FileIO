#pragma once
#include <OpenCLFrame\Platform\Platform.h>

namespace OpenCLFrame::Platform {

	class CL_Session
	{
	public:
		static CL_Platform find_platform(DeviceType type)
		{
			using namespace std; using namespace OpenCLFrame::Platform;

			const char PLATFORM_LS_LEN = 5;
			cl_platform_id platformLs[PLATFORM_LS_LEN];
			cl_uint platformLsActualLen = 0;
			clGetPlatformIDs(PLATFORM_LS_LEN, &platformLs[0], &platformLsActualLen);

			while (platformLsActualLen-- > 0)
			{
				CL_Platform platform(platformLs[platformLsActualLen]);
				if (platform.hasDeviceType(type))
					return platform;
			}
			return CL_Platform();
		}

		static CL_Platform find_platform(DeviceType type, const char * version)
		{
			using namespace std; using namespace OpenCLFrame::Platform;

			const char PLATFORM_LS_LEN = 5;
			cl_platform_id platformLs[PLATFORM_LS_LEN];
			cl_uint platformLsActualLen = 0;
			clGetPlatformIDs(PLATFORM_LS_LEN, &platformLs[0], &platformLsActualLen);

			while (platformLsActualLen-- > 0)
			{
				CL_Platform platform(platformLs[platformLsActualLen]);
				if (platform.hasDeviceType(type) && platform.getVersion().compare(version))
					return platform;
			}
			return CL_Platform();
		}
	
	};

}