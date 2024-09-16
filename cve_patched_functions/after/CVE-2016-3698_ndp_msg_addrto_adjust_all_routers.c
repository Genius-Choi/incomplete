static void ndp_msg_addrto_adjust_all_routers(struct in6_addr *addr)
{
	struct in6_addr any = IN6ADDR_ANY_INIT;

	if (memcmp(addr, &any, sizeof(any)))
		return;
	addr->s6_addr32[0] = htonl(0xFF020000);
	addr->s6_addr32[1] = 0;
	addr->s6_addr32[2] = 0;
	addr->s6_addr32[3] = htonl(0x2);
}
