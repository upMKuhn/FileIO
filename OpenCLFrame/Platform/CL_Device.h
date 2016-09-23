#pragma once
#include <OpenCLFrame\Platform\Platform.h>

enum DeviceType {DEVICE_CPU = CL_DEVICE_TYPE_CPU, DEVICE_GPU = CL_DEVICE_TYPE_GPU};


namespace OpenCLFrame::Platform 
{

	class CL_Device : public IOperational
	{
	public:
		CL_Device();
		CL_Device(cl_device_id id);
		~CL_Device();

		bool IsOperational() override { return true; }
		operator cl_device_id() { return m_deviceId; }
		operator const cl_device_id*() { return &m_deviceId; }

		cl_int setDeviceId(cl_device_id id);
		cl_device_id getDeviceId();


		std::string getName();
		std::string getTypeStr();
		DeviceType getType();
		std::string getVersion();
		std::string getVendor();
		
		std::string tostring();
		std::string tostring(int timesIndented);

		operator cl_device_id() const {
			return m_deviceId;
		}
	protected:

		cl_int fetchDeviceInfo(cl_device_id deviceId);

		cl_device_id m_deviceId;

		std::string m_name;
		int m_type; //deviceType
		std::string m_vendor;
		std::string m_version;

		unsigned long long m_localMemSize = 0;
		unsigned long long m_PrivateMemSize = 0;
		unsigned long long m_ConstantMemSize = 0;
		unsigned long long m_GlobalMemSize = 0;

	};

	std::string DeviceTypeToString(int deviceType);

}

