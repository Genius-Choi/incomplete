void sequencer_init(void)
{
	if (sequencer_ok)
		return;
	queue = vmalloc(SEQ_MAX_QUEUE * EV_SZ);
	if (queue == NULL)
	{
		printk(KERN_ERR "sequencer: Can't allocate memory for sequencer output queue\n");
		return;
	}
	iqueue = vmalloc(SEQ_MAX_QUEUE * IEV_SZ);
	if (iqueue == NULL)
	{
		printk(KERN_ERR "sequencer: Can't allocate memory for sequencer input queue\n");
		vfree(queue);
		return;
	}
	sequencer_ok = 1;
}
