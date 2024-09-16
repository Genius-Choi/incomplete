static int __init hostap_init(void)
{
	if (init_net.proc_net != NULL) {
		hostap_proc = proc_mkdir("hostap", init_net.proc_net);
		if (!hostap_proc)
			printk(KERN_WARNING "Failed to mkdir "
			       "/proc/net/hostap\n");
	} else
		hostap_proc = NULL;

	return 0;
}
