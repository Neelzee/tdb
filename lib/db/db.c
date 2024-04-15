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
