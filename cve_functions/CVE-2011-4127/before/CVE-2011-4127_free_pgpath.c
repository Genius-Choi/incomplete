static void free_pgpath(struct pgpath *pgpath)
{
	kfree(pgpath);
}
