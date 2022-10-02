#!/bin/bash
TEST_FILES=tester/files/*.test

VALGRIND=true

if [ $VALGRIND = true ]; then
	if ! command -v valgrind > /dev/null; then
		>&2 echo "error: valgrind not found"
		VALGRIND=false
	fi
fi

check_diff()
{
	if cmp -s .out .expected; then
		printf " \033[0;32mOK\033[0m "
		if [ -s log.txt ]; then
			printf "                         "
			printf "\033[1;31mMEMORY ERROR\033[0m\n"
			echo "+--------------------------------------------------------------------+"
			cat log.txt
			echo "+--------------------------------------------------------------------+"
			rm -f log.txt
			rm .out .expected
			exit 0
		else
			printf "\n"
	fi
	else 
		printf " \033[1;31mKO\033[0m "
		if [ -s log.txt ]; then
			printf "                         "
			printf "\033[1;31mMEMORY ERROR\033[0m\n"
			echo "+--------------------------------------------------------------------+"
			cat log.txt
			echo "+--------------------------------------------------------------------+"
			rm -f log.txt
			rm .out .expected
			exit 0
		else
			printf "\n"
			echo "+--------------------------------------------------------------------+"
		fi
		cat log.txt 2> /dev/null
		if command -v colordiff > /dev/null; then
			diff -a .out .expected | colordiff
		else
			diff -a .out .expected
		fi
		echo "+--------------------------------------------------------------------+"
		rm -f log.txt
		rm .out .expected
		exit 0
	fi
}

for file in $TEST_FILES; do
	python3 tester/reader.py $file | xxd > .expected
	if [ $VALGRIND = true ]; then
		valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=log.txt -q ./reader $file | xxd > .out
	else
		./reader $file | xxd > .out
	fi
	printf "$(basename $file) " && python3 -c "print(('.' * (40 - len('$file'))), end='')" 
	check_diff
done
rm -f log.txt
rm .out .expected