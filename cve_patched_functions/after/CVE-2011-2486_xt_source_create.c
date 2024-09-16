static int xt_source_create(void)
{
  if (++xt_source_count > 1 && xt_source != NULL)
	return 0;

  if ((xt_source = g_source_new(&xt_event_funcs, sizeof(GSource))) == NULL) {
	npw_printf("ERROR: failed to initialize Xt events listener\n");
	return -1;
  }
  g_source_set_priority(xt_source, GDK_PRIORITY_EVENTS);
  g_source_set_can_recurse(xt_source, TRUE);
  g_source_attach(xt_source, NULL);
  xt_event_poll_fd.fd = ConnectionNumber(x_display);
  xt_event_poll_fd.events = G_IO_IN;
  xt_event_poll_fd.revents = 0;
  g_source_add_poll(xt_source, &xt_event_poll_fd);
  return 0;
}
