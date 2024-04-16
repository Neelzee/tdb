export DB_TEST_PATH="/home/nmf/Documents/tdb/.test/"
gcc -Wall -o tdb src/main.c lib/*/*.c && ./tdb && rm tdb
