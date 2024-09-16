static ssize_t lbs_threshold_write(uint16_t tlv_type, uint16_t event_mask,
				   struct file *file,
				   const char __user *userbuf, size_t count,
				   loff_t *ppos)
{
	struct cmd_ds_802_11_subscribe_event *events;
	struct mrvl_ie_thresholds *tlv;
	struct lbs_private *priv = file->private_data;
	ssize_t buf_size;
	int value, freq, new_mask;
	uint16_t curr_mask;
	char *buf;
	int ret;

	buf = (char *)get_zeroed_page(GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	buf_size = min(count, len - 1);
	if (copy_from_user(buf, userbuf, buf_size)) {
		ret = -EFAULT;
		goto out_page;
	}
	ret = sscanf(buf, "%d %d %d", &value, &freq, &new_mask);
	if (ret != 3) {
		ret = -EINVAL;
		goto out_page;
	}
	events = kzalloc(sizeof(*events), GFP_KERNEL);
	if (!events) {
		ret = -ENOMEM;
		goto out_page;
	}

	events->hdr.size = cpu_to_le16(sizeof(*events));
	events->action = cpu_to_le16(CMD_ACT_GET);

	ret = lbs_cmd_with_response(priv, CMD_802_11_SUBSCRIBE_EVENT, events);
	if (ret)
		goto out_events;

	curr_mask = le16_to_cpu(events->events);

	if (new_mask)
		new_mask = curr_mask | event_mask;
	else
		new_mask = curr_mask & ~event_mask;

	/* Now everything is set and we can send stuff down to the firmware */

	tlv = (void *)events->tlv;

	events->action = cpu_to_le16(CMD_ACT_SET);
	events->events = cpu_to_le16(new_mask);
	tlv->header.type = cpu_to_le16(tlv_type);
	tlv->header.len = cpu_to_le16(sizeof(*tlv) - sizeof(tlv->header));
	tlv->value = value;
	if (tlv_type != TLV_TYPE_BCNMISS)
		tlv->freq = freq;

	/* The command header, the action, the event mask, and one TLV */
	events->hdr.size = cpu_to_le16(sizeof(events->hdr) + 4 + sizeof(*tlv));

	ret = lbs_cmd_with_response(priv, CMD_802_11_SUBSCRIBE_EVENT, events);

	if (!ret)
		ret = count;
 out_events:
	kfree(events);
 out_page:
	free_page((unsigned long)buf);
	return ret;
}
