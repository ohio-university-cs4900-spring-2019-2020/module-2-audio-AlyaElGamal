#----------------------------------------------------------------
# Generated CMake target import file for configuration "MinSizeRel".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "AftrBurnerEngine" for configuration "MinSizeRel"
set_property(TARGET AftrBurnerEngine APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(AftrBurnerEngine PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_MINSIZEREL "CXX"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/lib64/AftrBurnerEngine.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS AftrBurnerEngine )
list(APPEND _IMPORT_CHECK_FILES_FOR_AftrBurnerEngine "${_IMPORT_PREFIX}/lib64/AftrBurnerEngine.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
