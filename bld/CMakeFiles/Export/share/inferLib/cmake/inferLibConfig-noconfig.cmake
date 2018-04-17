#----------------------------------------------------------------
# Generated CMake target import file for configuration "".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "inferLib" for configuration ""
set_property(TARGET inferLib APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(inferLib PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_NOCONFIG "/usr/local/cuda/lib64/libcudart.so;/home/fares/TensorRT/lib/libnvcaffe_parser.so;/home/fares/TensorRT/lib/libnvinfer.so;/home/fares/TensorRT/lib/libnvinfer_plugin.so;/home/fares/TensorRT/lib/libnvparsers.so"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/inferLib/libinferLib.so"
  IMPORTED_SONAME_NOCONFIG "libinferLib.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS inferLib )
list(APPEND _IMPORT_CHECK_FILES_FOR_inferLib "${_IMPORT_PREFIX}/lib/inferLib/libinferLib.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
