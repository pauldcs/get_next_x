import sys

file = open(sys.argv[1], 'r')
while True:
    line = file.readline()
    if not line:
        break ;
    print(line.replace('\n', ''))

file.close()