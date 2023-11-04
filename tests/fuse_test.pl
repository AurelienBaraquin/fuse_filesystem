#!/usr/bin/perl
use strict;
use warnings;
use Test::More tests => 7; # The number here must correspond to the total number of tests
use File::Path qw(make_path remove_tree);

# Directory to mount the FUSE file system
my $test_dir = "./test_dir";

# Unmount the FUSE file system if necessary
system("umount $test_dir > /dev/null 2>&1");

# Create directory if necessary
unless (-d $test_dir) {
    make_path($test_dir) or die "Could not create test directory: $!";
}

# Mount the FUSE file system (example system call)
system("./myfuse $test_dir") == 0 or die "Could not mount FUSE filesystem: $!";




#* TESTS ______________________________________________________________________

# Test 1: Create a file with touch
my $file_name = "$test_dir/file.txt";
system("touch $file_name");
system("ls -l $file_name") == 0 or stop_tester("Could not create file: $!", $test_dir);
ok(-e $file_name, 'File creation test with touch');

# Test 2: Remove a file with rm
system("rm $file_name") == 0 or stop_tester("Could not remove file: $!", $test_dir);
ok(!-e $file_name, 'File removal test with rm');

# Test 3: Create a directory with mkdir
my $dir_name = "$test_dir/dir";
make_path($dir_name) or stop_tester("Could not create directory: $!", $test_dir);
ok(-d $dir_name, 'Directory creation test with mkdir');

# Test 4: Create a file in a directory and verify with ls
system("touch $dir_name/file.txt");
system("ls -l $dir_name") == 0 or stop_tester("Could not list directory: $!", $test_dir);
ok(-e "$dir_name/file.txt", 'File creation test in directory');

#Test 5: Create a file with echo
system("echo 'Hello World!' > $file_name");
system("ls -l $file_name") == 0 or stop_tester("Could not create file: $!", $test_dir);
ok(-e $file_name, 'File creation test with echo');

# Test 6: Read a file with cat
system("cat $file_name") == 0 or stop_tester("Could not read file: $!", $test_dir);
ok(-e $file_name, 'File read test with cat');

# Test 7: Write to a file with echo
system("echo 'HIIII' > $file_name");
system("ls -l $file_name") == 0 or stop_tester("Could not write to file: $!", $test_dir);
ok(-e $file_name, 'File write test with echo');

#* ___________________________________________________________________________




# Cleanup and unmount the FUSE file system
system("umount $test_dir > /dev/null 2>&1");

done_testing();
print "Tests passed!\n";
exit 0;

sub stop_tester {
    my ($error_msg, $test_dir) = @_;
    diag($error_msg);
    system("fusermount -u $test_dir") == 0 or diag("Could not unmount FUSE filesystem: $!");
    remove_tree($test_dir);
    done_testing();
    exit 1;
}
