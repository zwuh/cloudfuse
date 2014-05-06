#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include "cache.h"
#include "cloudfsapi.h"

/* Thread function for the cache synchronization daemon */
void *cache_sync_worker(void *ptr_cache)
{
 /* TODO: arg should be the "cache" */
 time_t last_sync, current;
 int rval;

 last_sync = time(NULL);

 for (;;)
 {
  current = time(NULL);
  if (current - last_sync >= sync_cycle) {
   rval = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
   if (0 != rval) {
    handle_error(rval, "pthread_setcancelstate(DISABLE)");
   }
   cache_flush_all(ptr_cache);
   last_sync = time(NULL);
   rval = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
   if (0 != rval) {
    handle_error(rval, "pthread_setcancelstate(ENABLE)");
   }
  }
  sleep(1);
 }
 pthread_exit(NULL);
}

void cache_flush_all(void *ptr_cache)
{
  /* TODO: scan through the cache, look for dirty entries, sync them to cloud */
}

void *cache_init(void)
{
  /* TODO: allocate and initialize a cache */
  return NULL;
}

void cache_destroy(void *ptr_cache)
{
 cache_flush_all(ptr_cache);
 /* TODO: destroy the cache */
}

