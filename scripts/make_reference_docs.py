#!/usr/bin/env python3
# This script creates markdown files in the docs directory documenting elements
# of each fetish, as well as creates a table of contents

import json
import os

def getFetishDirectory():
	return "../fetishes/"
def getDocsDirectory():
	return "../docs/"
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

def getListOfFetishes():
	return [x[1] for x in os.walk(getFetishDirectory())][0]

def getFetishFileOfFetish(fetish_name):
	return getFetishDirectory()+fetish_name+"/fetish.json"

def getMarkdownSection(fetish_file, section):
	if section.replace(" ", "_") in fetish_file:
		markdown = f"## {section.title()}\n"
		for element in fetish_file[section.replace(" ", "_")]:
			markdown += f"### {element['name']}\n"
			if "description" in element:
				markdown += element["description"]+"\n"
			if "examples" in element:
				markdown += "Examples:  \n"
				for example in element["examples"]:
					markdown += "`"+example+"`  \n"
			if "code" in element:
				markdown += "C Code:  \n"
				if section == "builtins":
					markdown += element["code"]
				else:
					for pair in getCodePairPossibilities():
						if pair in element["code"]:
							markdown += (f"{pair} - `{element['code'][pair]}`  \n")
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

def makeReferencePages():
	contents = "# Fetish Reference\n"
	for fetish in getListOfFetishes():
		ref_page = makeReferencePage(fetish)
		contents += f"[{fetish.title()}](reference/{fetish}.md) - <description>  \n"
	fp = open(getContentsPath(), "w")
	fp.write(contents)
	fp.close()
	
	
if __name__ == "__main__":
	makeReferencePages()
