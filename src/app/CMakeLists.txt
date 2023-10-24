set(target_name app)

add_executable(${target_name})

include(CompileOptions)
set_compile_options(${target_name})

target_sources(
  ${target_name}
  PRIVATE
    main.cpp
)

target_include_directories(
  ${target_name}
  PRIVATE
    ${LLVM_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/src
)

llvm_map_components_to_libnames(llvm_libs support core irreader analysis)

target_link_libraries(
  ${target_name}
  PRIVATE
    ${llvm_libs}
    fmt
    llvmgraph
)