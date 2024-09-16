static void do_pcd_read(void)
{
	pcd_busy = 1;
	pcd_retries = 0;
	pcd_transfer();
	if (!pcd_count) {
		next_request(0);
		return;
	}

	pi_do_claimed(pcd_current->pi, pcd_start);
}
