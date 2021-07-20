import glob
import os
import subprocess

path = '/home/akimonid/code/GinNTony/tests/Correct/'
errors = []
for filename in glob.glob(os.path.join(path, '*.tony')):
    res = subprocess.run(['./GinNTony', filename], stdout=subprocess.DEVNULL)
    print(res.returncode)
    if res.returncode != 0 and res.returncode != 69:
        errors.append(filename)

print(errors)

#    with open(os.path.join(os.getcwd(), filename), 'r') as f: # open in readonly mode
      # do your stuff