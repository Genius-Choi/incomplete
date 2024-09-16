version(void)
{
	fprintf(stdout,"bsdcpio %s -- %s\n",
	    BSDCPIO_VERSION_STRING,
	    archive_version_details());
	exit(0);
}
