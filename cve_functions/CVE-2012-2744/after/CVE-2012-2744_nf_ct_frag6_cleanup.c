void nf_ct_frag6_cleanup(void)
{
	inet_frags_fini(&nf_frags);

	nf_init_frags.low_thresh = 0;
	nf_ct_frag6_evictor();
}
