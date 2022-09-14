#!/bin/bash
TEST_FILES=tester/files/*.test

VALGRIND=true
V_FLAGS="--leak-check=full --show-leak-kinds=all -q"
SEP="+--------------------------------------------------------------------+"
OK="<\033[0;32mOK\033[0m>"
KO="<\033[1;31mKO\033[0m>"

# create trace 

if [ $VALGRIND = true ]; then
	if ! command -v valgrind > /dev/null; then
		>&2 echo "error: valgrind not found"
		VALGRIND=false
	fi
fi

check_diff()
{
	if cmp -s .out .expected;then
		printf "$OK\n"
	else 
		printf "$KO\n"
		echo $SEP
		if command -v colordiff > /dev/null; then
			diff -a .out .expected | colordiff
		else
			diff -a .out .expected
		fi
		echo $SEP
	fi
}

for file in $TEST_FILES; do
	if [ $VALGRIND = true ]; then
		python3 tester/gnl.py $file > .expected
		valgrind $V_FLAGS ./get_next_x $file > .out
	else
		python3 tester/gnl.py $file | xxd > .expected
		./get_next_x $file | xxd > .out
	fi
	printf "$(basename $file) ..." && python3 -c "print((' ' * (40 - len('$file'))), end='')" 
	check_diff
done
rm .out .expected