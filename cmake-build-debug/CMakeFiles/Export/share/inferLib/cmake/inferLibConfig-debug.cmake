#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "inferLib" for configuration "Debug"
set_property(TARGET inferLib APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(inferLib PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "/usr/local/cuda/lib64/libcudart_static.a;-lpthread;dl;/usr/lib/x86_64-linux-gnu/librt.so;/home/fares/TensorRT/lib/libnvcaffe_parser.so;/home/fares/TensorRT/lib/libnvinfer.so;/home/fares/TensorRT/lib/libnvinfer_plugin.so;/home/fares/TensorRT/lib/libnvparsers.so"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/inferLib/libinferLib.so"
  IMPORTED_SONAME_DEBUG "libinferLib.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS inferLib )
list(APPEND _IMPORT_CHECK_FILES_FOR_inferLib "${_IMPORT_PREFIX}/lib/inferLib/libinferLib.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
