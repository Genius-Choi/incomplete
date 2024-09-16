static int help(struct sk_buff *skb, unsigned int protoff,
		struct nf_conn *ct,
		enum ip_conntrack_info ctinfo)
{
	int dir = CTINFO2DIR(ctinfo);
	unsigned int ret;
	const struct iphdr *iph = ip_hdr(skb);
	const struct udphdr *udph = (struct udphdr *)((__be32 *)iph + iph->ihl);

	/* SNMP replies and originating SNMP traps get mangled */
	if (udph->source == htons(SNMP_PORT) && dir != IP_CT_DIR_REPLY)
		return NF_ACCEPT;
	if (udph->dest == htons(SNMP_TRAP_PORT) && dir != IP_CT_DIR_ORIGINAL)
		return NF_ACCEPT;

	/* No NAT? */
	if (!(ct->status & IPS_NAT_MASK))
		return NF_ACCEPT;

	/* Make sure the packet length is ok.  So far, we were only guaranteed
	 * to have a valid length IP header plus 8 bytes, which means we have
	 * enough room for a UDP header.  Just verify the UDP length field so we
	 * can mess around with the payload.
	 */
	if (ntohs(udph->len) != skb->len - (iph->ihl << 2)) {
		nf_ct_helper_log(skb, ct, "dropping malformed packet\n");
		return NF_DROP;
	}

	if (!skb_make_writable(skb, skb->len)) {
		nf_ct_helper_log(skb, ct, "cannot mangle packet");
		return NF_DROP;
	}

	spin_lock_bh(&snmp_lock);
	ret = snmp_translate(ct, dir, skb);
	spin_unlock_bh(&snmp_lock);
	return ret;
}
