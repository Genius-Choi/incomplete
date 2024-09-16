static int __init early_coherent_pool(char *p)
{
	atomic_pool.size = memparse(p, &p);
	return 0;
}
