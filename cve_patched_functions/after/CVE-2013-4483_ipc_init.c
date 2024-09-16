static int __init ipc_init(void)
{
	sem_init();
	msg_init();
	shm_init();
	register_hotmemory_notifier(&ipc_memory_nb);
	register_ipcns_notifier(&init_ipc_ns);
	return 0;
}
