#ifndef __CACHE_H
#define __CACHE_H

int sync_cycle;

void *cache_sync_worker(void *ptr_cache);
void cache_flush_all(void *ptr_cache);
void *cache_init(void);
void cache_destroy(void *ptr_cache);

#endif

