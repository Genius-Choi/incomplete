static unsigned int hns_nic_get_headlen(unsigned char *data, u32 flag,
					unsigned int max_size)
{
	unsigned char *network;
	u8 hlen;

	/* this should never happen, but better safe than sorry */
	if (max_size < ETH_HLEN)
		return max_size;

	/* initialize network frame pointer */
	network = data;

	/* set first protocol and move network header forward */
	network += ETH_HLEN;

	/* handle any vlan tag if present */
	if (hnae_get_field(flag, HNS_RXD_VLAN_M, HNS_RXD_VLAN_S)
		== HNS_RX_FLAG_VLAN_PRESENT) {
		if ((typeof(max_size))(network - data) > (max_size - VLAN_HLEN))
			return max_size;

		network += VLAN_HLEN;
	}

	/* handle L3 protocols */
	if (hnae_get_field(flag, HNS_RXD_L3ID_M, HNS_RXD_L3ID_S)
		== HNS_RX_FLAG_L3ID_IPV4) {
		if ((typeof(max_size))(network - data) >
		    (max_size - sizeof(struct iphdr)))
			return max_size;

		/* access ihl as a u8 to avoid unaligned access on ia64 */
		hlen = (network[0] & 0x0F) << 2;

		/* verify hlen meets minimum size requirements */
		if (hlen < sizeof(struct iphdr))
			return network - data;

		/* record next protocol if header is present */
	} else if (hnae_get_field(flag, HNS_RXD_L3ID_M, HNS_RXD_L3ID_S)
		== HNS_RX_FLAG_L3ID_IPV6) {
		if ((typeof(max_size))(network - data) >
		    (max_size - sizeof(struct ipv6hdr)))
			return max_size;

		/* record next protocol */
		hlen = sizeof(struct ipv6hdr);
	} else {
		return network - data;
	}

	/* relocate pointer to start of L4 header */
	network += hlen;

	/* finally sort out TCP/UDP */
	if (hnae_get_field(flag, HNS_RXD_L4ID_M, HNS_RXD_L4ID_S)
		== HNS_RX_FLAG_L4ID_TCP) {
		if ((typeof(max_size))(network - data) >
		    (max_size - sizeof(struct tcphdr)))
			return max_size;

		/* access doff as a u8 to avoid unaligned access on ia64 */
		hlen = (network[12] & 0xF0) >> 2;

		/* verify hlen meets minimum size requirements */
		if (hlen < sizeof(struct tcphdr))
			return network - data;

		network += hlen;
	} else if (hnae_get_field(flag, HNS_RXD_L4ID_M, HNS_RXD_L4ID_S)
		== HNS_RX_FLAG_L4ID_UDP) {
		if ((typeof(max_size))(network - data) >
		    (max_size - sizeof(struct udphdr)))
			return max_size;

		network += sizeof(struct udphdr);
	}

	/* If everything has gone correctly network should be the
	 * data section of the packet and will be the end of the header.
	 * If not then it probably represents the end of the last recognized
	 * header.
	 */
	if ((typeof(max_size))(network - data) < max_size)
		return network - data;
	else
		return max_size;
}
