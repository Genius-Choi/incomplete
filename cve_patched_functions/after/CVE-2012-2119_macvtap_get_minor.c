static int macvtap_get_minor(struct macvlan_dev *vlan)
{
	int retval = -ENOMEM;
	int id;

	mutex_lock(&minor_lock);
	if (idr_pre_get(&minor_idr, GFP_KERNEL) == 0)
		goto exit;

	retval = idr_get_new_above(&minor_idr, vlan, 1, &id);
	if (retval < 0) {
		if (retval == -EAGAIN)
			retval = -ENOMEM;
		goto exit;
	}
	if (id < MACVTAP_NUM_DEVS) {
		vlan->minor = id;
	} else {
		printk(KERN_ERR "too many macvtap devices\n");
		retval = -EINVAL;
		idr_remove(&minor_idr, id);
	}
exit:
	mutex_unlock(&minor_lock);
	return retval;
}
