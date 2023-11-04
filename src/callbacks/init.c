#include "tree.h"
#include "ffuse.h"

//* INIT ____________________________________________________________________*/
/* Call on filesystem mount before any other operation */
void *ffuse_init(struct fuse_conn_info *conn, struct fuse_config *cfg)
{
    init_root();

    (void) conn; // conn store connection to the filesystem information
    (void) cfg; // cfg store configuration of the filesystem

    cfg->hard_remove = 1;

    return NULL; // Null as success
}
