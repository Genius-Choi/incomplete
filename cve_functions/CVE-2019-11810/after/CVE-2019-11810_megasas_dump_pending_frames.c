megasas_dump_pending_frames(struct megasas_instance *instance)
{
	struct megasas_cmd *cmd;
	int i,n;
	union megasas_sgl *mfi_sgl;
	struct megasas_io_frame *ldio;
	struct megasas_pthru_frame *pthru;
	u32 sgcount;
	u16 max_cmd = instance->max_fw_cmds;

	dev_err(&instance->pdev->dev, "[%d]: Dumping Frame Phys Address of all pending cmds in FW\n",instance->host->host_no);
	dev_err(&instance->pdev->dev, "[%d]: Total OS Pending cmds : %d\n",instance->host->host_no,atomic_read(&instance->fw_outstanding));
	if (IS_DMA64)
		dev_err(&instance->pdev->dev, "[%d]: 64 bit SGLs were sent to FW\n",instance->host->host_no);
	else
		dev_err(&instance->pdev->dev, "[%d]: 32 bit SGLs were sent to FW\n",instance->host->host_no);

	dev_err(&instance->pdev->dev, "[%d]: Pending OS cmds in FW : \n",instance->host->host_no);
	for (i = 0; i < max_cmd; i++) {
		cmd = instance->cmd_list[i];
		if (!cmd->scmd)
			continue;
		dev_err(&instance->pdev->dev, "[%d]: Frame addr :0x%08lx : ",instance->host->host_no,(unsigned long)cmd->frame_phys_addr);
		if (megasas_cmd_type(cmd->scmd) == READ_WRITE_LDIO) {
			ldio = (struct megasas_io_frame *)cmd->frame;
			mfi_sgl = &ldio->sgl;
			sgcount = ldio->sge_count;
			dev_err(&instance->pdev->dev, "[%d]: frame count : 0x%x, Cmd : 0x%x, Tgt id : 0x%x,"
			" lba lo : 0x%x, lba_hi : 0x%x, sense_buf addr : 0x%x,sge count : 0x%x\n",
			instance->host->host_no, cmd->frame_count, ldio->cmd, ldio->target_id,
			le32_to_cpu(ldio->start_lba_lo), le32_to_cpu(ldio->start_lba_hi),
			le32_to_cpu(ldio->sense_buf_phys_addr_lo), sgcount);
		} else {
			pthru = (struct megasas_pthru_frame *) cmd->frame;
			mfi_sgl = &pthru->sgl;
			sgcount = pthru->sge_count;
			dev_err(&instance->pdev->dev, "[%d]: frame count : 0x%x, Cmd : 0x%x, Tgt id : 0x%x, "
			"lun : 0x%x, cdb_len : 0x%x, data xfer len : 0x%x, sense_buf addr : 0x%x,sge count : 0x%x\n",
			instance->host->host_no, cmd->frame_count, pthru->cmd, pthru->target_id,
			pthru->lun, pthru->cdb_len, le32_to_cpu(pthru->data_xfer_len),
			le32_to_cpu(pthru->sense_buf_phys_addr_lo), sgcount);
		}
		if (megasas_dbg_lvl & MEGASAS_DBG_LVL) {
			for (n = 0; n < sgcount; n++) {
				if (IS_DMA64)
					dev_err(&instance->pdev->dev, "sgl len : 0x%x, sgl addr : 0x%llx\n",
						le32_to_cpu(mfi_sgl->sge64[n].length),
						le64_to_cpu(mfi_sgl->sge64[n].phys_addr));
				else
					dev_err(&instance->pdev->dev, "sgl len : 0x%x, sgl addr : 0x%x\n",
						le32_to_cpu(mfi_sgl->sge32[n].length),
						le32_to_cpu(mfi_sgl->sge32[n].phys_addr));
			}
		}
	} /*for max_cmd*/
	dev_err(&instance->pdev->dev, "[%d]: Pending Internal cmds in FW : \n",instance->host->host_no);
	for (i = 0; i < max_cmd; i++) {

		cmd = instance->cmd_list[i];

		if (cmd->sync_cmd == 1)
			dev_err(&instance->pdev->dev, "0x%08lx : ", (unsigned long)cmd->frame_phys_addr);
	}
	dev_err(&instance->pdev->dev, "[%d]: Dumping Done\n\n",instance->host->host_no);
}
