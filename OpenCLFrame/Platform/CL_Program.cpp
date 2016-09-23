#include <OpenCLFrame\Platform\Platform.h>
#include <FrameByFrame\IO\IO.h>
using namespace FIO;
namespace OpenCLFrame::Platform {

	CL_Program::CL_Program(FIO::VPath filePath, CL_Context& context, std::vector<Path> includeFolders)
		: m_includeFolders(includeFolders)

	{
		createProgram(filePath, context);
	}


	void CL_Program::createProgram(FIO::VPath& filePath, CL_Context& context)
	{
		assert(context.IsOperational());
		sourceFolder = VFS::Get()->Resolve(filePath);
		TextFile source(filePath);
		const char * p = sourceFolder;
		source.ReadToEnd();
		const char* file = source;
		size_t sizes = source.size();
		m_program = clCreateProgramWithSource(context, 1, &file, &sizes, &m_state);
	}

	bool CL_Program::Build(std::vector<CL_Device*> devices)
	{
		cl_int errors = 0;

		for (CL_Device* device : devices)
		{
			errors = clBuildProgram(m_program, devices.size(), *device, getBuildOptions().c_str(), NULL, NULL);
			if (errors != CL_SUCCESS)
				m_state = errors;
			logBuildError(*device);
		}
		return true;
	}

	void CL_Program::logBuildError(CL_Device& device)
	{
		if (m_state == CL_BUILD_PROGRAM_FAILURE)
		{
			size_t log_size = 0;
			clGetProgramBuildInfo(m_program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
			char* build_log = new char [log_size];
			std::fill_n(build_log, log_size, NULL);
			clGetProgramBuildInfo(m_program, device, CL_PROGRAM_BUILD_LOG, log_size, &build_log[0], NULL);

			printf("Error happened during the build of OpenCL program.\nBuild log: \n");
			for (int i = 0; i < log_size; i++)
				std::cout << build_log[i];
			console_wait_for_key();
		}
	}

	std::string CL_Program::getBuildOptions(CL_Device* dev)
	{
		std::string str;
		if (DEBUG)
		{
			str.append("-g -s ");
			str.append("\"").append(sourceFolder.c_str()).append("\" ");
		}
		Path homeFolder(sourceFolder);
		homeFolder = homeFolder.directory();
		str = str.append("-I \"").append(homeFolder.c_str()).append("\" ");

		for (Path p : m_includeFolders)
		{
			FIO::FileSystem::get()->resolve(p);
			str = str.append("-I \"").append(Path::Combine(homeFolder, p).c_str()).append("\" ");
		}
		return str;
	}

}
