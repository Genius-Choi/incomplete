static int pcd_ready(void)
{
	return (((status_reg(pcd_current) & (IDE_BUSY | IDE_DRQ)) == IDE_DRQ));
}
