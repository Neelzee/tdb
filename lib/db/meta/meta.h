#ifndef META_H
#define META_H

#include "../../consts.h"
#include "../db.h"

/**
 * Meta inforation about a cell in a column
 *
 * type: The type stored in this cell.
 *
 * size: The size of the cell in bytes
 */
struct MetaCell {
  DBTypes type;
  int size;
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
struct MetaTable {
  char name[LIGATURE_LENGTH];
  int row_count;
  int col_count;
  MetaCell *cells;
};

struct MetaDb {
  MetaTable *tables;
  int table_count;
};

#endif
