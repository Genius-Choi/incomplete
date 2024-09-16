dissect_PRINTER_INFO_0(tvbuff_t *tvb, int offset,
				  packet_info *pinfo, proto_tree *tree,
				  dcerpc_info *di, guint8 *drep)
{
	offset = dissect_spoolss_relstr(
		tvb, offset, pinfo, tree, di, drep, hf_printername,
		0, NULL);

	offset = dissect_spoolss_relstr(
		tvb, offset, pinfo, tree, di, drep, hf_servername,
		0, NULL);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep, hf_printer_cjobs, NULL);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep, hf_printer_total_jobs,
		NULL);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep, hf_printer_total_bytes,
		NULL);

	offset = dissect_SYSTEM_TIME(
		tvb, offset, pinfo, tree, di, drep, "Unknown time", TRUE, NULL);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep, hf_printer_global_counter,
		NULL);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep, hf_printer_total_pages,
		NULL);

	offset = dissect_ndr_uint16(
		tvb, offset, pinfo, tree, di, drep, hf_printer_major_version,
		NULL);

	offset = dissect_ndr_uint16(
		tvb, offset, pinfo, tree, di, drep, hf_printer_build_version,
		NULL);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep, hf_printer_unk7, NULL);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep, hf_printer_unk8, NULL);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep, hf_printer_unk9, NULL);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep, hf_printer_session_ctr,
		NULL);

	offset = dissect_ndr_uint32( tvb, offset, pinfo, tree, di, drep,
		hf_printer_unk11, NULL);

	offset = dissect_ndr_uint32( tvb, offset, pinfo, tree, di, drep,
		hf_printer_printer_errors, NULL);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep, hf_printer_unk13, NULL);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep, hf_printer_unk14, NULL);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep, hf_printer_unk15, NULL);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep, hf_printer_unk16, NULL);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep, hf_printer_changeid, NULL);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep, hf_printer_unk18, NULL);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep, hf_printer_status, NULL);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep, hf_printer_unk20, NULL);

	offset = dissect_ndr_uint32(
		tvb, offset, pinfo, tree, di, drep, hf_printer_c_setprinter,
		NULL);

	offset = dissect_ndr_uint16(
		tvb, offset, pinfo, tree, di, drep, hf_printer_unk22, NULL);

	offset = dissect_ndr_uint16(
		tvb, offset, pinfo, tree, di, drep, hf_printer_unk23, NULL);

	offset = dissect_ndr_uint16(
		tvb, offset, pinfo, tree, di, drep, hf_printer_unk24, NULL);

	offset = dissect_ndr_uint16(
		tvb, offset, pinfo, tree, di, drep, hf_printer_unk25, NULL);

	offset = dissect_ndr_uint16(
		tvb, offset, pinfo, tree, di, drep, hf_printer_unk26, NULL);

	offset = dissect_ndr_uint16(
		tvb, offset, pinfo, tree, di, drep, hf_printer_unk27, NULL);

	offset = dissect_ndr_uint16(
		tvb, offset, pinfo, tree, di, drep, hf_printer_unk28, NULL);

	offset = dissect_ndr_uint16(
		tvb, offset, pinfo, tree, di, drep, hf_printer_unk29, NULL);

	return offset;
}
