import glob
import os
import subprocess

path = '/home/akimonid/code/GinNTony/tests/Correct/'
errors = []
nesting_links_errors = []
for filename in glob.glob(os.path.join(path, '*.tony')):
    res = subprocess.run(['./GinNTony', '-o', filename], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    # print(res.returncode)
    if res.returncode == 69:
        nesting_links_errors.append(filename)
    if res.returncode != 0 and res.returncode != 69:
        errors.append(filename)

print("This tests didn't run because nesting links were not implemented")
print("=================================================================")
for f in nesting_links_errors:
    print(f)
print("=================================================================")
print()
print()

print("This tests didn't run because we suck")
print("=====================================")
for f in errors:
    print(f)
print("=====================================")


#    with open(os.path.join(os.getcwd(), filename), 'r') as f: # open in readonly mode
      # do your stuff