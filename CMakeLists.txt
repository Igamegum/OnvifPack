#Set the cmake version
cmake_minimum_required (VERSION 3.0)
project(OnvifPack)



#Set the compiled version type
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -std=c++11 -DWITH_OPENSSL")

## Set compiler if need
set(CMAKE_CXX_COMPILER "g++-5")

#set the output path
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)



### soap
include_directories(${CMAKE_SOURCE_DIR}/include/gsoap/soap)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/gsoap/soap soap_src)

### soap_client
include_directories(${CMAKE_SOURCE_DIR}/include/gsoap/soap/client)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/gsoap/soap/client soap_client_src)

### plugin
include_directories(${CMAKE_SOURCE_DIR}/include/gsoap/plugin)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/gsoap/plugin plugin_src)


### sourcecode
aux_source_directory(${CMAKE_SOURCE_DIR} sourcecode_root)

### onvifpack
include_directories(${CMAKE_SOURCE_DIR}/include/onvifpack)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/onvifpack onvifpack_src)

#Compile the executable program.
set(sourcecode 
	${sourcecode_root} 
	${soap_src}
	${soap_client_src}
	${plugin_src}  
	${onvifpack_src}  
    )


#message(STATUS "All CPPFile is "　${sourcecode})


add_executable(Demo ${sourcecode} )

#Link dynamic library
target_link_libraries(Demo  ssl crypto)




