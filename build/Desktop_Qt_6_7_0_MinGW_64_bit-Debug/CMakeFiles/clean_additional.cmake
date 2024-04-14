# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\PwdManager_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\PwdManager_autogen.dir\\ParseCache.txt"
  "PwdManager_autogen"
  )
endif()
