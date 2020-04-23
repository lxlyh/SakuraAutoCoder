// Copyright (C) 2017-2019 Jonathan M��ller <jonathanmueller.dev@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level directory of this distribution.

#include <iostream>
#include "cppast/external/cxxopts/include/cxxopts.hpp"
#include <cppast/cpp_forward_declarable.hpp> // for is_definition()
#include <cppast/cpp_namespace.hpp>          // for cpp_namespace
#include <cppast/visitor.hpp>         // for visit()
#include "CodeGen/Common/TimeStampHeader.hpp"
#include "include/filesystem.utils.hpp"
#include "Parse/sakura_cpp.parser.hpp"
#include "CodeGen/Refl/refl.codegenerater.hpp"
#include <fstream> 
#include <filesystem>
namespace fs = std::filesystem;

extern std::unordered_map<std::string, Sakura::refl::ReflUnit> ReflUnits = {};
extern bool bDebugAST = false;


// print help options
void print_help(const cxxopts::Options& options)
{
	std::cout << options.help({ "", "compilation" }) << '\n';
}

// print error message
void print_error(const std::string& msg)
{
	std::cerr << msg << '\n';
}

int main(int argc, char* argv[])
try
{
	cxxopts::Options option_list("SakuraRefl",
		"SakuraAutoCoder - The CodeGenTool of SakuraEngine.\n");
	// clang-format off
	option_list.add_options()
		("h,help", "display this help and exit")
		("version", "display version information and exit")
		("v,verbose", "be verbose when parsing")
		("fatal_errors", "abort program when a parser error occurs, instead of doing error correction")
		("dbg", "print debug AST info")
		("o", "generated file", cxxopts::value<std::string>())
		("file", "the file that is being parsed (last positional argument)",
			cxxopts::value<std::string>());
	option_list.add_options("compilation")
		("database_dir", "set the directory where a 'compile_commands.json' file is located containing build information",
			cxxopts::value<std::string>())
		("database_file", "set the file name whose configuration will be used regardless of the current file name",
			cxxopts::value<std::string>())
		("std", "set the C++ standard (c++98, c++03, c++11, c++14, c++1z (experimental))",
			cxxopts::value<std::string>()->default_value(cppast::to_string(cppast::cpp_standard::cpp_latest)))
		("I,include_directory", "add directory to include search path",
			cxxopts::value<std::vector<std::string>>())
		("D,macro_definition", "define a macro on the command line",
			cxxopts::value<std::vector<std::string>>())
		("U,macro_undefinition", "undefine a macro on the command line",
			cxxopts::value<std::vector<std::string>>())
		("f,feature", "enable a custom feature (-fXX flag)",
			cxxopts::value<std::vector<std::string>>())
		("gnu_extensions", "enable GNU extensions (equivalent to -std=gnu++XX)")
		("msvc_extensions", "enable MSVC extensions (equivalent to -fms-extensions)")
		("msvc_compatibility", "enable MSVC compatibility (equivalent to -fms-compatibility)")
		("fast_preprocessing", "enable fast preprocessing, be careful, this breaks if you e.g. redefine macros in the same file!")
		("remove_comments_in_macro", "whether or not comments generated by macro are kept, enable if you run into errors");
	// clang-format on
	option_list.parse_positional("file");
	auto options = option_list.parse(argc, argv);
	auto startTime = std::chrono::high_resolution_clock::now();

	if (options.count("dbg"))
		bDebugAST = true;
	if (options.count("help"))
		print_help(option_list);
	else if (options.count("version"))
	{
		std::cout << "cppast version " << CPPAST_VERSION_STRING << "\n";
		std::cout << "Copyright (C) Jonathan M��ller 2017-2019 <jonathanmueller.dev@gmail.com>\n";
		std::cout << '\n';
		std::cout << "Using libclang version " << CPPAST_CLANG_VERSION_STRING << '\n';
	}
	else if (!options.count("file") || options["file"].as<std::string>().empty())
	{
		print_error("missing file argument");
		return 1;
	}
	else
	{
		if (options.count("o"))
		{
			fs::path p = options["file"].as<std::string>();
			fs::path genp = options["o"].as<std::string>();
			std::map<fs::path, bool> validMap;
			validMap[p] = Sakura::fs::generated_file_valid(p, genp);
			if(!validMap[p])
			{
				// the compile config stores compilation flags
				cppast::libclang_compile_config config;
				Sakura::parser::sakura_cpp_config(config, options);
				// the logger is used to print diagnostics
				cppast::stderr_diagnostic_logger logger;
				if (options.count("verbose"))
					logger.set_verbose(true);

				// parse and gen-code for single file
				std::string oof = options["o"].as<std::string>();
				std::ofstream outf(oof, fstream::out | ios_base::trunc);
				startTime = std::chrono::high_resolution_clock::now();
				auto file = Sakura::parser::parse_file(config, logger, options["file"].as<std::string>(),
				options.count("fatal_errors") == 1);
				if (!file)
					return 2;
				// start codegen
				Sakura::CommonGen::gen_timestamp_header(outf, genp);
				// generate reflection code
				Sakura::refl::gen_refl_code(outf, *file);
			}
		}
	}
	auto currentTime = std::chrono::high_resolution_clock::now();
	float time = std::chrono::duration
		<float, std::chrono::seconds::period>(currentTime - startTime).count();
	std::cout << time << std::endl;
}
catch (const cppast::libclang_error& ex)
{
	print_error(std::string("[fatal parsing error] ") + ex.what());
	return 2;
}
