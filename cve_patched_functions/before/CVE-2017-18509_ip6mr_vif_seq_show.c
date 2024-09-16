static int ip6mr_vif_seq_show(struct seq_file *seq, void *v)
{
	struct ipmr_vif_iter *iter = seq->private;
	struct mr6_table *mrt = iter->mrt;

	if (v == SEQ_START_TOKEN) {
		seq_puts(seq,
			 "Interface      BytesIn  PktsIn  BytesOut PktsOut Flags\n");
	} else {
		const struct mif_device *vif = v;
		const char *name = vif->dev ? vif->dev->name : "none";

		seq_printf(seq,
			   "%2td %-10s %8ld %7ld  %8ld %7ld %05X\n",
			   vif - mrt->vif6_table,
			   name, vif->bytes_in, vif->pkt_in,
			   vif->bytes_out, vif->pkt_out,
			   vif->flags);
	}
	return 0;
}
