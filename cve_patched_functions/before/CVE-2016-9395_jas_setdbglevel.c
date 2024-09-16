int jas_setdbglevel(int dbglevel)
{
	int olddbglevel;

	/* Save the old debug level. */
	olddbglevel = jas_dbglevel;

	/* Change the debug level. */
	jas_dbglevel = dbglevel;

	/* Return the old debug level. */
	return olddbglevel;
}
