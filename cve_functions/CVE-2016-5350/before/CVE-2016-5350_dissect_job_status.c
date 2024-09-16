dissect_job_status(tvbuff_t *tvb, int offset, packet_info *pinfo,
		   proto_tree *tree, dcerpc_info *di, guint8 *drep)
{
	guint32 status;
	static const int * hf_status[] = {
		&hf_job_status_user_intervention,
		&hf_job_status_blocked,
		&hf_job_status_deleted,
		&hf_job_status_printed,
		&hf_job_status_paperout,
		&hf_job_status_offline,
		&hf_job_status_printing,
		&hf_job_status_spooling,
		&hf_job_status_deleting,
		&hf_job_status_error,
		&hf_job_status_paused,
		NULL
	};

	offset = dissect_ndr_uint32(tvb, offset, pinfo, NULL, di, drep, -1, &status);

	proto_tree_add_bitmask_value_with_flags(tree, tvb, offset - 4, hf_job_status,
					ett_job_status, hf_status, status, BMT_NO_APPEND);

	return offset;
}
