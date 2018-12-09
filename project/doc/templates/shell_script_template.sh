#!/bin/bash

print_info_message()
{
	echo "\n\n##############################"
	echo "	$1"
	echo "##############################\n\n"
}

print_error_message()
{
	echo "##############################"
	echo "	A COMMAND HAS FAILED --->"
	echo "			$1"
	echo "##############################"
}


print_success_message()
{
	echo "##############################"
	echo "	SUCESS MESSAGE"
	echo "##############################"
}

print_success_message