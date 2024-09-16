static void pcd_transfer(void)
{

	while (pcd_count && (pcd_sector / 4 == pcd_bufblk)) {
		int o = (pcd_sector % 4) * 512;
		memcpy(pcd_buf, pcd_buffer + o, 512);
		pcd_count--;
		pcd_buf += 512;
		pcd_sector++;
	}
}
