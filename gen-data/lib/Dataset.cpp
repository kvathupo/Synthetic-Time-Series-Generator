#include "Dataset.h"

// Must define pure virtual destructor to properly unravel the destructors
// called from derived objects. Otherwise, compile-time error.
Dataset::~Dataset() {}
