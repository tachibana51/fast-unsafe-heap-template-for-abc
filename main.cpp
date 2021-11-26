//using fast unsafe heap(fuh) by douro(a.k.a. internal_human)

//fuh
#include <sys/mman.h>
#include <malloc.h>
#define BASE_P 0x10000
//end fuhscope

//fuh
static void my_init_hook(void);
static void *my_malloc_hook(size_t, const void *);
static void my_free_hook(void *, const void *);
static void *(*old_malloc_hook)(size_t, const void *);
void (*__malloc_initialize_hook)(void) = my_init_hook;
static void *mymap;
static size_t top = BASE_P;
//end fuhscope

//fuh
static void my_init_hook(void)
{
    //alloc 200MB memory
    mymap = mmap((void *)BASE_P, 200 * 1024 * 1024, PROT_READ | PROT_WRITE,
                 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    __malloc_hook = my_malloc_hook;
    __free_hook = my_free_hook;
}

static void my_free_hook(void *addr, const void *caller)
{
}

static void *my_malloc_hook(size_t size, const void *caller)
{
    void *result;
    result = (void *)top;
    top += size;
    return result;
}
//end fuhscope

int main()
{
    //fuh
    my_init_hook();
    //end fuhscope

    // chall code...
}

