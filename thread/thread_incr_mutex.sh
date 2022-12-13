gcc -pthread thread_incr_mutex.c -o thread_incr_mutex
echo "./thread_incr_mutex 10000"
./thread_incr_mutex 10000
rm thread_incr_mutex
