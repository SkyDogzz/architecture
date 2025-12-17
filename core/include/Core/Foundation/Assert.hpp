#pragma once
#include <cstdlib>
#include <iostream>

#define CORE_ASSERT(x, msg)                                                    \
  do {                                                                         \
    if (!(x)) {                                                                \
      std::cerr << "[ASSERT] " << msg << "\n";                                 \
      std::abort();                                                            \
    }                                                                          \
  } while (0)
