#include "ops.h"

void append_row(struct DBReader *b_reader, union DBLiteral *row) {
  // Sets the `cursor` to the end of the file
  fseek(b_reader->db, 0, SEEK_END);

  // Writes the row to the file
  fwrite(row, sizeof(union DBLiteral), b_reader->table->col_count,
         b_reader->db);

  free(row);
}

struct DBCell *read_row(struct DBReader *b_reader, int row) {
  int size = sizeof(union DBLiteral);
  // Moves the `cursor`, size * column count * row bytes forward, relative to
  // the start of the file.
  fseek(b_reader->db, size * b_reader->table->col_count * row, SEEK_SET);

  // Allocates an array of cells, column count long
  struct DBCell *cells =
      malloc(sizeof(struct DBCell) * b_reader->table->col_count);

  for (int i = 0; i < b_reader->table->col_count; i++) {
    // Reads from where the `cursor` is, into literals
    // the `cursor` is moved after a read, the same amount of bytes read

    // Allocates memory
    cells[i].value = malloc(size);

    fread(cells[i].value, size, 1, b_reader->db);
    cells[i].type = b_reader->table->col[i];
  }

  return cells;
}
