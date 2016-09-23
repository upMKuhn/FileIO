#include <OpenCLFrame\Platform\Platform.h>

namespace OpenCLFrame::Platform
{
	using namespace std;
	
	CL_Platform::CL_Platform()
	{
		m_id = 0;
	}

	CL_Platform::CL_Platform(cl_platform_id platformId)
	{
		m_id = 0;
		set_PlatformId(platformId);
	}


	CL_Platform::~CL_Platform()
	{
		//for (CL_Device* dev : m_devices)
			//delete dev;
	}

	cl_platform_id CL_Platform::getPlatformId()
	{
		return m_id;
	}

	//Populate class with information about platform 
	cl_uint CL_Platform::set_PlatformId(cl_platform_id platformId)
	{
		cl_int err = CL_SUCCESS;

		if(err == CL_SUCCESS)
			err = fetchPlatformInfo(platformId);
		if (err == CL_SUCCESS)
			err = populateDeviceVector(platformId);
		
		//on any failures set information back to old id.
		if (err != CL_SUCCESS && m_id != NULL && m_id != platformId)
			set_PlatformId(m_id);
		else //Update ID after success
			m_id = platformId;

		return err;
	}

	CL_Device& CL_Platform::GetFirstDevice()
	{
		return *m_devices[0];
	}

	CL_Device& CL_Platform::GetFirstDevice(DeviceType type)
	{
		for (CL_Device* d : m_devices)
			if (d->getType() == type)
				return *d;
		return *m_devices[0];
	}

	string CL_Platform::getVendor()
	{
		return m_vendor;
	}

	string CL_Platform::getName()
	{
		return m_name;
	}

	string CL_Platform::getVersion()
	{
		return m_version;
	}

	string CL_Platform::getProfile()
	{
		return m_profile;
	}

	string CL_Platform::getExtensions()
	{
		return m_extensions;
	}

	cl_uint CL_Platform::fetchPlatformInfo(cl_platform_id platformId)
	{
		char arr[10000]; size_t size = 100;
		cl_int err = CL_SUCCESS;

		err = clGetPlatformInfo(platformId, CL_PLATFORM_VENDOR, 100, &arr[0], &size);
		m_vendor.assign(&arr[0], &arr[size]);
		err = clGetPlatformInfo(platformId, CL_PLATFORM_NAME, 100, &arr[0], &size);
		m_name.assign(&arr[0], &arr[size]);
		err = clGetPlatformInfo(platformId, CL_PLATFORM_PROFILE, 100, &arr[0], &size);
		m_profile.assign(&arr[0], &arr[size]);
		err = clGetPlatformInfo(platformId, CL_PLATFORM_VERSION, 100, &arr[0], &size);
		m_version = arr;
		err = clGetPlatformInfo(platformId, CL_PLATFORM_EXTENSIONS, 10000, &arr[0], &size);
		m_extensions = arr;

		return err;
	}

	cl_uint CL_Platform::populateDeviceVector(cl_platform_id platformId)
	{
		cl_uint err = CL_SUCCESS;
		cl_uint size = 100; cl_device_id devices[100];

		err = clGetDeviceIDs(platformId, CL_DEVICE_TYPE_ALL, size, &(devices[0]), &size);

		while (err == CL_SUCCESS && size-- > 0)
			m_devices.push_back(new CL_Device(devices[size]));
		return err;
	}

	std::string CL_Platform::tostring()
	{
		string str;
		str = str.append("Platform: ").append(getName()).append("\n");
		str = str.append("	Vendor- ").append(getVendor());
		str = str.append("	Version- ").append(getVersion()).append("\n");

		for (CL_Device* d : m_devices)
			str = str.append(d->tostring(2)).append("\n");


		return str;
	}

}