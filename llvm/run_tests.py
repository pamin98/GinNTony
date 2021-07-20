import glob
import os

path = '/home/akimonid/code/GinNTony/tests/Correct/'
errors = []
for filename in glob.glob(os.path.join(path, '*.tony')):
    ret = os.system('./GinNTony %s' % filename)
    if ret != 0:
        errors.append(filename)

print(errors)

#    with open(os.path.join(os.getcwd(), filename), 'r') as f: # open in readonly mode
      # do your stuff