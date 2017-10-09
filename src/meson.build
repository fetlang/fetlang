project('Fetlang', ['c', 'cpp'], default_options : ['cpp_std=c++11'])
use_system_boost = get_option('use_system_boost')

#include directories
thirdparty_dir = include_directories('thirdparty')
fetish_dir = include_directories('../fetishes')
# This only used if use_system_boost is false
boost_dir = include_directories('thirdparty/boost/')

main_incdirs = [boost_dir, thirdparty_dir]
test_incdirs = [fetish_dir, boost_dir, thirdparty_dir]

if use_system_boost
	boost_dep = dependency('boost', modules:['algorithm', 'filesystem', 'system'], required:false, version: '>=1.62.0')
endif

boost_sources = [
'thirdparty/boost/libs/filesystem/src/operations.cpp',
'thirdparty/boost/libs/filesystem/src/path.cpp',
'thirdparty/boost/libs/filesystem/src/path_traits.cpp',
'thirdparty/boost/libs/filesystem/src/portability.cpp',
'thirdparty/boost/libs/filesystem/src/unique_path.cpp',
'thirdparty/boost/libs/filesystem/src/utf8_codecvt_facet.cpp',
'thirdparty/boost/libs/filesystem/src/windows_file_codecvt.cpp',
'thirdparty/boost/libs/filesystem/src/codecvt_error_category.cpp',
'thirdparty/boost/libs/system/src/error_code.cpp'
]

raw_common_sources = ['Fraction.cpp', 'FractionParser.cpp', 'QuoteUtil.cpp', 'Token.cpp', 'Tokenizer.cpp',
	'Variable.cpp', 'FetlangManager.cpp', 'Operator.cpp', 'Variable.cpp', 'VariableCollection.cpp',
	'SyntaxTree.cpp', 'Parser.cpp', 'Grammar.cpp', 'Transpiler.cpp', 'FileUtil.cpp', 'Builder.cpp',
	'thirdparty/whereami.cpp', 'FetlangException.cpp', 'CompilationProcess.cpp']
if use_system_boost
	common_sources = raw_common_sources
else
	common_sources = boost_sources + raw_common_sources
endif
release_sources = common_sources + ['main.cpp']

fetish_sources = [
'../fetishes/core/source/chain.c', '../fetishes/core/source/error.c', '../fetishes/core/source/fraction.c',
'../fetishes/obedience/source/fileio.c',
'../fetishes/core/tests/chain.cpp', '../fetishes/obedience/tests/fileio.cpp',
'../fetishes/core/tests/fraction.cpp']
test_sources = common_sources + fetish_sources + ['tests/main.cpp','tests/fraction_parser.cpp','tests/quote_util.cpp', 'tests/parser.cpp',
'tests/tokenizer.cpp', 'tests/file_util.cpp', 'tests/compilation.cpp',
'tests/fraction.cpp']

install_subdir('../fetishes', install_dir:'share/fetlang')

if use_system_boost
	executable('fetlang', release_sources, include_directories: main_incdirs, install:true, install_dir: 'bin', dependencies: boost_dep)
	unit_tests_executable = executable('unit_tests', test_sources, include_directories: test_incdirs, dependencies: boost_dep)
else
	executable('fetlang', release_sources, include_directories: main_incdirs, install:true, install_dir: 'bin')
	unit_tests_executable = executable('unit_tests', test_sources, include_directories: test_incdirs)
endif

test('unit_tests', unit_tests_executable)
