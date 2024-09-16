static void __exit snd_hrtimer_exit(void)
{
	if (mytimer) {
		snd_timer_global_free(mytimer);
		mytimer = NULL;
	}
}
