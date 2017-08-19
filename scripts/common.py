import os
# Top level directory where fetishes are held
def getFetishDirectory():
	return "../fetishes/"

# Top level directory where docs are held
def getDocsDirectory():
	return "../docs/"

# List of fetishes as a list of strings
def getListOfFetishes():
	return [x[1] for x in os.walk(getFetishDirectory())][0]

# The fetish.json file given the name of a fetish
def getFetishFileOfFetish(fetish_name):
	return getFetishDirectory()+fetish_name+"/fetish.json"

