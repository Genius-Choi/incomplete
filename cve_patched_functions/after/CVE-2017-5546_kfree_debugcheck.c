static void kfree_debugcheck(const void *objp)
{
	if (!virt_addr_valid(objp)) {
		pr_err("kfree_debugcheck: out of range ptr %lxh\n",
		       (unsigned long)objp);
		BUG();
	}
}
