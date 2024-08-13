import subprocess
import os
import sys

def isccppfile(filename):
    return filename.endswith('.h') \
        or filename.endswith('.c') \
        or filename.endswith('.hpp') \
        or filename.endswith('.cpp') \

if __name__ == "__main__":
    args = sys.argv[1:]
    if len(args) < 2:
        print('Usage: python3 run-clang-format.py <dir> <style>')
        exit(1)

    dir   = args[0]
    style = ('BasedOnStyle: Microsoft, '
    	     'IndentWidth: 2, '
    	     'AlignAfterOpenBracket: Align, '
    	     'AlignConsecutiveAssignments: true, '
    	     'AlignConsecutiveDeclarations: true, '
    	     'AlignTrailingComments: true, '
    	     'AllowShortIfStatementsOnASingleLine: true, '
    	     'BreakBeforeBraces: Allman, '
    	     'PointerAlignment: Right, '
    	     'SpaceAfterCStyleCast: true, '
    	     'SpacesBeforeTrailingComments: 1, '
    	     'TabWidth: 4, '
    	     'UseTab: Always')


    for dir, _, files in os.walk(dir):
        for filename in files:
            filepath = dir + '/' + filename
            if isccppfile(filename):
                cmd = 'clang-format -i -style=' + '"{' + style + '}"' + ' ' + filepath
                subprocess.run(cmd, shell=True)


#    for dir, _, files in os.walk(dir):
#        for filename in files:
#            filepath = dir + '/' + filename
#            if isccppfile(filename):
#                subprocess.run('clang-format -i -style={} {}'.format(style, filepath), shell=True)