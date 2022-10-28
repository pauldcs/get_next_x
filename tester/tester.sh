#    tester.sh
#    By: pducos <pducos@student.42.fr>
#    Created: 2022/10/05 03:39:34 by pducos

#!/bin/bash

PROG="./reader"
SUFFIX=test
INFILES=tester/infiles/*.$SUFFIX
INDIR=tester/infiles
OUTDIR=tester/outfiles
VALGRIND=true

OK="\033[0;32mOK\033[0m\n"
KO="\033[1;31mKO\033[0m\n"

if [[ $(uname) == 'Linux' ]];
	then
		DIFF_FLAGS="--color -Tp"
		if ! command -v valgrind > /dev/null;
			then
				>&2 echo "Notice: Consider installing valgrind"
				VALGRIND=false
		fi
	else
		VALGRIND=false
		DIFF_FLAGS="-Tp"
fi

if [ "$VALGRIND" == false ];
	then
		>&2 echo "Notice: valgrind not enabled"
fi

mkdir -vp $OUTDIR > /dev/null
for infile in $INFILES;
	do
		name=$(basename $infile)
		base=${name%.$SUFFIX}
		actual=$OUTDIR/$base.actual
		log_valg=$OUTDIR/$base.valgrind
		python3 tester/reader.py $infile &> $OUTDIR/$base.out
		expected=$OUTDIR/$base.out
		if [ "$VALGRIND" == true ];
			then
				valgrind                     \
					-q                       \
					--leak-check=full        \
					--show-leak-kinds=all    \
					--track-origins=yes      \
					--log-file=$log_valg     \
				$PROG $infile &> $actual
			else
				$PROG $infile &> $actual
		fi
		printf $name
		printf " "
		python3 -c                                           \
			"import os;                                      \
			 name_len = len('$name');                        \
			 term_len = $(/usr/bin/tput cols);               \
			 print(('.' * (term_len - name_len - 4)), end='')"
		printf " "
		if (cmp -s $actual $expected)
			then
				printf $OK
			else
				printf $KO
				diff $DIFF_FLAGS $actual $expected
		fi
		if [ -s $log_valg ];
			then
				printf "\033[1;31mMEMORY ERROR\033[0m\n"
				cat $log_valg
		fi
done
rm -rf $OUTDIR
