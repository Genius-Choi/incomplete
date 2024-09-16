static ssize_t lbs_threshold_read(uint16_t tlv_type, uint16_t event_mask,
				  struct file *file, char __user *userbuf,
				  size_t count, loff_t *ppos)
{
	struct cmd_ds_802_11_subscribe_event *subscribed;
	struct mrvl_ie_thresholds *got;
	struct lbs_private *priv = file->private_data;
	ssize_t ret = 0;
	size_t pos = 0;
	char *buf;
	u8 value;
	u8 freq;
	int events = 0;

	buf = (char *)get_zeroed_page(GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	subscribed = kzalloc(sizeof(*subscribed), GFP_KERNEL);
	if (!subscribed) {
		ret = -ENOMEM;
		goto out_page;
	}

	subscribed->hdr.size = cpu_to_le16(sizeof(*subscribed));
	subscribed->action = cpu_to_le16(CMD_ACT_GET);

	ret = lbs_cmd_with_response(priv, CMD_802_11_SUBSCRIBE_EVENT, subscribed);
	if (ret)
		goto out_cmd;

	got = lbs_tlv_find(tlv_type, subscribed->tlv, sizeof(subscribed->tlv));
	if (got) {
		value = got->value;
		freq  = got->freq;
		events = le16_to_cpu(subscribed->events);

		pos += snprintf(buf, len, "%d %d %d\n", value, freq,
				!!(events & event_mask));
	}

	ret = simple_read_from_buffer(userbuf, count, ppos, buf, pos);

 out_cmd:
	kfree(subscribed);

 out_page:
	free_page((unsigned long)buf);
	return ret;
}
