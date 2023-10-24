set(target_name llvmgraph)

file(GLOB_RECURSE LIBLLVMGRAPH_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

file(GLOB_RECURSE LIBLLVMGRAPH_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

add_library(${target_name} STATIC ${LIBLLVMGRAPH_SOURCE_FILES} ${LIBLLVMGRAPH_HEADER_FILES})

include(CompileOptions)
set_compile_options(${target_name})

target_link_libraries(${target_name} PRIVATE fmt)

target_include_directories(${target_name} PRIVATE ${LLVM_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/src)

llvm_map_components_to_libnames(llvm_libs support core irreader analysis)