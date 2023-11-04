# fuse_filesystem
*This is my first time using fuse and create a full filesystem in local, I'm doing this to understand the concept of filesystem and improve my competences about it to create a network filesystem then.*

## ***Before you start***
### **Dependencies**
- [libfuse-dev] (Filesystem in userspace) (https://packages.debian.org/fr/sid/libfuse-dev)
- [check] (Unit testing framework for C) (https://packages.debian.org/fr/sid/check)
- [make] (GNU Make) (https://packages.debian.org/fr/sid/make)
- [gcc] (GNU C compiler) (https://packages.debian.org/fr/sid/gcc)
- [Test::More] (Perl module) (https://metacpan.org/pod/Test::More)

### **How to install dependencies**
> **Note**
>
> This is for Debian based distributions, you can find the dependencies for your distribution on the links above.

***Execute this shell script to install all the dependencies :***
```bash
sudo ./setup.sh
```

***Or you can install them manually :***

```bash
sudo apt-get install libfuse-dev check make gcc perl perl-base
```
```bash
cpan Test::More
```

### What is fuse?
FUSE (Filesystem in Userspace) is a simple interface for userspace programs to export a virtual filesystem to the Linux kernel. It also aims to provide a secure method for non privileged users to create and mount their own filesystem implementations.

> **Note**
>
> See more in [About FUSE](#about-fuse)

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

| Callbacks         | Implemented  | Description  |
|-------------------|:------------:|:-------------|
| getattr           |       ✔️      | Get attributes of a file. | 
| readdir           |       ✔️      | Read the contents of a directory. |
| open              |       ❌     | Open a file. |
| read              |       ✔️      | Read data from a file. |
| write             |       ✔️      | Write data to a file. |
| create            |       ✔️      | Create a file. |
| unlink            |       ✔️      | Delete a file. |
| mkdir             |       ✔️      | Create a directory. |
| rmdir             |       ✔️     | Delete a directory. |
| rename            |       ✔️     | Rename a file or directory. |
| truncate          |       ✔️     | Modify the size of a file. |
| utimens           |       ❌     | Modify the access and modification times of a file. |
| chmod             |       ❌     | Modify the permissions of a file. |
| chown             |       ❌     | Change the owner or group of a file. |
| link              |       ❌     | Create a hard link. |
| symlink           |       ❌     | Create a symbolic link. |
| readlink          |       ❌     | Read the target of a symbolic link. |
| release           |       ❌     | Close a file. |
| destroy           |       ✔️      | Destroy the filesystem data structure. |
| flush             |       ✔️     | Flush cached resources. |
| fsync             |       ❌     | Synchronize modifications to a file. |
| setxattr          |       ❌     | Set an extended attribute. |
| getxattr          |       ❌     | Get an extended attribute. |
| listxattr         |       ❌     | List extended attributes. |
| removexattr       |       ❌     | Remove an extended attribute. |
| mknod             |       ❌     | Create a special or ordinary file. |
| statfs            |       ❌     | Get filesystem statistics. |
| opendir           |       ❌     | Open a directory. |
| releasedir        |       ❌     | Close a directory. |
| fsyncdir          |       ❌     | Synchronize modifications to a directory. |
| init              |       ✔️      | Initialize the filesystem. This is often used to set up global resources. |
| access            |       ❌     | Check access permissions for a file. |
| ftruncate         |       ❌     | Modify the size of an open file. |
| fgetattr          |       ❌     | Get the attributes of an open file. |
| lock              |       ❌     | Apply file locking. |

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

***If you want to unmount the filesystem you can use :***
```bash
fusermount -u [mountpoint]
```

or
  
```bash
umount [mountpoint]
```

## How to test it

### Compile the project as test mode & run tests

***Unit tests***
```bash
make unitest
```

> That will compile the project and run the tests.
> *You can see in output the tests results.*

The tester executable isn't cleaned after the tests, you can run it again with :
```bash
./run_unitests
```

***Integration tests***
*Using test/fuse_test.pl and the library Test::More ([See dependencies](#dependencies))

```bash
make fusetest
```

> That will compile the project and run the tests.
> *You can see in output the tests results.*

## About FUSE

> **Note**
>
> Here I only talk about technical things, like how it works, how to use it, etc...

### What is a Callback?

A callback is a function that is called when an event occurs, for example when try to read a file, the callback read is called.
See [Supported Callbacks](#supported-callbacks) to see all the callbacks supported by this project.

Some callbacks have others utilities, for example the callback **getattr** is used to get the attributes of a file, but it's also used to check if a file exist
or **init** is used to initialize the filesystem but it's also used to set up global resources.

> **By the way I want to speak about init**
>
> Like I said init is used to initialize the filesystem but it's also used to set up global resources, so I use it to initialize the tree and set up global resources.
> But as you can see if you use it, the callback take two struct as params : **struct fuse_conn_info** and **struct fuse_config**.
> - **struct fuse_conn_info** is used to set up the connection with the filesystem.
> - **struct fuse_config** is used to set up the filesystem.
>
> In my case I use fuse_config->remove_hard = 1; this make the filesystem able to remove file / directory even if there is a process that use it. (It's useful when I encounter a bug and I can't remove a file / directory because it's used by a process)
>
> I also use **destroy** to free the tree and all the resources used by the filesystem.
