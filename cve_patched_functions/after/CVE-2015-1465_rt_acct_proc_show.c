static int rt_acct_proc_show(struct seq_file *m, void *v)
{
	struct ip_rt_acct *dst, *src;
	unsigned int i, j;

	dst = kcalloc(256, sizeof(struct ip_rt_acct), GFP_KERNEL);
	if (!dst)
		return -ENOMEM;

	for_each_possible_cpu(i) {
		src = (struct ip_rt_acct *)per_cpu_ptr(ip_rt_acct, i);
		for (j = 0; j < 256; j++) {
			dst[j].o_bytes   += src[j].o_bytes;
			dst[j].o_packets += src[j].o_packets;
			dst[j].i_bytes   += src[j].i_bytes;
			dst[j].i_packets += src[j].i_packets;
		}
	}

	seq_write(m, dst, 256 * sizeof(struct ip_rt_acct));
	kfree(dst);
	return 0;
}
