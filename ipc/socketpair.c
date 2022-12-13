/*
        socketpair-rw.c -- socketpair() による双方向通信
        ~yas/syspro1-1998/ipc/socketpair-rw.c
        $Header: /home/lab2/OS/yas/syspro1-1998/ipc/RCS/socketpair-rw.c,v 1.2 1998/06/01 15:18:20 yas Exp $
        Start: 1997/05/26 21:29:34
*/

// https://stackoverflow.com/questions/11461106/socketpair-in-c-unix
// https://www.web-dev-qa-db-ja.com/ja/c/c-unix%E3%81%AEsocketpair%EF%BC%88%EF%BC%89/1068146938/
#include <stdio.h>
#include <sys/types.h>  /* fork(), socketpair() */
#include <unistd.h>     /* fork() */
#include <sys/socket.h> /* socketpair() */

void parent( int fd );
void child( int fd );

main()
{
    int fildes[2] ;
    pid_t pid ;

        if( socketpair(AF_UNIX,SOCK_STREAM,0,fildes) == -1)
        {
            perror("socketpair");
            exit( 1 );
        }
        /* fildes[0] -- その１
         * fildes[1] -- その２
         */
        if( (pid=fork()) == 0 )
        {
            printf("this is child process");
            close( fildes[1] );
            child( fildes[0] );
        }
        else if( pid > 0 )
        {
            printf("this is parent process");
            close( fildes[0] );
            parent( fildes[1] );
        }
        else
        {
            printf("fork failed");
            perror("fork");
            exit( 1 );
        }
}

void parent( int fd )
{
    char *p,c,ret ;
        p = "hello,world\n" ;
        while( c = *p++ )
        {
            if( write( fd, &c, 1 ) != 1 )
                perror("write");
            if( read( fd, &ret, 1 ) != 1 )
                perror("read");
            putchar( ret );
        }
        close( fd );
}

void child( int fd )
{
    char c,*p,ret ;
    char buf[1024];

    p = "Hello,World\n";
        while( read(fd,&c,1) == 1 )
        {
            c = toupper( c );
            if( write( fd,&c,1 ) != 1 )
                perror("read");
        }
        close( fd );
}