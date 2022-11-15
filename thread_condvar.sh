gcc -pthread thread_condvar.c -o thread_condvar
echo "./thread_condvar foo bar foobar"
./thread_condvar foo bar foobar
rm thread_condvar
