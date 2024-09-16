static int __init serpent_sse2_init(void)
{
	if (!cpu_has_xmm2) {
		printk(KERN_INFO "SSE2 instructions are not detected.\n");
		return -ENODEV;
	}

	return crypto_register_algs(serpent_algs, ARRAY_SIZE(serpent_algs));
}
