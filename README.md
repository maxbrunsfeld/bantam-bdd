bantam-bdd
==========

Bantam is a minimalist [BDD](http://dannorth.net/introducing-bdd/)-style testing library for C. It helps you to write clean and readable tests,
and consists of only a single header file.

Setup
-----

- Add `bantam_bdd.h` to your project.
- Compile your tests with nested functions enabled, using `gcc -fnested-functions`.

Usage
-----

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

Running this program produces this output:

```
integer_math
  addition
    is commutative
  subtraction
    is not associative
```
