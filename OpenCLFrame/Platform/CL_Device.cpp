#include <OpenCLFrame\Platform\Platform.h>


using namespace std;
namespace OpenCLFrame::Platform {

	CL_Device::CL_Device()
	{}

	CL_Device::CL_Device(cl_device_id id)
	{setDeviceId(id);}

	CL_Device::~CL_Device()
	{
	}

	
	cl_int CL_Device::setDeviceId(cl_device_id id)
	{
		cl_int err = CL_SUCCESS;

		if (err == CL_SUCCESS)
			err = fetchDeviceInfo(id);

		m_deviceId = id;
		return err;
	}

	cl_device_id CL_Device::getDeviceId()
	{
		return m_deviceId;
	}

	string CL_Device::getVendor()
	{
		return m_vendor;
	}

	string CL_Device::getTypeStr()
	{
		return DeviceTypeToString(m_type);
	}
	
	DeviceType CL_Device::getType()
	{
		return DeviceType(m_type);
	}

	string CL_Device::getName()
	{
		return m_name;
	}

	string CL_Device::getVersion()
	{
		return m_version;
	}

	cl_int CL_Device::fetchDeviceInfo(cl_device_id deviceId)
	{
		char arr[100]; size_t size = 100;
		cl_int err = CL_SUCCESS;

		err = clGetDeviceInfo(deviceId, CL_DEVICE_VENDOR, 100, &arr[0], &size);
		m_vendor.assign(&arr[0], &arr[size]);
		err = clGetDeviceInfo(deviceId, CL_DEVICE_NAME, 100, &arr[0], &size);
		m_name.assign(&arr[0], &arr[size]);
		err = clGetDeviceInfo(deviceId, CL_DEVICE_TYPE, 100, &arr[0], &size);
		m_type = arr[0];
		err = clGetDeviceInfo(deviceId, CL_DEVICE_VERSION, 100, &arr[0], &size);
		m_version.assign(&arr[0], &arr[size]);
		err = clGetDeviceInfo(deviceId, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(long long), &m_GlobalMemSize, &size);
		err = clGetDeviceInfo(deviceId, CL_DEVICE_GLOBAL_MEM_CACHE_SIZE, sizeof(long long), &m_ConstantMemSize, &size);
		err = clGetDeviceInfo(deviceId, CL_DEVICE_LOCAL_MEM_SIZE, sizeof(long long), &m_localMemSize, &size);

		return err;
	}


	std::string CL_Device::tostring()
	{
		return tostring(0);
	}

	std::string byteSize_ToString(unsigned long long memory)
	{
		std::string str;
		double mem = memory;
		const char * units[] = { " bytes", "KB", "MB", "GB", "TB" };
		int unitAt = 0; const int MAX_UNIT = 4;
		while (mem > 1024 && ++unitAt < MAX_UNIT)
			mem /= 1024;
		return str.append(std::to_string(mem)).append(units[unitAt]);
	}

	std::string CL_Device::tostring(int timesIndented)
	{
		string indentation;
		indentation.clear();
		while (timesIndented-- > 0)
			indentation += '	';

		string str;
		str = str.append(indentation).append("Device: ").append(DeviceTypeToString(m_type)).append("\n");
		str = str.append(indentation).append("	").append(m_name);
		str = str.append(indentation).append(" V. ").append(m_version).append("\n");
		str = str.append(indentation).append("Global memory ").append(byteSize_ToString(m_GlobalMemSize)).append("\n");
		str = str.append(indentation).append("Cache size ").append(byteSize_ToString(m_ConstantMemSize)).append("\n");
		str = str.append(indentation).append("Local memory ").append(byteSize_ToString(m_localMemSize)).append("\n");

		return str;
	}

	std::string DeviceTypeToString(int deviceType)
	{
		switch (deviceType)
		{
		case CL_DEVICE_TYPE_CPU:
			return string("CPU");
		case CL_DEVICE_TYPE_GPU:
			return string("GPU");
		case CL_DEVICE_TYPE_CUSTOM:
			return string("CUSTOM");
		case CL_DEVICE_TYPE_ACCELERATOR:
			return string("ACCELERATOR");
		default:
			return "INVALID_DEVICE_TYPE";
		}
	}
}