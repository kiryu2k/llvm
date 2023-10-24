#include <libllvmgraph/callgraph.hpp>
#include <libllvmgraph/defuse.hpp>

#include <fmt/core.h>

#include <fstream>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/SourceMgr.h>

int main(int argc, char **argv) {
    /* setup args */
    llvm::cl::opt<std::string> output(
        "output",
        llvm::cl::desc("An ouput file. Default stdout"),
        llvm::cl::value_desc("filename"));
    llvm::cl::opt<std::string> input(
        "input",
        llvm::cl::desc("An input file"),
        llvm::cl::value_desc("filename"));
    llvm::cl::opt<bool> callgraph(
        "dot-callgraph", llvm::cl::desc("Boolean flag. Output call graph"));
    llvm::cl::opt<bool> defuse(
        "dot-def-use", llvm::cl::desc("Boolean flag. Output def-use graph"));
    llvm::cl::ParseCommandLineOptions(argc, argv);
    llvm::SMDiagnostic err;
    llvm::LLVMContext ctx;
    auto ir_module = llvm::parseIRFile(input.getValue(), err, ctx);
    std::string result;
    if (callgraph.getValue()) {
        result = llvmgraph::build_callgraph(ir_module.get());
    } else if (defuse.getValue()) {
        result = llvmgraph::build_defuse_graph(ir_module.get());
    } else {
        fmt::print("invalid graph type to build\n");
        return 0;
    }
    if (result.empty()) {
        fmt::print("invalid input data\n");
        return 0;
    }
    if (output.getValue().empty()) {
        fmt::print("{}", result);
    } else {
        std::ofstream file(output.getValue());
        file << result;
    }
    return 0;
}