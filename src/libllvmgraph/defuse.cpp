#include <libllvmgraph/defuse.hpp>

#include <fmt/format.h>

#include <sstream>

#include <llvm/IR/InstIterator.h>
#include <llvm/IR/Instructions.h>

namespace llvmgraph {

std::string build_defuse_graph(llvm::Module *module) {
    if (module == nullptr) {
        return "";
    }
    std::string res_string;
    llvm::raw_string_ostream res(res_string);
    for (const auto &func : module->functions()) {
        for (auto i = llvm::inst_begin(func); i != llvm::inst_end(func); ++i) {
            for (const auto &operand : i->operands()) {
                auto *value = operand.get();
                auto instr = llvm::dyn_cast<llvm::Instruction>(value);
                if (instr == nullptr) {
                    continue;
                }
                res << "\"" << *i << "\" -> \"" << *instr << "\";\n";
            }
        }
    }
    return res.str();
}

}; // namespace llvmgraph