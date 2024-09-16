static inline int arp_checkentry(const struct arpt_arp *arp)
{
	if (arp->flags & ~ARPT_F_MASK) {
		duprintf("Unknown flag bits set: %08X\n",
			 arp->flags & ~ARPT_F_MASK);
		return 0;
	}
	if (arp->invflags & ~ARPT_INV_MASK) {
		duprintf("Unknown invflag bits set: %08X\n",
			 arp->invflags & ~ARPT_INV_MASK);
		return 0;
	}

	return 1;
}
