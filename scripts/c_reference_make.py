#!/usr/bin/env python3
# This script creates markdown files in the docs directory documenting elements
# of the C functions corresponding to each fetish
#
# Requires Python >=3.6

from common import*
import shutil

def makeDoxygenConfigFiles():
	if not os.path.exists("./doxygen"):
		os.makedirs("./doxygen")
	fetishes = getListOfFetishes()
	tabs = "\t"*4
	for fetish in fetishes:
		name = f"{fetish}_c_reference"
		config_text=f"""PROJECT_NAME{tabs}= {name}
HIDE_UNDOC_MEMBERS{tabs}= YES
OUTPUT_DIRECTORY{tabs}= ./doxygen/output
WARNINGS{tabs}= YES
INPUT{tabs}= {getFetishDirectory()}/{fetish}/include
FILE_PATTERNS{tabs}= *.h
GENERATE_XML{tabs}= YES
XML_OUTPUT{tabs}= ./{name}_xml
"""

		fp = open("doxygen/"+name, "w")
		fp.write(config_text)
		fp.close()

def runDoxygen():
	files = [x[2] for x in os.walk("./doxygen")][0]
	print(files)

	for fname in files:
		os.system("doxygen ./doxygen/"+fname)
def runMoxygen():
	fetishes = getListOfFetishes()
	for fetish in fetishes:
		filepath = f"../docs/c_reference/{fetish}.md"
		os.system(f"moxygen ./doxygen/output/{fetish}_c_reference_xml -o {filepath}")
		# Remove `public, cause this ain't C++
		doc = open(filepath, "r");
		new_contents = doc.read().replace("`public ", "`")
		doc.close()
		
		doc = open(filepath, "w")
		doc.write(new_contents)
		doc.close()

if __name__ == "__main__":
	makeDoxygenConfigFiles()
	runDoxygen()
	runMoxygen()
	shutil.rmtree("./doxygen")
