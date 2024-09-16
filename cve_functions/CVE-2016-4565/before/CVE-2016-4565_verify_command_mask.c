static int verify_command_mask(struct ib_device *ib_dev, __u32 command)
{
	u64 mask;

	if (command <= IB_USER_VERBS_CMD_OPEN_QP)
		mask = ib_dev->uverbs_cmd_mask;
	else
		mask = ib_dev->uverbs_ex_cmd_mask;

	if (mask & ((u64)1 << command))
		return 0;

	return -1;
}
