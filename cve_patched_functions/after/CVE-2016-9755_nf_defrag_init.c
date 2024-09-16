static int __init nf_defrag_init(void)
{
	int ret = 0;

	ret = nf_ct_frag6_init();
	if (ret < 0) {
		pr_err("nf_defrag_ipv6: can't initialize frag6.\n");
		return ret;
	}
	ret = nf_register_hooks(ipv6_defrag_ops, ARRAY_SIZE(ipv6_defrag_ops));
	if (ret < 0) {
		pr_err("nf_defrag_ipv6: can't register hooks\n");
		goto cleanup_frag6;
	}
	return ret;

cleanup_frag6:
	nf_ct_frag6_cleanup();
	return ret;

}
