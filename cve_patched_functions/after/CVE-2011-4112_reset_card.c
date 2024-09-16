static int reset_card( struct net_device *dev , int lock) {
	struct airo_info *ai = dev->ml_priv;

	if (lock && down_interruptible(&ai->sem))
		return -1;
	waitbusy (ai);
	OUT4500(ai,COMMAND,CMD_SOFTRESET);
	msleep(200);
	waitbusy (ai);
	msleep(200);
	if (lock)
		up(&ai->sem);
	return 0;
}
