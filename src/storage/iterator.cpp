#include "iterator.h"

#include "expr.h"
#include "internal_tensor.h"
#include "ir.h"

#include "root_iterator.h"
#include "dense_iterator.h"
#include "sparse_iterator.h"

using namespace std;

namespace taco {
namespace storage {

// class Iterator
Iterator::Iterator() {
}

Iterator Iterator::makeRoot() {
  Iterator iterator;
  iterator.iterator = std::make_shared<RootIterator>();
  return iterator;
}

Iterator Iterator::make(string name, const ir::Expr& tensorVar,
                        int level, Level levelFormat) {
  Iterator iterator;

  // TODO: Remove
  switch (levelFormat.getType()) {
    case LevelType::Dense:
      iterator.iterator = std::make_shared<DenseIterator>(name, tensorVar);
      break;
    case LevelType::Sparse:
      iterator.iterator = std::make_shared<SparseIterator>(name, tensorVar);
      break;
    case LevelType::Fixed:
      break;
  }
  iassert(iterator.defined());
  return iterator;
}

ir::Expr Iterator::getPtrVar() const {
  return iterator->getPtrVar();
}

ir::Expr Iterator::getIdxVar() const {
  return iterator->getIdxVar();
}

bool Iterator::defined() const {
  return iterator != nullptr;
}

std::ostream& operator<<(std::ostream& os, const Iterator& iterator) {
  return os << iterator.getPtrVar();
}

}}
