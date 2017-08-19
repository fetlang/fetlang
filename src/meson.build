project('Fetlang', ['c', 'cpp'], default_options : ['cpp_std=c++11'])
boost_dir = include_directories('thirdparty/boost/')
thirdparty_dir = include_directories('thirdparty')
fetish_dir = include_directories('../fetishes')

main_incdirs = [boost_dir, thirdparty_dir]
test_incdirs = [fetish_dir, boost_dir, thirdparty_dir]
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

common_sources = boost_sources+['Fraction.cpp', 'FractionParser.cpp', 'QuoteUtil.cpp', 'Token.cpp', 'Tokenizer.cpp',
	'Variable.cpp', 'FetlangManager.cpp', 'Operator.cpp', 'Variable.cpp', 'VariableCollection.cpp',
	'SyntaxTree.cpp', 'Parser.cpp', 'Grammar.cpp', 'Transpiler.cpp', 'FileUtil.cpp', 'Builder.cpp',
	'thirdparty/whereami.cpp']
release_sources = common_sources + ['main.cpp']

fetish_sources = [
'../fetishes/core/source/chain.c', '../fetishes/core/source/error.c', '../fetishes/core/source/fraction.c', '../fetishes/core/source/fraction_math.c',
'../fetishes/core/tests/chain.cpp']
test_sources = common_sources + fetish_sources + ['tests/main.cpp','tests/fraction_parser.cpp','tests/quote_util.cpp', 'tests/parser.cpp',
'tests/tokenizer.cpp', 'tests/file_util.cpp', 'tests/compilation.cpp']

install_subdir('../fetishes', install_dir:'share/fetlang')
executable('fetlang', release_sources, include_directories: main_incdirs, install:true, install_dir: 'bin')


unit_tests_executable = executable('unit_tests', test_sources, include_directories: test_incdirs)
test('unit_tests', unit_tests_executable)
