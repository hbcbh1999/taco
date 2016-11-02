#ifndef TACO_STORAGE_ITERATOR_H
#define TACO_STORAGE_ITERATOR_H

#include <memory>
#include <ostream>
#include <string>

#include "ir.h"

namespace taco {
class Level;

namespace internal {
class Tensor;
}

namespace ir {
class Expr;
}

namespace storage {
class IteratorImpl;

/// A compile-time iterator over a tensor storage level. This class can be used
/// to generate the IR expressions for iterating over different level types.
class Iterator {
public:
  Iterator();

  static Iterator makeRoot();
  static Iterator make(std::string name, const ir::Expr& tensorVar,
                       int level, Level levelFormat);

  /// Returns the ptr variable for this iterator (e.g. `ja_ptr`). Ptr variables
  /// are used to index into the data at the next level (as well as the index
  /// arrays for formats such as sparse that have them).
  ir::Expr getPtrVar() const;

  /// Returns the index variable for this iterator (e.g. `ja`). Index variables
  /// are merged together using `min` in the emitted code to produce the loop
  /// index variable (e.g. `j`).
  ir::Expr getIdxVar() const;

  /// Returns the iterator variable. This is the variable that will iterate over
  /// the range [begin,end) with an increment of 1 in the emitted loop.
  ir::Expr getIteratorVar() const;

  /// Retrieves the expression that initializes the iterator variable before the
  /// loop starts executing.
  ir::Expr begin() const;

  /// Retrieves the expression that the iterator variable will be tested agains
  /// in the loop and that determines the end of the iterator.
  ir::Expr end() const;

  /// Returns a statement that initializes loop variables that are derived from
  /// the iterator variable.
  ir::Stmt initDerivedVar() const;

  bool defined() const;

private:
  std::shared_ptr<IteratorImpl> iterator;
};

std::ostream& operator<<(std::ostream&, const Iterator&);


/// Abstract class for iterators over different types of storage levels.
class IteratorImpl {
public:
  virtual ir::Expr getPtrVar() const = 0;
  virtual ir::Expr getIdxVar() const = 0;

  virtual ir::Expr getIteratorVar() const = 0;
  virtual ir::Expr begin() const = 0;
  virtual ir::Expr end() const = 0;

  virtual ir::Stmt initDerivedVars() const = 0;
};

}}
#endif
