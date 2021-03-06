#include "error_messages.h"

namespace taco {
namespace error {

const std::string type_mismatch =
  "Type mismatch.";

const std::string type_bitwidt =
  "The given bit width is not supported for this type.";

const std::string expr_dimension_mismatch =
  "Dimension size mismatch.";

const std::string expr_transposition =
  "Computations with transpositions are not supported, but are planned for the "
  "future.";

const std::string expr_distribution =
  "Expressions with free variables that do not appear on the right hand side "
  "of the expression are not supported, but are planned for the future";

const std::string compile_without_expr =
  "An index expression must be defined before compile is called.";

const std::string assemble_without_compile =
  "The compile method must be called before assemble.";

const std::string compute_without_compile =
   "The compile method must be called before compute.";

const std::string requires_matrix =
    "The argument must be a matrix.";

}}
