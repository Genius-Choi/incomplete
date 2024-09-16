void reset_revision_walk(void)
{
	clear_object_flags(SEEN | ADDED | SHOWN);
}
