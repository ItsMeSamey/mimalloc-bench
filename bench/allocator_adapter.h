#ifndef MIMALLOC_BENCH_ALLOCATOR_ADAPTER_H
#define MIMALLOC_BENCH_ALLOCATOR_ADAPTER_H

#include <stddef.h>
#include <stdlib.h>

#if defined(__cplusplus)
#define BENCH_EXTERN_C extern "C"
#else
#define BENCH_EXTERN_C extern
#endif

#if defined(__GNUC__) || defined(__clang__)
#define BENCH_WEAK __attribute__((weak))
#else
#define BENCH_WEAK
#endif

BENCH_EXTERN_C void* mimalloc_bench_alloc(size_t size) BENCH_WEAK;
BENCH_EXTERN_C void mimalloc_bench_free_sized(void* p, size_t size) BENCH_WEAK;
BENCH_EXTERN_C void mimalloc_bench_thread_done(void) BENCH_WEAK;

static inline void* bench_alloc(size_t size) {
  return mimalloc_bench_alloc != NULL ? mimalloc_bench_alloc(size) : malloc(size);
}

static inline void bench_free_sized(void* p, size_t size) {
  if (p == NULL) return;
  if (mimalloc_bench_free_sized != NULL) mimalloc_bench_free_sized(p, size);
  else free(p);
}

static inline void bench_thread_done(void) {
  if (mimalloc_bench_thread_done != NULL) mimalloc_bench_thread_done();
}

#endif
