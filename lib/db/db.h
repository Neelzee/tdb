#ifndef DB_H
#define DB_H

#include <stdbool.h>
#include <stdio.h>

enum DBType {
  INT,
  FLOAT,
  STRING,
  LIST,
  MAYBE,
};

// Forward declaration?
union DBLiteral;

struct Maybe {
  union DBLiteral *just;
  bool nothing;
};

union DBLiteral {
  int _int;
  float _float;
  char *_string;
  bool _bool;
  union DBLiteral *list;
  struct Maybe maybe;
};

struct DBCell {
  enum DBType type;
  union DBLiteral *value;
};

bool is_nothing(struct Maybe *maybe);

bool write_cell(struct DBCell *cell);

bool read_cell(struct DBCell *cell);

#endif
