# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Seminar7_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Seminar7_autogen.dir\\ParseCache.txt"
  "Seminar7_autogen"
  )
endif()
