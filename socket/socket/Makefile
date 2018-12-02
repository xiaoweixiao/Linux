all:tcp_client ttcp_server
ttcp_server:ttcp_server.c
	gcc $^ -o $@ -pthread
ptcp_server:ptcp_server.c
	gcc $^ -o $@
tcp_client:tcp_client.c
	gcc $^ -o $@
tcp_server:tcp_server.c
	gcc $^ -o $@
udp_client:udp_client.c
	gcc $^ -o $@
udp_server:udp_server.c
	gcc $^ -o $@
