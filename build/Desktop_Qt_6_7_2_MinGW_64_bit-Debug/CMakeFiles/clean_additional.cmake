# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\GUI_Calculator_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\GUI_Calculator_autogen.dir\\ParseCache.txt"
  "GUI_Calculator_autogen"
  )
endif()
