dissect_spoolss_JOB_INFO_1(tvbuff_t *tvb, int offset, packet_info *pinfo,
			   proto_tree *tree, dcerpc_info *di, guint8 *drep)
{
	proto_item *item;
	proto_tree *subtree;
	int struct_start = offset;
	char *document_name;

	subtree = proto_tree_add_subtree(tree, tvb, offset, 0, ett_JOB_INFO_1, &item, "Job info level 1");

	offset = dissect_ndr_uint32(tvb, offset, pinfo, subtree, di, drep,
				    hf_job_id, NULL);

	offset = dissect_spoolss_relstr(
		tvb, offset, pinfo, subtree, di, drep, hf_printername,
		struct_start, NULL);

	offset = dissect_spoolss_relstr(
		tvb, offset, pinfo, subtree, di, drep, hf_servername,
		struct_start, NULL);

	offset = dissect_spoolss_relstr(
		tvb, offset, pinfo, subtree, di, drep, hf_username,
		struct_start, NULL);

	offset = dissect_spoolss_relstr(
		tvb, offset, pinfo, subtree, di, drep, hf_documentname,
		struct_start, &document_name);

	proto_item_append_text(item, ": %s", document_name);
	g_free(document_name);

	offset = dissect_spoolss_relstr(
		tvb, offset, pinfo, subtree, di, drep, hf_datatype,
		struct_start, NULL);

	offset = dissect_spoolss_relstr(
		tvb, offset, pinfo, subtree, di, drep, hf_textstatus,
		struct_start, NULL);

	offset = dissect_job_status(tvb, offset, pinfo, subtree, di, drep);

	offset = dissect_ndr_uint32(tvb, offset, pinfo, subtree, di, drep,
				    hf_job_priority, NULL);

	offset = dissect_ndr_uint32(tvb, offset, pinfo, subtree, di, drep,
				    hf_job_position, NULL);

	offset = dissect_ndr_uint32(tvb, offset, pinfo, subtree, di, drep,
				    hf_job_totalpages, NULL);

	offset = dissect_ndr_uint32(tvb, offset, pinfo, subtree, di, drep,
				    hf_job_pagesprinted, NULL);

	offset = dissect_SYSTEM_TIME(
		tvb, offset, pinfo, subtree, di, drep, "Job Submission Time",
		TRUE, NULL);

	proto_item_set_len(item, offset - struct_start);

	return offset;
}
