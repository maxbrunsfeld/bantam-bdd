bantam-bdd
==========

This is a minimalistic BDD framework for C. It consists of a single header file, `bantam_bdd.h`.

Example
-------

```c
#include "bantam_bdd.h"
#include "assert.h"

TEST(integer_math)
{
  int x, y;

  BEFORE_EACH {
    x = 5;
    y = 7;
  }

  AFTER_EACH {
    x = y = 0;
  }
  
  DESCRIBE("addition") {
    IT("is commutative") {
      assert((x + y) == (y + x));
    }
  }
  
  DESCRIBE("subtraction") {
    int z;
    
    BEFORE_EACH {
      z = 11;
    }
    
    IT("is not associative") {
      assert((x - y - z) != (x - (y - z)));
    }
  }
}

END_TEST

int main()
{
  RUN_TESTS(integer_math);
}

```
