uucp_unlock(void)
{
	if ( lockname[0] ) unlink(lockname);
	return 0;
}
