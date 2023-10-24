#pragma once

#include <llvm/IR/Module.h>

namespace llvmgraph {

std::string build_callgraph(llvm::Module *module);

}; // namespace llvmgraph