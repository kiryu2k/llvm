#include <libllvmgraph/callgraph.hpp>

#include <fmt/format.h>

#include <sstream>
#include <unordered_set>

#include <llvm/IR/InstIterator.h>
#include <llvm/IR/Instructions.h>

namespace llvmgraph {

std::string build_callgraph(llvm::Module *module) {
    if (module == nullptr) {
        return "";
    }
    std::stringstream res;
    for (const auto &func : module->functions()) {
        std::unordered_set<std::string_view> callee_set;
        for (auto i = llvm::inst_begin(func); i != llvm::inst_end(func); ++i) {
            if (!llvm::isa<llvm::CallInst>(*i)) {
                continue;
            }
            const auto callee =
                llvm::cast<llvm::CallInst>(*i).getCalledFunction()->getName();
            if (callee_set.contains(std::string_view(callee.data()))) {
                continue;
            }
            res << fmt::format(
                "{} -> {};\n", func.getName().data(), callee.data());
            callee_set.insert(std::string_view(callee.data()));
        }
    }
    return res.str();
}

} // namespace llvmgraph