rm ./fifo_seqnum_client 
gcc fifo_seqnum_client.c -o fifo_seqnum_client
./fifo_seqnum_client 3
./fifo_seqnum_client 2
rm ./fifo_seqnum_client 
rm ./fifo_seqnum_server 
