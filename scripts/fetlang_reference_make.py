#!/usr/bin/env python3
# This script creates markdown files in the docs directory documenting elements
# of each fetish, as well as creates a table of contents
#
# Requires Python >=3.6

import json
from common import*

def getReferenceDirectory():
	return getDocsDirectory()+"/reference/"
def getContentsPath():
	return getDocsDirectory()+"/reference.md"

def getCodePairPossibilities():
	types = ["fraction", "chain", "stream", "reference"]
	pairs = []
	for a in types:
		for b in types:
			pairs.append(f"{a}/{b}")
	return pairs

def loadJsonFile(filename):
	a = open(filename, "r")
	j = json.loads(a.read())
	a.close()
	return j


def getMarkdownSection(fetish_file, section):
	if section.replace(" ", "_") in fetish_file:
		markdown = f"## {section.title()}\n"
		for element in fetish_file[section.replace(" ", "_")]:
			if "description" in element:
				markdown += f"### {element['name']}\n"
				if "description" in element:
					markdown += element["description"]+"  \n\n"
				if "grammars" in element:
					markdown += "Grammar: "
					for grammar in element["grammars"]:
						markdown += grammar+ (", " if grammar != element["grammars"][-1] else "")
					markdown += "  \n"
				if "examples" in element:
					markdown += "Examples:  \n"
					for example in element["examples"]:
						markdown += "`"+example+"`  \n\n"
				if "type" in element:
					markdown += f"Type: {element['type']}  \n"
				if "gender" in element:
					markdown += f"Gender: {element['gender']}  \n"
				if "code" in element:
					markdown += "C Code: "
					if section == "builtins":
						markdown += "`"+element["code"]+"`  \n\n"
					else:
						markdown += " \n\n"
						for pair in getCodePairPossibilities():
							if pair in element["code"]:
								markdown += (f"    /* {pair} overload */\n    {element['code'][pair]}  \n\n")
		return markdown
	return ""

def getReferencePageMarkdown(fetish_name):
	fetish_file = loadJsonFile(getFetishFileOfFetish(fetish_name))

	markdown = f"# {fetish_name.title()}\n{fetish_file['description']}\n"
	markdown += getMarkdownSection(fetish_file, "operators")
	markdown += getMarkdownSection(fetish_file, "comparison operators")
	markdown += getMarkdownSection(fetish_file, "builtins")
	return markdown

def makeReferencePage(fetish_name):
	markdown = getReferencePageMarkdown(fetish_name)
	filename = getReferenceDirectory()+fetish_name+".md"
	fp = open(filename, "w")
	fp.write(markdown)
	fp.close()
	return filename
def getShortDescription(fetish):
	descriptions = {"core" : "The included-by-default fetish that defines the language",
	"assertiveness": "Contains assertion operators. Useful for unit tests",
	"obedience": "File IO operators",
	"manhandling": "Filesystem operators"}

	return descriptions[fetish]

def makeReferencePages():
	contents = "# Fetish Reference\n"
	for fetish in getListOfFetishes():
		ref_page = makeReferencePage(fetish)
		contents += f"""{fetish.title()} - {getShortDescription(fetish)}  
[C Reference](c_reference/{fetish}.md)  
[Fetlang Reference](reference/{fetish}.md)  \n\n"""
	fp = open(getContentsPath(), "w")
	fp.write(contents)
	fp.close()
	
	
if __name__ == "__main__":
	makeReferencePages()
