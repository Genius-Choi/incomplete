int inode_wait(void *word)
{
	schedule();
	return 0;
}
