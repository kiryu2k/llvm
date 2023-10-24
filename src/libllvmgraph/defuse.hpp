#pragma once

#include <llvm/IR/Module.h>

namespace llvmgraph {

std::string build_defuse_graph(llvm::Module *module);

}; // namespace llvmgraph