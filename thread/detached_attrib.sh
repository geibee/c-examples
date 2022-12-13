gcc -pthread detached_attrib.c -o detached_attrib
echo "sleepしないので、mainのほうが早く終了した場合、標準出力に何も表示されない"
./detached_attrib 0
echo "3秒sleepすると、標準出力に表示される"
./detached_attrib 3
rm detached_attrib
