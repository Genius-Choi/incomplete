static void flush_multipath_work(struct multipath *m)
{
	flush_workqueue(kmpath_handlerd);
	multipath_wait_for_pg_init_completion(m);
	flush_workqueue(kmultipathd);
	flush_work_sync(&m->trigger_event);
}
