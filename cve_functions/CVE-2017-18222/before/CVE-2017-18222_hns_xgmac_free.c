static void hns_xgmac_free(void *mac_drv)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;
	struct dsaf_device *dsaf_dev
		= (struct dsaf_device *)dev_get_drvdata(drv->dev);

	u32 mac_id = drv->mac_id;

	dsaf_dev->misc_op->xge_srst(dsaf_dev, mac_id, 0);
}
