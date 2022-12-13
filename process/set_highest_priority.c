#define _GNU_SOURCE
#include <sys/types.h>
#include <sched.h>

int set_highest_priority(pid_t pid) {
    struct sched_param sp;
    int policy, max, ret;

    policy = sched_getscheduler(pid);
    if(policy == -1)
        return -1;
    
    max = sched_get_priority_max(policy);
    if(max == -1)
        return -1;
    
    memset(&sp, 0, sizeof(struct sched_param));
    sp.sched_priority = max;
    ret = sched_setparam(pid, &sp);

    return ret;
}

int main() {
    int ret;
    
    ret = set_highest_priority(0);
    if(ret == -1) {
        return -1;
    }
    return 0;
}
