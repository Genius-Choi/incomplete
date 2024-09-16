static int dell_poweredge_bt_xaction_handler(struct notifier_block *self,
					     unsigned long unused,
					     void *in)
{
	struct smi_info *smi_info = in;
	unsigned char *data = smi_info->curr_msg->data;
	unsigned int size   = smi_info->curr_msg->data_size;
	if (size >= 8 &&
	    (data[0]>>2) == STORAGE_NETFN &&
	    data[1] == STORAGE_CMD_GET_SDR &&
	    data[7] == 0x3A) {
		return_hosed_msg_badsize(smi_info);
		return NOTIFY_STOP;
	}
	return NOTIFY_DONE;
}
