#ifndef DB_H
#define DB_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum DBType {
  INT,
  FLOAT,
  STRING,
  LIST,
  MAYBE,
};

/**
 * Value being written to the database
 */
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

/**
 * Cell representation
 * Not what is written to the database,
 * but used too know what type we are dealing with.
 */
struct DBCell {
  enum DBType type;
  union DBLiteral *value;
};

/**
 * Meta information about a table in a database
 *
 * name: Name of the table
 *
 * row_count: amount of rows in this table
 *
 * col_count: amount of cols in this table
 *
 * cells: array of cells, from 0-col_count
 */
struct DBTable {
  char name[256];
  int row_count;
  int col_count;
  enum DBType *col;
};

/**
 * Returns true if the given Maybe is nothing
 * TODO: Remove this, it's not needed
 */
bool is_nothing(struct Maybe *maybe);

bool write_cell(struct DBCell *cell);

bool read_cell(struct DBCell *cell);

bool init_db(struct DBTable *table);

/**
 * Overwrites the n-th row with the given new row
 */
bool overwrite_row(struct DBTable *table, union DBLiteral *cells, int row);

/**
 * Writes the given rows to the db
 */
bool append_rows(struct DBTable *table, union DBLiteral *cells, int rows);

/**
 * overwrites
 */
bool write_rows(struct DBTable *table, union DBLiteral *cells, int rows);

bool read_row(struct DBTable *table, struct DBCell *cells, int row);

#endif
