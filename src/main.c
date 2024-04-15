#include "../lib/db/db.h"
#include <stdio.h>

int main() {
  printf("Hello, world!\n");

  union DBLiteral value = {._int = 69};

  struct DBCell cell = {INT, &value};
  struct DBCell _cell;

  bool res = write_cell(&cell);

  if (res) {
    printf("Saved something to a file!\n");
  } else {
    printf("Did not save something to a file!\n");
  }

  bool res_2 = read_cell(&_cell);

  if (res_2) {
    printf("Read something from a file!\n");
    printf("Value: %d\n", _cell.value->_int);
  } else {
    printf("Did not read something from a file!\n");
  }

  return 0;
}
