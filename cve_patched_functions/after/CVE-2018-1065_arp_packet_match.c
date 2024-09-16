static inline int arp_packet_match(const struct arphdr *arphdr,
				   struct net_device *dev,
				   const char *indev,
				   const char *outdev,
				   const struct arpt_arp *arpinfo)
{
	const char *arpptr = (char *)(arphdr + 1);
	const char *src_devaddr, *tgt_devaddr;
	__be32 src_ipaddr, tgt_ipaddr;
	long ret;

	if (NF_INVF(arpinfo, ARPT_INV_ARPOP,
		    (arphdr->ar_op & arpinfo->arpop_mask) != arpinfo->arpop))
		return 0;

	if (NF_INVF(arpinfo, ARPT_INV_ARPHRD,
		    (arphdr->ar_hrd & arpinfo->arhrd_mask) != arpinfo->arhrd))
		return 0;

	if (NF_INVF(arpinfo, ARPT_INV_ARPPRO,
		    (arphdr->ar_pro & arpinfo->arpro_mask) != arpinfo->arpro))
		return 0;

	if (NF_INVF(arpinfo, ARPT_INV_ARPHLN,
		    (arphdr->ar_hln & arpinfo->arhln_mask) != arpinfo->arhln))
		return 0;

	src_devaddr = arpptr;
	arpptr += dev->addr_len;
	memcpy(&src_ipaddr, arpptr, sizeof(u32));
	arpptr += sizeof(u32);
	tgt_devaddr = arpptr;
	arpptr += dev->addr_len;
	memcpy(&tgt_ipaddr, arpptr, sizeof(u32));

	if (NF_INVF(arpinfo, ARPT_INV_SRCDEVADDR,
		    arp_devaddr_compare(&arpinfo->src_devaddr, src_devaddr,
					dev->addr_len)) ||
	    NF_INVF(arpinfo, ARPT_INV_TGTDEVADDR,
		    arp_devaddr_compare(&arpinfo->tgt_devaddr, tgt_devaddr,
					dev->addr_len)))
		return 0;

	if (NF_INVF(arpinfo, ARPT_INV_SRCIP,
		    (src_ipaddr & arpinfo->smsk.s_addr) != arpinfo->src.s_addr) ||
	    NF_INVF(arpinfo, ARPT_INV_TGTIP,
		    (tgt_ipaddr & arpinfo->tmsk.s_addr) != arpinfo->tgt.s_addr))
		return 0;

	/* Look for ifname matches.  */
	ret = ifname_compare(indev, arpinfo->iniface, arpinfo->iniface_mask);

	if (NF_INVF(arpinfo, ARPT_INV_VIA_IN, ret != 0))
		return 0;

	ret = ifname_compare(outdev, arpinfo->outiface, arpinfo->outiface_mask);

	if (NF_INVF(arpinfo, ARPT_INV_VIA_OUT, ret != 0))
		return 0;

	return 1;
}
