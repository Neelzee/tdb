#include "db.h"
#include <stdio.h>

struct DBTable *init_db(char *o_name, int name_len, enum DBType *o_col,
                        int col_count) {
  struct DBTable *table = malloc(sizeof(struct DBTable));
  table->col = o_col;

  for (int i = 0; i < name_len; i++) {
    table->name[i] = o_name[i];
  }

  table->col_count = col_count;

  table->row_count = 0;

  return table;
}

struct DBReader *init_reader(struct DBTable *o_table) {
  struct DBReader *reader = malloc(sizeof(struct DBReader));

  reader->table = o_table;

  FILE *file = fopen(o_table->name, "rb+");

  if (file == NULL) {
    file = fopen(o_table->name, "a");
    file = fopen(o_table->name, "rb+");
  }

  reader->db = file;

  return reader;
}
