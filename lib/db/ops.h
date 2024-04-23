#ifndef OPS_H
#define OPS_H

#include "db.h"

/**
 * Appends the given row, then frees it
 */
void append_row(struct DBReader *b_reader, union DBLiteral *row);

/**
 * Reads the given row
 */
struct DBCell *read_row(struct DBReader *b_reader, int row);

#endif // !OPS_H
