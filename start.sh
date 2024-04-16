export DB_TEST_PATH="/home/nmf/Documents/tdb/.test/"
gcc -o tdb src/main.c lib/*/*.c && ./tdb && rm tdb
