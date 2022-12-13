mkfifo testfifo
cat testfifo &
echo test | tee testfifo
rm testfifo
