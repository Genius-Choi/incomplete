void sequencer_unload(void)
{
	vfree(queue);
	vfree(iqueue);
	queue = iqueue = NULL;
}
