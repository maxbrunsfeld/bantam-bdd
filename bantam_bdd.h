#ifndef __BANTAM_BDD__
#define __BANTAM_BDD__

#include "stdlib.h"
#ifdef __cplusplus
#include <functional>
#endif

#ifndef REPORT_TEST
#include "stdio.h"
#define REPORT_TEST(description, depth) \
  printf("%*s%s\n", (2 * depth), "", description);
#endif

#define RUN_TESTS(subject) \
  test_##subject();

#define TEST(subject) \
  void test_##subject() { \
    REPORT_TEST(#subject, 0) \
    int __last_run_depth = 0; \
    int __current_depth = 1; \
    int __previous_depth = 1; \
    __SETUP_HOOKS \
    (void)__current_depth; (void)__previous_depth; (void)__last_run_depth; \
    (void)__before_hooks; (void)__after_hooks;

#define END_TEST \
  __RUN_AFTER_HOOKS \
  free(__before_hooks); \
  free(__after_hooks); }

#define DESCRIBE(description) \
  REPORT_TEST(description, __current_depth) \
  __previous_depth = __current_depth; \
  for (__current_depth++; __current_depth > __previous_depth; __current_depth--)

#define IT(description) \
  __RUN_AFTER_HOOKS \
  REPORT_TEST(description, __current_depth) \
  __last_run_depth = __current_depth; \
  __RUN_BEFORE_HOOKS

#ifdef __cplusplus
#define BEFORE_EACH \
  __before_hooks[__current_depth] = [&]()

#define AFTER_EACH \
  __after_hooks[__current_depth] = [&]()
#else
#define BEFORE_EACH \
  auto void before_each(void); \
  __before_hooks[__current_depth] = before_each; \
  void before_each()

#define AFTER_EACH \
  auto void after_each(void); \
  __after_hooks[__current_depth] = after_each; \
  void after_each()
#endif

/*  Private  */

#ifdef __cplusplus
#define __SETUP_HOOKS \
  std::function<void()> *__before_hooks = (std::function<void()> *)(calloc(100, sizeof(*__before_hooks))); \
  std::function<void()> *__after_hooks  = (std::function<void()> *)(calloc(100, sizeof(*__after_hooks)));
#else
#define __SETUP_HOOKS \
  void (**__before_hooks)(void) = calloc(100, sizeof(*__before_hooks)); \
  void (**__after_hooks)(void)  = calloc(100, sizeof(*__after_hooks));
#endif

#define __RUN_AFTER_HOOKS \
  for (int __depth = __last_run_depth; __depth > 0; __depth--) { \
    if (__after_hooks[__depth]) __after_hooks[__depth](); \
  }

#define __RUN_BEFORE_HOOKS \
  for (int __depth = 0; __depth <= __current_depth; __depth++) { \
    if (__before_hooks[__depth]) __before_hooks[__depth](); \
  }

#endif
