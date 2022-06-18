#include <bits/stdc++.h>
#include <stdlib.h>

using namespace std;

int main()
{
    /// read n
    /// check n range
    /// allocate space - malloc
    /// init matrix rand

    /// void* malloc(size_t)

    /// int** a;
    /// a = (int**)malloc(sizeof(int*)*n);
    /// for(int i=0; i<n; i++) {
    ///     a[i] = (int*)malloc(sizeof(int)*n);
    /// }

    /// free(void*)

    /// for(int i=0; i<n; i++) {
    ///     free(m[i]);
    ///     free(m);
    /// }

    /// ls - lists the working directory
    /// man - used for documentation
    /// CTRL + C - used to exit almost all comands
    /// q - used for exiting the man
    /// man ls - see manual for ls (for example, it works with any command)
    /// ls -l - list long; lists the working directory with all the details
    /// ls -la/-al - list long all; lists the working directory with all the details and hidden directories

/**drwx------  5 giie3115 student 4096 Nov  1 13:02 .
    drwxr-xr-x 31 root     root    4096 Oct  2 19:06 ..
    -rw-r--r--  1 giie3115 student   18 Mar 23  2017 .bash_logout
    -rw-r--r--  1 giie3115 student  176 Mar 23  2017 .bash_profile
    -rw-r--r--  1 giie3115 student  124 Mar 23  2017 .bashrc
    -rw-r--r--  1 giie3115 student  500 Nov 27  2014 .emacs
    drwxr-xr-x  2 giie3115 student 4096 Nov 12  2010 .gnome2
    drwx------  3 giie3115 student 4096 Nov  1 13:02 mail
    drwxr-xr-x  4 giie3115 student 4096 Sep 12  2012 .mozilla
**/
/**First column:
    d - directory
    - - regular file
    r - read
    w - write
    x - execute for file/exchange for directory

    ex. drwxr-xr-x = d o g ou = d --- --- ---
    o - rights for owners
    g - rights for users that are in the same group
    ou - rights for other users

    Second column:
    size in bytes

    Third column:
    creation details (owner, time)

**/
    /// cd $PATH - change directory
    /// mkdir $name - make directory
    /// rmdir $name - remove directory
    /// touch $name - create file
    /// pwd - print working directory
    /// rm $PATH - remove file
    /// rm -fR $name - remove files recursively (empty the directory $name)
    /// echo text - prints text on the screen
    /// echo text > $name - writes text in $name file
    /// cat $name - see the content of a text file
    /// echo text >> $name - appends text in $name file
    /// chmod $u $name - changes mode of the rights using binary rwx - 210 as bits, so to set rw- --- --x, we just 601 (man chmod, ex. chmod 400 1.txt)

    int n;
    int a[n][n];
    cin >> n;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            a[i][j] = rand()%91 + 10;
        }
    }

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            cout << a[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}
