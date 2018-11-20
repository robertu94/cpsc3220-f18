#define __CL_ENABLE_EXCEPTIONS
#include <CL/cl.hpp>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

template <class T = float>
void
run_on_device(cl::Context context, cl::Program::Sources sources)
{
  std::vector<cl::Device> devices = context.getInfo<CL_CONTEXT_DEVICES>();
  auto device = devices.front();

  cl::Program program(context, sources);
  try {
    program.build(devices);
  } catch (cl::Error e) {
    auto log = program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device);
    std::cerr << log << std::endl;
    throw;
  }

  cl::CommandQueue queue(context, device);
  cl::Kernel compute_pi(program, "compute_pi");
  auto const work_group_size =
		device.getInfo<CL_DEVICE_MAX_WORK_GROUP_SIZE>();
  size_t const steps = work_group_size*1000;
  auto num_work_groups = steps / work_group_size;
  std::vector<T> results(num_work_groups);
  cl::Buffer buffer(context, CL_MEM_WRITE_ONLY|CL_MEM_COPY_HOST_PTR, sizeof(T)*results.size(), results.data());

  T step = 1.0 / steps;

  compute_pi.setArg(0, step);
  compute_pi.setArg(1, cl::LocalSpaceArg{ sizeof(T) * work_group_size });
  compute_pi.setArg(2, buffer);

  cl::Event event;
  std::vector<cl::Event> kernel_event(1);
  queue.enqueueNDRangeKernel(compute_pi,
                             /*offset*/ cl::NullRange,
                             /*global*/ cl::NDRange(steps),
                             /*local size*/ cl::NDRange(work_group_size),
                             /*input events*/ nullptr,
                             /*output event*/ &kernel_event[0]);
  queue.enqueueReadBuffer(buffer, CL_TRUE, 0, sizeof(T) * num_work_groups,
                          results.data(), &kernel_event, &event);
  T result =
    step * std::accumulate(std::begin(results), std::end(results), 0.0);
  event.wait();
  std::cout << result << std::endl;
}

int
main(int argc, char* argv[])
{
  std::vector<cl::Platform> platforms;
  std::vector<cl::Device> devices;

  try {

    cl::Platform::get(&platforms);
    for (auto platform : platforms) {
			try{
				platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);
			} catch(cl::Error const& e) {
				continue;
			}

			std::cout << platform.getInfo<CL_PLATFORM_NAME>() << " ";

      cl::Context context(devices);

      std::string program_source(R"(
		#define T double
		#pragma OPENCL EXTENSION cl_khr_fp64
		kernel void compute_pi(T step, __local T* local_mem, __global T *pi)
		{
			//get global and local ids
			size_t global_id = get_global_id(0);
			size_t local_id = get_local_id(0);

			//compute pi element
			T x = (global_id - 0.5) * step;
			local_mem[local_id] =  (4.0/(1.0 + x * x));

			//wait for rectangle to be computed
			barrier(CLK_LOCAL_MEM_FENCE);

			//preform parallel reduction
			size_t local_size = get_local_size(0);
			for(int i = (local_size >> 1); i > 0; i >>= 1)
			{
				if(local_id < i)
				{
					local_mem[local_id] += local_mem[local_id + i];
				}
				barrier(CLK_LOCAL_MEM_FENCE);
			}

			//write to global memory
			size_t group_id = get_group_id(0);
			if(local_id == 0)
			{
				pi[group_id] = local_mem[0];
			}
		}
	)");

      cl::Program::Sources sources( 1, std::make_pair(program_source.c_str(),
                                                   program_source.size() + 1) );

      // run_on_device(gpu_context);
      run_on_device<double>(context, sources);
    }

  } catch (cl::Error const& error) {
    std::cout << error.what() << " " << error.err() << std::endl;
  }

  return 0;
}

