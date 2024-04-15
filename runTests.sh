gcc -o test tests/test.c -l cmocka -L /usr/local/lib lib/db/*.c -I../lib/db && ./test && rm test
