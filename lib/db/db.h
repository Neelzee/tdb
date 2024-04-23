#ifndef DB_H
#define DB_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Type of a cell value
 */
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
 * Reader
 */
struct DBReader {
  FILE *db;
  struct DBTable *table;
};

struct DBTable *init_db(char name[], int name_len, enum DBType *col,
                        int col_count);

struct DBReader *init_reader(struct DBTable *table);

#endif
