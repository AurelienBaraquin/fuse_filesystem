# fuse_filesystem
*This is my first time using fuse and create a full filesystem in local, I'm doing this to understand the concept of filesystem and improve my competences about it to create a network filesystem then.*

## What is fuse?
FUSE (Filesystem in Userspace) is a simple interface for userspace programs to export a virtual filesystem to the Linux kernel. It also aims to provide a secure method for non privileged users to create and mount their own filesystem implementations.

## What is a filesystem?
A filesystem is a way to organize data in a storage device, it's a way to store, retrieve and update data in a storage device.

## What is a virtual filesystem?
A virtual filesystem is a filesystem that doesn't exist in a storage device, it's a way to organize data in a storage device but it's not a real filesystem, it's a way to organize data in a storage device using a software.



# My objectives in this repo :
- [x] Full binary tree filesystem
- [ ] Create / Delete / Read / Write   files / directories
- [ ] Add unique fonctionnalities like an auto git add or a auto make
- [ ] Add a way to keep data after reboot



## Final objectives :
- Create a network filesystem with client/server
- Encrypt data
- Add a compression system
- Add a way to store data in a database



### Binary tree filesystem

Exemple of a binary tree filesystem (you can find it in the file ***tree.c / tree.h***):

Using this code :
```c
// Test the tree
int main(void)
{
    sys_add_file("/home");
    sys_add_file("/home/user");
    sys_add_file("/home/user/file.txt");
    sys_add_file("/home/user/file2.txt");
    sys_add_file("/home/lala");
    sys_add_file("/home/lala/file.txt");
    sys_remove_file("/home/lala");
    sys_add_file("/home/lala");
    sys_add_file("/home/lala/file.txt");
    print_tree();
    free_tree(sys_get_root());
}
```

I get this output :
```
/
  /home
    /user
      /file.txt
      /file2.txt
    /lala
      /file.txt
```