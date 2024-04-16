#include "db.h"

bool is_nothing(struct Maybe *maybe) { return maybe->nothing; }

bool write_cell(struct DBCell *cell) {
  FILE *file = fopen("data.bin", "wb");
  if (file != NULL) {
    fwrite(cell, sizeof(struct DBCell), 1, file);
    fclose(file);
    return true;
  } else {
    return false;
  }
}

bool read_cell(struct DBCell *cell) {
  FILE *file = fopen("data.bin", "rb");
  if (file != NULL) {
    fread(cell, sizeof(struct DBCell), 1, file);
    fclose(file);
    return true;
  } else {
    return false;
  }
}

bool overwrite_row(struct DBTable *table, union DBLiteral *cells, int row) {

  FILE *file = fopen(table->name, "rb+");

  if (file == NULL) {
    return false;
  }

  /*
   * SEEK_SET is a constant defined in the stdio.h header file,
   * typically used with file positioning functions like fseek().
   * > ChatGPT 2024
   */
  int size = sizeof(struct DBCell);
  int row_size = size * table->col_count;
  fseek(file, row_size * row, SEEK_SET);
  // ^ Moves the cursor, to the specified row
  for (int i = 0; i < table->col_count; i++) {
    fwrite(cells, sizeof(struct DBCell), table->col_count, file);
    // Moves the `cursor` `size` forward, relative to where the cursor is.
    fseek(file, size, SEEK_CUR);
    cells++;
  }

  return true;
}

bool append_rows(struct DBTable *table, union DBLiteral *cells, int rows) {
  FILE *file = fopen(table->name, "ab");

  if (file == NULL) {
    return false;
  }

  int size = sizeof(union DBLiteral);
  for (int i = 0; i < rows * table->col_count; i++) {
    fwrite(&cells[i], size, 1, file);
  }

  return true;
}

bool write_rows(struct DBTable *table, union DBLiteral *cells, int rows) {
  FILE *file = fopen(table->name, "wb");

  if (file == NULL) {
    return false;
  }

  int size = sizeof(union DBLiteral);
  for (int i = 0; i < rows * table->col_count; i++) {
    fwrite(&cells[i], size, 1, file);
  }

  return true;
}

bool read_row(struct DBTable *table, struct DBCell *cells, int row) {
  FILE *file = fopen(table->name, "rb");

  if (file == NULL) {
    return false;
  }

  // Moves the cursor to the expected place

  int size = sizeof(union DBLiteral);

  fseek(file, size * table->col_count * row, SEEK_SET);

  enum DBType *types = table->col;

  for (int i = 0; i < table->col_count; i++) {
    enum DBType type = types[i];
    cells[i].type = type;
    cells[i].value = malloc(size);
    fread(cells[i].value, size, 1, file);
  }

  fseek(file, size * table->col_count * row, SEEK_SET);

  return true;
}
