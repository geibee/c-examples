#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>

int main() {
    struct timespec tp;
    int ret, policy;

    policy = sched_getscheduler(0);
    switch(policy) {
        case SCHED_OTHER:
            printf("Policy is normal\n");
            break;
        case SCHED_RR:
            printf("Policy is round-robin\n");
            break;
        case SCHED_FIFO:        
            printf("Policy is FIFO\n");
            break;
        case -1:        
            printf("sched_getscheduler");
            break;
        default:        
            fprintf(stderr, "unknown policy!\n");
    }

    ret = sched_rr_get_interval(0, &tp);
    if(ret == -1) {
        perror("sched_rr_get_interval");
        return 1;
    }

    printf("Our time quantum is %.2lf milliseconds\n",
           (tp.tv_sec * 1000.0f) + (tp.tv_sec / 1000000.0f)
    );
    return 0;
}