# fuse_filesystem
*This is my first time using fuse and create a full filesystem in local, I'm doing this to understand the concept of filesystem and improve my competences about it to create a network filesystem then.*

## ***Before you start***
### **Dependencies**
- [libfuse-dev] (Filesystem in userspace) (https://packages.debian.org/fr/sid/libfuse-dev)
- [check] (Unit testing framework for C) (https://packages.debian.org/fr/sid/check)
- [make] (GNU Make) (https://packages.debian.org/fr/sid/make)

### **How to install dependencies**
> **Note**
>
> This is for Debian based distributions, you can find the dependencies for your distribution on the links above.

```bash
sudo apt-get install libfuse-dev check make
```

### What is fuse?
FUSE (Filesystem in Userspace) is a simple interface for userspace programs to export a virtual filesystem to the Linux kernel. It also aims to provide a secure method for non privileged users to create and mount their own filesystem implementations.

### What is a filesystem?
A filesystem is a way to organize data in a storage device, it's a way to store, retrieve and update data in a storage device.

### What is a virtual filesystem?
A virtual filesystem is a filesystem that doesn't exist in a storage device, it's a way to organize data in a storage device but it's not a real filesystem, it's a way to organize data in a storage device using a software.



## My objectives in this repo :
- [x] Full binary tree filesystem
- [x] Create / Delete / Read / Write   files / directories
- [ ] Set all callbacks from fuse and of course make them work
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
    init_root();
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

## Supported Callbacks

***From the filesystem***

> **Note**
>
> The listed callbacks that are not yet implemented (indicated with ❌) are in development and will be supported in
> later releases.

| Callbacks         | Implemented  |
|-------------------|-------------:|
| getattr           |       ✔️      | 
| readdir           |       ✔️      |
| open              |       ❌     |
| read              |       ✔️      |
| write             |       ✔️      |
| create            |       ✔️      |
| unlink            |       ❌     |
| mkdir             |       ✔️      |
| rmdir             |       ❌     |
| rename            |       ❌     |
| truncate          |       ❌     |
| utimens           |       ❌     |
| chmod             |       ❌     |
| chown             |       ❌     |
| link              |       ❌     |
| symlink           |       ❌     |
| readlink          |       ❌     |
| release           |       ❌     |
| destroy           |       ❌     |


## How to use it

### Compile the project

> **Note**
>
> You need to have the dependencies installed before compiling the project.
> *See [Before you start](#before-you-start)*

```bash
make
```

### Run the project
```bash
./myfuse [flags] [mountpoint]
```

### Flags
| Flags             | Description  |
|-------------------|-------------:|
| -d                | Enable debug mode |
| -f                | Run in foreground |
| -s                | Disable multi-threaded operation |
| -h                | Print help message |
| -V                | Print version number |

### Mountpoint
The mountpoint is the path where you want to mount the filesystem.

> *You can use a simple **empty** directory to mount the filesystem.*

## How to test it

### Compile the project & run the tests
```bash
make test
```

> That will compile the project and run the tests.
> *You can see in output the tests results.*

The tester executable isn't cleaned after the tests, you can run it again with :
```bash
./run_tests
```
