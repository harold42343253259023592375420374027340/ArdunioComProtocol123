2|- ONLINE, out  <br>
3|- RECV, in <br>
4|- SEND, out <br>
5|- CLK, in <br>
6|- ERECV (ENABLE RECEIVING)

int ips[256]

server::on_connect:
    send(ip) // give them ip, simaler to DHCP <br>
    send(0x69) // magic number to tell, you are ready <br>

server::no_ip_found: <br>
    send(sender, 0x0, 0, 0, 0, 0, 0) <br>


3bytes <br>
[to | ip] [from | ip] [0, for now] [length | Byte] [data | bytes] [sum of data high] [sum of data low]

2, 1, NONE, 3, the, sum <br>
00000010 00000001 00000000 00000011 byte byte byte 00000001 00000011