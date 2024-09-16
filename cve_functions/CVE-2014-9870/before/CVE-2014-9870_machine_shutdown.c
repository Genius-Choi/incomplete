void machine_shutdown(void)
{
#ifdef CONFIG_SMP
	smp_send_stop();
#endif
}
