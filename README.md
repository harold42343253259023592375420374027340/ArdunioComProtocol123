2|- ONLINE, out
3|- RECV, in
4|- SEND, out
5|- CLK, in
6|- ERECV (ENABLE RECEIVING)

int ips[256]

server::on_connect:
    send(ip) // give them ip, simaler to DHCP
    send(0x69) // magic number to tell, you are ready

server::no_ip_found:
    send(sender, 0x0, 0, 0, 0, 0, 0)


3bytes
[to | ip] [from | ip] [0, for now] [length | Byte] [data | bytes] [sum of data high] [sum of data low]

2, 1, NONE, 3, the, sum 
00000010 00000001 00000000 00000011 byte byte byte 00000001 00000011