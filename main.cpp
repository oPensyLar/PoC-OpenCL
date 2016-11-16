#define __CL_ENABLE_EXCEPTIONS

#include <CL/cl.h>
#include <CL/opencl.h>
#include <stdio.h>


int main()
{

	cl_platform_id platform;	

	int err = clGetPlatformIDs(1, &platform, NULL);

	if(err<0)
	{
		printf("[!] OpenCL not available\n");
	}

		else
		{

			
			size_t strSiz;
			char *nam;
    		
    		cl_uint platformCount;	
    		cl_uint deviceCount;

			cl_device_id* devs;
    		cl_platform_id* platforms;						

			
			//Platform count.. 
			clGetPlatformIDs(0, NULL, &platformCount);		

			//Reserva mem suficiente para las platforms
			platforms = (cl_platform_id*) malloc(sizeof(cl_platform_id) * platformCount);

			clGetPlatformIDs(platformCount, platforms, NULL);

			//Enums todas las platforms
			for(int i=0; i<platformCount; i++)
			{
				//Enum  All devices
				clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &deviceCount);

				devs = (cl_device_id*) malloc(sizeof(cl_device_id) * deviceCount);				

				clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, deviceCount, devs, NULL);

				for (int j = 0; j < deviceCount; j++)
				{
					clGetDeviceInfo(devs[j], CL_DEVICE_NAME, 0, NULL, &strSiz);

					nam = (char*) malloc(strSiz);

					clGetDeviceInfo(devs[j], CL_DEVICE_NAME, strSiz, nam, NULL);            

            		printf("%d. Device: %sn", j+1, nam);
            		free(nam);
				}
			}

		}

	return 0;
}