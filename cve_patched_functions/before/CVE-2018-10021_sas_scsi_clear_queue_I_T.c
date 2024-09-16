static void sas_scsi_clear_queue_I_T(struct list_head *error_q,
				     struct domain_device *dev)
{
	struct scsi_cmnd *cmd, *n;

	list_for_each_entry_safe(cmd, n, error_q, eh_entry) {
		struct domain_device *x = cmd_to_domain_dev(cmd);

		if (x == dev)
			sas_eh_finish_cmd(cmd);
	}
}
