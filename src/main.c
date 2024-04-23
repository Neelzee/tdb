#include "../lib/db/db.h"
#include "../lib/db/ops.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

  char name[] = "nils_db";

  enum DBType column[] = {INT, INT, INT};

  struct DBTable *table = init_db(name, 7, column, 3);

  struct DBReader *reader = init_reader(table);

  // ROWS

  union DBLiteral *row = malloc(sizeof(union DBLiteral) * 3);

  row[0]._int = 10;
  row[1]._int = 11;
  row[2]._int = 12;

  append_row(reader, row);

  // Reads

  struct DBCell *row2 = read_row(reader, 0);

  printf("%d\n", row2[0].value->_int);
  printf("%d\n", row2[1].value->_int);
  printf("%d\n", row2[2].value->_int);

  return 0;
}
