#include "../lib/db/db.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("Doing stuff\n");

  // Three columns, three rows
  union DBLiteral *lits = malloc(sizeof(union DBLiteral) * 3 * 3);

  union DBLiteral *start = lits;

  for (int i = 0; i < 9; i++) {
    lits[i]._int = i;
  }

  enum DBType *row = malloc(sizeof(enum DBType) * 3);

  for (int i = 0; i < 3; i++) {
    row[i] = INT;
  }

  struct DBTable table = {
      .name = "nils_db",
      .row_count = 3,
      .col_count = 3,
      .col = row,
  };

  bool res = write_rows(&table, start, 3);

  if (res) {
    printf("WE WROTE\n");
  } else {
    printf("WE BROKE\n");
  }

  struct DBCell *cells = malloc(sizeof(struct DBCell) * 3);

  struct DBCell *s = cells;

  res = read_row(&table, cells, 0);

  if (res) {
    printf("WE RODE\n");

    for (int i = 0; i < 3; i++) {
      union DBLiteral lit = *s[i].value;
      printf("%d ", lit._int);
    }
    printf("\n");

  } else {
    printf("WE BROKE\n");
  }

  free(start);
  free(cells);
  free(row);

  return 0;
}
