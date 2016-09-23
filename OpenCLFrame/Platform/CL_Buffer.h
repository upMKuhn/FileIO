#pragma once
#include <OpenCLFrame\Platform\Platform.h>
#include <functional>
namespace OpenCLFrame::Platform {

	enum Buffer_Mode 
	{
		READ_ONLY = 1,
		WRITE_ONLY = 2,
		READ_WRITE = READ_ONLY | WRITE_ONLY
	};

	class CL_BufferBase : IOperational{
	public:

		virtual size_t size() abstract;
		inline operator void*() { return dataptr; }
		virtual bool IsOperational() abstract;
		virtual cl_mem* getMem() abstract;
		void* dataptr;
	};

	template<typename T>
	class CL_Buffer : public IOperational, public CL_BufferBase
	{
	public:
		CL_Buffer(const char* name , Buffer_Mode mode, CL_Context& context)  
			: m_context(context), NAME(name)
		{
			this->mode = mode;
			dataptr = ((void*)m_data);
		}
		~CL_Buffer() 
		{
			if(mode == WRITE_ONLY)
				clReleaseMemObject(buffer); 
		}

		inline operator CL_Buffer<void*>&() { return *this; }
		inline operator cl_mem() {return buffer;}
		inline size_t size() override { return m_size * sizeof(T); }
		inline operator size_t() { return m_size * sizeof(T); }
		inline cl_mem* getMem() override { return &buffer; };

		bool IsOperational() override { return m_state == CL_SUCCESS; }
		const char* NAME;
		Buffer_Mode mode;
		
		void data(T* d, size_t size) { 
			m_data = d; 
			m_size = size; 
			buffer = clCreateBuffer(m_context, modeToFlag(), sizeof(T) * (m_size), m_data, &m_state);
			dataptr = m_data;
		}

		T* data() { return m_data; }

	private:
		T* m_data = nullptr;
		size_t m_size = 0;

		cl_int m_state = 0; 
		cl_mem_flags modeToFlag()
		{
			cl_mem_flags  f = 0;
			f = mode == READ_ONLY ?  CL_MEM_READ_ONLY  | CL_MEM_ALLOC_HOST_PTR | CL_MEM_COPY_HOST_PTR : f;
			f = mode == WRITE_ONLY ? CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR : f;
			f = mode == READ_WRITE ? CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR : f;
			return f;
		}
		CL_Context& m_context;
		cl_mem buffer = 0;
	};

}
