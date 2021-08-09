#ifndef _STD_H_
#define _STD_H_
#include <alloc.h>
#include <math.h>
#include <fstream.h>
#include <stdlib.h>
#include "cpptypes.hpp"

class TSourceFile : public ifstream
 {
  public:
   TSourceFile(char* FileName):ifstream(FileName){};
   word Get()
    {
     word Result;
     (*this)>>Result;
     return Result;
    };
 };

#include "math_cls.hpp"
#include "memarray.hpp"

#include "interval.hpp"
#include "polin's.hpp"
#include "links.hpp"
//#include "graph.hpp"

#endif
