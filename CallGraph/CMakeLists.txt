# set the plugin name here
set(PLUGIN_NAME "CallGraph")

# Our project is called 'plugin' this is how it will be called in visual studio, and in our makefiles.
project(${PLUGIN_NAME})

# It was noticed that when using MinGW gcc it is essential that 'core' is mentioned before 'base'.

# wxWidgets include (this will do all the magic to configure everything)
include("${wxWidgets_USE_FILE}")

if(USE_PCH)
    add_definitions(-include "${CL_PCH_FILE}")
    add_definitions(-Winvalid-pch)
endif(USE_PCH)

file(GLOB SRCS "*.cpp")

# Define the output
add_library(${PLUGIN_NAME} SHARED ${SRCS})

if(UNIX OR APPLE)
    set_target_properties(${PLUGIN_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()

# Remove the "lib" prefix from the plugin name
set_target_properties(${PLUGIN_NAME} PROPERTIES PREFIX "")
target_link_libraries(${PLUGIN_NAME} ${LINKER_OPTIONS} -L"${CL_LIBPATH}" libcodelite plugin)
# Make sure that the plugin will not start build before 'plugin.so' is ready
add_dependencies(${PLUGIN_NAME} plugin)

if(UNIX AND NOT APPLE)
    install(TARGETS ${PLUGIN_NAME} DESTINATION ${PLUGINS_DIR})
endif()
