static inline void print_ucode(struct ucode_cpu_info *uci)
{
	struct microcode_intel *mc_intel;

	mc_intel = uci->mc;
	if (mc_intel == NULL)
		return;

	print_ucode_info(uci, mc_intel->hdr.date);
}
