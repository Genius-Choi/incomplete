static int __init ulri_disable(char *s)
{
	pr_info("Disabling ulri\n");
	noulri = 1;

	return 1;
}
