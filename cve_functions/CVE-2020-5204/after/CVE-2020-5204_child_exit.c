static void child_exit(uev_t *w, void *arg, int events)
{
	DBG("Child exiting ...");
	uev_exit(w->ctx);
}
