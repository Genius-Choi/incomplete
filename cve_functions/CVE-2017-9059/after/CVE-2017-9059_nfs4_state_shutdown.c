nfs4_state_shutdown(void)
{
	destroy_workqueue(laundry_wq);
	nfsd4_destroy_callback_queue();
	cleanup_callback_cred();
}
