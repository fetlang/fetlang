project('Fetlang', ['c', 'cpp'], default_options : ['cpp_std=c++17'])

#include directories
thirdparty_dir = include_directories('thirdparty')
fetish_dir = include_directories('../fetishes')

main_incdirs = [thirdparty_dir]
test_incdirs = [fetish_dir, thirdparty_dir]

common_sources = ['Fraction.cpp', 'FractionParser.cpp', 'QuoteUtil.cpp', 'Token.cpp', 'Tokenizer.cpp',
	'Variable.cpp', 'FetlangManager.cpp', 'Operator.cpp', 'Variable.cpp', 'VariableCollection.cpp',
	'SyntaxTree.cpp', 'Parser.cpp', 'Grammar.cpp', 'Transpiler.cpp', 'FileUtil.cpp', 'Builder.cpp',
	'thirdparty/whereami.cpp', 'FetlangException.cpp', 'CompilationProcess.cpp']

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

executable('fetlang', release_sources, include_directories: main_incdirs, install:true, install_dir: 'bin')
unit_tests_executable = executable('unit_tests', test_sources, include_directories: test_incdirs)

test('unit_tests', unit_tests_executable)
