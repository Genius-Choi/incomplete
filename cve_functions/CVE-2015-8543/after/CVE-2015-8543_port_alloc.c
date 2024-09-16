static unsigned short port_alloc(struct sock *sk)
{
	struct dn_scp *scp = DN_SK(sk);
static unsigned short port = 0x2000;
	unsigned short i_port = port;

	while(check_port(cpu_to_le16(++port)) != 0) {
		if (port == i_port)
			return 0;
	}

	scp->addrloc = cpu_to_le16(port);

	return 1;
}
