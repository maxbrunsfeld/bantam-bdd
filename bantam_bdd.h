#ifndef __BANTAM_BDD__
#define __BANTAM_BDD__

#include "stdio.h"

#define RUN_TESTS(subject) \
  test_##subject();

#define TEST(subject) \
  void test_##subject() { \
    int __last_run_depth = -1; \
    int __current_depth = 0; \
    int __previous_depth = 0; __previous_depth = __previous_depth; \
    void (**__before_fns)(void) = calloc(100, sizeof(void *)); \
    void (**__after_fns)(void) = calloc(100, sizeof(void *)); \
    printf("\n%s\n", #subject);

#define END_TEST \
  __run_after_each__ }

#define DESCRIBE(description) \
  __print_description(description); \
  __previous_depth = __current_depth; \
  for (__current_depth++; __current_depth > __previous_depth; __current_depth--)

#define BEFORE_EACH \
  auto void before_each(void); \
  __before_fns[__current_depth] = before_each; \
  void before_each()

#define AFTER_EACH \
  auto void after_each(void); \
  __after_fns[__current_depth] = after_each; \
  void after_each()

#define IT(description) \
  __run_after_each__ \
  __print_description(description); \
  __last_run_depth = __current_depth; \
  __run_before_each__

// private

#define __print_description(description) \
  printf("%*s%s\n", (2 * (__current_depth + 1)), " ", description);

#define __run_after_each__ \
  for (int __depth_i = __last_run_depth; __depth_i >= 0; __depth_i--) { \
    if (__after_fns[__depth_i]) __after_fns[__depth_i](); \
  }

#define __run_before_each__ \
  for (int __depth_i = 0; __depth_i <= __current_depth; __depth_i++) { \
    if (__before_fns[__depth_i]) __before_fns[__depth_i](); \
  }

#endif
