#include "visiting.h"

// visitor //

/**
 * Overloaded in specializations of the Visitor class.
 * @param visitable some visitable object
 */
void Visitor::
visit(Visitable visitable)
{}


// visitable //

[[maybe_unused]]
void Visitable::
accept(Visitor visitor)
{}