#pragma once
#include <OpenCLFrame\Platform\Platform.h>

namespace OpenCLFrame::Platform {

	class CL_Program : public IOperational
	{
	public:
		//TO_DO
		//Build program according to OPEN_CL version 
		CL_Program(FIO::VPath filePath, CL_Context& context, std::vector<FIO::Path> includeFolders);
		~CL_Program() { clReleaseProgram(m_program); }
		bool IsOperational() override { return m_state == CL_SUCCESS; }
		operator cl_program() { return m_program; }

		bool Build(CL_Device device)
		{ 
			std::vector<CL_Device*> vec;
			vec.push_back(&device);
			return Build(vec);
		}

		bool Build(std::vector<CL_Device*> devices);
		

	private:
		void createProgram(FIO::VPath& filePath, CL_Context& context);
		void logBuildError(CL_Device& device);

		/*Generate appropriate build options for the device and debug situations*/
		std::string getBuildOptions(CL_Device* dev = nullptr);

		FIO::Path sourceFolder;
		std::vector<FIO::Path> m_includeFolders;
		cl_program m_program;
		cl_int m_state;
	};

}
