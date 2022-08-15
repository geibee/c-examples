#define MAX_EVENTS 64
#include <stdlib.h>
#include <stdio.h>
#include <sys/epoll.h>
#include <fcntl.h>

int main() {
    struct epoll_event event;
    struct epoll_event *events;
    int fd, ret, nr_events, i, epfd;
    char *buf[] = {
        "The term buccaneer comes from the word boucan.\n",
        "A boucan is a wooden frame used for cooking meat.\n",
        "Buccaneer is the West Indies name for a pirate.\n"
    };
   

    if(mkfifo("test.fifo", 0666) == -1) {
        perror("mkfifo");
    }

    if((fd = open("test.fifo", O_WRONLY)) == -1) {
        perror("open");
        exit(-1);
    }

    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLOUT;

    epfd = epoll_create(100);
    if(epfd < 0) {
        perror("epoll_create");
    }


    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event);
    if(ret) {
        perror("epoll_ctl");
    }

    events = malloc(sizeof(struct epoll_event) * MAX_EVENTS);
    if(!events) {
        perror("malloc");
        return 1;
    }

    nr_events = epoll_wait(epfd, events, MAX_EVENTS, -1);
    if (nr_events < 0) {
        perror("epoll_wait");
        free(events);
        return 1;
    }

    write(fd, buf, strlen(buf));

    for(i = 0; i < nr_events; i++) {
        printf("event=%u on fd=%d\n",
            events[i].events,
            events[i].data.fd
        );    
    }

    free(events);
    close(epfd);

    return 0;
} 