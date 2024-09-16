signal_init(void)
{
#ifndef _DEBUG_
	signal_set(SIGHUP, propagate_signal, NULL);
	signal_set(SIGUSR1, propagate_signal, NULL);
	signal_set(SIGUSR2, propagate_signal, NULL);
#ifdef _WITH_JSON_
	signal_set(SIGJSON, propagate_signal, NULL);
#endif
	signal_set(SIGINT, sigend, NULL);
	signal_set(SIGTERM, sigend, NULL);
#endif
	signal_ignore(SIGPIPE);
}
