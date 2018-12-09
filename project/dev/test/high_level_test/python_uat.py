#############################################################################
# 8-bit Hubble User Aceptance Test (UAT)
#
# The script launches in a command line interface (CLI) several commands
# reproducing the user interaction with the application.
# Not all possible combinations are tested; only those required to
# demonstrate the proper behavior of the app.
#############################################################################

import sys
import os
import subprocess
import time 

####################
# GLOBAL VARIABLES #
####################

# This executable name shall concur with the one in the Makefile of the project
# located at <project_root>/project/def/sw/dev/integration"
cli_exec = "../../integration/8bh_cli_cov.exe"

o_flag = "-o" # Flag to indicate the output directory
n_flag = "-n" # Flag to indicate the output image name
s_flag = "-s" # Flag to indicate the value of the seed
h_flag = "-h" # Flag to print the help information
v_flag = "-v" # Flag to print the version or "about" information

o_dir = "./"
o_alt_dir = ".\\" # This reproduces a Windows directory, using a backslash as separator
o_wrong_dir = "/this/do/not/exist"
o_noperm_dir = "/path/to/no_perm/dir"

name = "uat_image"
name2 = "uat_image2"
wrong_name = "uat image"
wrong_name2 = "uat_image.png"
wrong_name3 = "uat_image5!"

seed = "1234567890"
# Seed 2, 3 and 4 are used to force generation of images with all possible stars, with cosmic background color, etc
seed2 = "10"
seed3 = "20"
seed4 = "30"
wrong_seed = "a"
wrong_seed2 = "9999999999"
wrong_seed3 = "-12"

png_ext = ".png"


working_commands = [
[cli_exec, h_flag], 	# Shall print the help information
[cli_exec, v_flag], 	# Shall print the version information
[cli_exec, o_flag, o_dir, n_flag, name],			# Generates image
[cli_exec, o_flag, o_alt_dir, n_flag, name],			# Generates image
[cli_exec, o_flag, o_dir, n_flag, name, s_flag, seed2], 	# Generates image
[cli_exec, o_flag, o_dir, n_flag, name, s_flag, seed3], 	# Generates image
[cli_exec, o_flag, o_dir, n_flag, name, s_flag, seed4], 	# Generates image
[cli_exec, o_flag, o_dir, n_flag, name, s_flag, seed], 	# Generates image
[cli_exec, o_flag, o_dir, n_flag, name, s_flag, seed, "irrelevant_value"], 	# Generates image (more arguments than needed does not affect the app.
[cli_exec, o_flag, o_dir, n_flag, name2, s_flag, seed] 	# Generates image number 2 with same seed
]

failing_commands = [
[cli_exec], 			# Fail due to incomplete arguments

### THESE COMMANDS TEST EACH ERROR CONDITION INDIVIDUALLY
[cli_exec, o_flag, n_flag, name], 	# No output path specified
[cli_exec, o_dir, n_flag, name], 	# Missing -o flag
[cli_exec, n_flag, name], 	# No flag and no path specified
[cli_exec, o_flag, o_wrong_dir, n_flag, name], 	# Incorrect output directory
[cli_exec, o_flag, o_noperm_dir, n_flag, name], 	# Output directory forbidden


[cli_exec, o_flag, o_dir, n_flag], 	# No output image name specified
[cli_exec, o_flag, o_dir, n_flag, ""], 	# No output image name specified (to force shell recognize an empty string)
[cli_exec, o_flag, o_dir, name], 	# Missing -n flag
[cli_exec, o_flag, o_dir], 	# No flag and no path specified
[cli_exec, o_flag, o_dir, n_flag, wrong_name], 	# Invalid output image name
[cli_exec, o_flag, o_dir, n_flag, wrong_name2], 	# Invalid output image name
[cli_exec, o_flag, o_dir, n_flag, wrong_name3], 	# Invalid output image name

[cli_exec, o_flag, o_dir, n_flag, name, s_flag], 	# No seed specified
### [cli_exec, o_flag, o_dir, n_flag, name, seed], 	# This command WORKS. It is actually tested in working_commands list
[cli_exec, o_flag, o_dir, n_flag, name, s_flag, wrong_seed], 	# Invalid seed
#[cli_exec, o_flag, o_dir, n_flag, name, s_flag, wrong_seed2], 	# Invalid seed #@TODO decide what to do with big seeds
[cli_exec, o_flag, o_dir, n_flag, name, s_flag, wrong_seed3], 	# Invalid seed


### THESE COMMANDS TEST THAT SEVERAL ERRORS AT THE SAME TIME DOES NOT NULLIFY EACH OTHER
[cli_exec, o_flag], 		# Fail due to incomplete arguments
[cli_exec, o_flag, o_dir], 	# Fail due to incomplete arguments
[cli_exec, o_flag, o_dir, n_flag], # Fail due to incomplete arguments
[cli_exec, o_flag, o_dir, n_flag, name, s_flag], # Fail due to incomplete arguments
[cli_exec, o_flag, o_wrong_dir, n_flag, name, s_flag, seed], 	# Fail due to incorrect output dir
[cli_exec, o_flag, o_noperm_dir, n_flag, name, s_flag, seed], 	# Fail due to forbidden output dir
[cli_exec, o_flag, o_dir, n_flag, wrong_name, s_flag, seed], 	# Fail due to incorrect name
[cli_exec, o_flag, o_dir, n_flag, wrong_name2, s_flag, seed], 	# Fail due to incorrect name
[cli_exec, o_flag, o_dir, n_flag, wrong_name3, s_flag, seed], 	# Fail due to incorrect name
[cli_exec, o_flag, o_dir, n_flag, name, s_flag, wrong_seed], 	# Fail due to incorrect seed
#[cli_exec, o_flag, o_dir, n_flag, name, s_flag, wrong_seed2], 	# Fail due to incorrect seed #@TODO decide what to do with big seeds
[cli_exec, o_flag, o_dir, n_flag, name, s_flag, wrong_seed3], 	# Fail due to incorrect seed
]

####################
# FUNCTIONS        #
####################

def compare_byte_to_byte(img1, img2):
    # Compare size of files
    img1_stats = os.stat(img1)
    img2_stats = os.stat(img2)
    
    if (img1_stats.st_size != img2_stats.st_size):
        print "Error: images generated with same seed are NOT equal (different size).\n"
        print "Aborting tests.\n"
        sys.exit(1)
    
    reader_one = open(img1)
    reader_two = open(img2)
    
    byte_from_one = reader_one.read(1)
    byte_from_two = reader_two.read(1)
    
    while ((byte_from_one != "") and (byte_from_two != "")):
        if (byte_from_one != byte_from_two):
            print "Error: images generated with same seed are NOT equal (different content).\n"
            reader_one.close()
            reader_two.close()
            print "Aborting tests.\n"
            sys.exit(1)
        byte_from_one = reader_one.read(1)
        byte_from_two = reader_two.read(1)
        
    reader_one.close()
    reader_two.close()
    
def main():
	# Check the executable exists
	if not (os.path.isfile(cli_exec)):
		print "Executable does not exist. Please compile before testing.\n"
		print "To compile, go to home directory, and launch \"install.sh\" script, \
			 or go to dev/integration/8bH_cli and execute \"make\"\n"
		print "Aborting test\n"
		sys.exit(1)
		
	if (o_noperm_dir == "/path/to/no_perm/dir"):
		print "WARNING: the variable \"o_noperm_dir\" has not been modified by the user.\n \
Test will continue to run, but the test that checks that no permissions directory\n \
makes the app fail won't be correct. To properly test all possibilities, modify\n \
that variable inside \"python_uat.py\" to contain a path to a directory with no permissions.\n\n"

	print "STARTING TESTS ... \n\n"
	time.sleep(5) # The only purpose of this wait is to give user time to read all messages printed up to this point.
	
	#devnull = open (os.devnull, "w") # Use the null device to discard the commands output
	
	# Test working commands
	for command in working_commands:
		#ret_value = subprocess.call(command, stdout=devnull)
		ret_value = subprocess.call(command)
		if (ret_value != 0):
			print "\n"*4 + "="*10
			print "Unexpected error when launching the following command:\n"
			print str(command) + "\n"
			print "It should WORK, but returned a failure code. Aborting test\n"
			#devnull.close()
			sys.exit(1)

	# Test failing commands
	for command in failing_commands:
		#ret_value = subprocess.call(command, stdout=devnull)
		ret_value = subprocess.call(command)
		if (ret_value == 0):
			print "\n"*4 + "="*10
			print "Unexpected error when launching the following command:\n"
			print str(command) + "\n"
			print "It should FAIL, but returned a successfull code. Aborting test\n"
			#devnull.close()
			sys.exit(1)

	# Test specific features
    	# Test generation with seed is correct
	subprocess.call(working_commands[6])
	subprocess.call(working_commands[8])
	compare_byte_to_byte(o_dir + name + png_ext, o_dir + name2 + png_ext)
	#devnull.close()
    
	print "\n"*4 + "="*10
	print "8 BIT HUBBLE USER ACCEPTANCE TEST FINISHED SUCCESSFULLY\n"	



# ENTRY POINT.
if __name__ == '__main__':
    main()
