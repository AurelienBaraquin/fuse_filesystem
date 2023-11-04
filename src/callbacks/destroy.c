#include "tree.h"
#include "ffuse.h"

//* DESTROY __________________________________________________________________*/
void ffuse_destroy(void *private_data)
{
    (void) private_data;
    free_tree(sys_get_root());
}
