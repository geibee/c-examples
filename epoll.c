#include <sys/epoll.h>
#include <stdlib.h>
#define MAX_EVENTS 64

struct epoll_event *events;
int nr_events, i;

int epfd = epoll_create(100);
if (epfd < 0) {
    perror("epoll_create");
}

events = malloc(sizeof(struct epoll_event) * MAX_EVENTS);
if (!events) {
    perror("malloc");
    return 1;
}

nr_events = epoll_wait(epfd, events, MAX_EVENTS, -1);
if(nr_events < 0) {
    perror("epoll_wait");
    free(events);
    return 1;
}

for (i = 0; i < nr_events; i++) {
    printf("event=%u on fd=%d\n",
           events[i].events,
           events[i].data.fd
    );    
}

free(events);