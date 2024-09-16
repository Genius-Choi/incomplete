megasas_mgmt_fw_ioctl(struct megasas_instance *instance,
		      struct megasas_iocpacket __user * user_ioc,
		      struct megasas_iocpacket *ioc)
{
	struct megasas_sge64 *kern_sge64 = NULL;
	struct megasas_sge32 *kern_sge32 = NULL;
	struct megasas_cmd *cmd;
	void *kbuff_arr[MAX_IOCTL_SGE];
	dma_addr_t buf_handle = 0;
	int error = 0, i;
	void *sense = NULL;
	dma_addr_t sense_handle;
	unsigned long *sense_ptr;
	u32 opcode = 0;

	memset(kbuff_arr, 0, sizeof(kbuff_arr));

	if (ioc->sge_count > MAX_IOCTL_SGE) {
		dev_printk(KERN_DEBUG, &instance->pdev->dev, "SGE count [%d] >  max limit [%d]\n",
		       ioc->sge_count, MAX_IOCTL_SGE);
		return -EINVAL;
	}

	if ((ioc->frame.hdr.cmd >= MFI_CMD_OP_COUNT) ||
	    ((ioc->frame.hdr.cmd == MFI_CMD_NVME) &&
	    !instance->support_nvme_passthru)) {
		dev_err(&instance->pdev->dev,
			"Received invalid ioctl command 0x%x\n",
			ioc->frame.hdr.cmd);
		return -ENOTSUPP;
	}

	cmd = megasas_get_cmd(instance);
	if (!cmd) {
		dev_printk(KERN_DEBUG, &instance->pdev->dev, "Failed to get a cmd packet\n");
		return -ENOMEM;
	}

	/*
	 * User's IOCTL packet has 2 frames (maximum). Copy those two
	 * frames into our cmd's frames. cmd->frame's context will get
	 * overwritten when we copy from user's frames. So set that value
	 * alone separately
	 */
	memcpy(cmd->frame, ioc->frame.raw, 2 * MEGAMFI_FRAME_SIZE);
	cmd->frame->hdr.context = cpu_to_le32(cmd->index);
	cmd->frame->hdr.pad_0 = 0;

	cmd->frame->hdr.flags &= (~MFI_FRAME_IEEE);

	if (instance->consistent_mask_64bit)
		cmd->frame->hdr.flags |= cpu_to_le16((MFI_FRAME_SGL64 |
				       MFI_FRAME_SENSE64));
	else
		cmd->frame->hdr.flags &= cpu_to_le16(~(MFI_FRAME_SGL64 |
					       MFI_FRAME_SENSE64));

	if (cmd->frame->hdr.cmd == MFI_CMD_DCMD)
		opcode = le32_to_cpu(cmd->frame->dcmd.opcode);

	if (opcode == MR_DCMD_CTRL_SHUTDOWN) {
		if (megasas_get_ctrl_info(instance) != DCMD_SUCCESS) {
			megasas_return_cmd(instance, cmd);
			return -1;
		}
	}

	if (opcode == MR_DRIVER_SET_APP_CRASHDUMP_MODE) {
		error = megasas_set_crash_dump_params_ioctl(cmd);
		megasas_return_cmd(instance, cmd);
		return error;
	}

	/*
	 * The management interface between applications and the fw uses
	 * MFI frames. E.g, RAID configuration changes, LD property changes
	 * etc are accomplishes through different kinds of MFI frames. The
	 * driver needs to care only about substituting user buffers with
	 * kernel buffers in SGLs. The location of SGL is embedded in the
	 * struct iocpacket itself.
	 */
	if (instance->consistent_mask_64bit)
		kern_sge64 = (struct megasas_sge64 *)
			((unsigned long)cmd->frame + ioc->sgl_off);
	else
		kern_sge32 = (struct megasas_sge32 *)
			((unsigned long)cmd->frame + ioc->sgl_off);

	/*
	 * For each user buffer, create a mirror buffer and copy in
	 */
	for (i = 0; i < ioc->sge_count; i++) {
		if (!ioc->sgl[i].iov_len)
			continue;

		kbuff_arr[i] = dma_alloc_coherent(&instance->pdev->dev,
						    ioc->sgl[i].iov_len,
						    &buf_handle, GFP_KERNEL);
		if (!kbuff_arr[i]) {
			dev_printk(KERN_DEBUG, &instance->pdev->dev, "Failed to alloc "
			       "kernel SGL buffer for IOCTL\n");
			error = -ENOMEM;
			goto out;
		}

		/*
		 * We don't change the dma_coherent_mask, so
		 * dma_alloc_coherent only returns 32bit addresses
		 */
		if (instance->consistent_mask_64bit) {
			kern_sge64[i].phys_addr = cpu_to_le64(buf_handle);
			kern_sge64[i].length = cpu_to_le32(ioc->sgl[i].iov_len);
		} else {
			kern_sge32[i].phys_addr = cpu_to_le32(buf_handle);
			kern_sge32[i].length = cpu_to_le32(ioc->sgl[i].iov_len);
		}

		/*
		 * We created a kernel buffer corresponding to the
		 * user buffer. Now copy in from the user buffer
		 */
		if (copy_from_user(kbuff_arr[i], ioc->sgl[i].iov_base,
				   (u32) (ioc->sgl[i].iov_len))) {
			error = -EFAULT;
			goto out;
		}
	}

	if (ioc->sense_len) {
		sense = dma_alloc_coherent(&instance->pdev->dev, ioc->sense_len,
					     &sense_handle, GFP_KERNEL);
		if (!sense) {
			error = -ENOMEM;
			goto out;
		}

		sense_ptr =
		(unsigned long *) ((unsigned long)cmd->frame + ioc->sense_off);
		if (instance->consistent_mask_64bit)
			*sense_ptr = cpu_to_le64(sense_handle);
		else
			*sense_ptr = cpu_to_le32(sense_handle);
	}

	/*
	 * Set the sync_cmd flag so that the ISR knows not to complete this
	 * cmd to the SCSI mid-layer
	 */
	cmd->sync_cmd = 1;
	if (megasas_issue_blocked_cmd(instance, cmd, 0) == DCMD_NOT_FIRED) {
		cmd->sync_cmd = 0;
		dev_err(&instance->pdev->dev,
			"return -EBUSY from %s %d cmd 0x%x opcode 0x%x cmd->cmd_status_drv 0x%x\n",
			__func__, __LINE__, cmd->frame->hdr.cmd, opcode,
			cmd->cmd_status_drv);
		return -EBUSY;
	}

	cmd->sync_cmd = 0;

	if (instance->unload == 1) {
		dev_info(&instance->pdev->dev, "Driver unload is in progress "
			"don't submit data to application\n");
		goto out;
	}
	/*
	 * copy out the kernel buffers to user buffers
	 */
	for (i = 0; i < ioc->sge_count; i++) {
		if (copy_to_user(ioc->sgl[i].iov_base, kbuff_arr[i],
				 ioc->sgl[i].iov_len)) {
			error = -EFAULT;
			goto out;
		}
	}

	/*
	 * copy out the sense
	 */
	if (ioc->sense_len) {
		/*
		 * sense_ptr points to the location that has the user
		 * sense buffer address
		 */
		sense_ptr = (unsigned long *) ((unsigned long)ioc->frame.raw +
				ioc->sense_off);

		if (copy_to_user((void __user *)((unsigned long)
				 get_unaligned((unsigned long *)sense_ptr)),
				 sense, ioc->sense_len)) {
			dev_err(&instance->pdev->dev, "Failed to copy out to user "
					"sense data\n");
			error = -EFAULT;
			goto out;
		}
	}

	/*
	 * copy the status codes returned by the fw
	 */
	if (copy_to_user(&user_ioc->frame.hdr.cmd_status,
			 &cmd->frame->hdr.cmd_status, sizeof(u8))) {
		dev_printk(KERN_DEBUG, &instance->pdev->dev, "Error copying out cmd_status\n");
		error = -EFAULT;
	}

out:
	if (sense) {
		dma_free_coherent(&instance->pdev->dev, ioc->sense_len,
				    sense, sense_handle);
	}

	for (i = 0; i < ioc->sge_count; i++) {
		if (kbuff_arr[i]) {
			if (instance->consistent_mask_64bit)
				dma_free_coherent(&instance->pdev->dev,
					le32_to_cpu(kern_sge64[i].length),
					kbuff_arr[i],
					le64_to_cpu(kern_sge64[i].phys_addr));
			else
				dma_free_coherent(&instance->pdev->dev,
					le32_to_cpu(kern_sge32[i].length),
					kbuff_arr[i],
					le32_to_cpu(kern_sge32[i].phys_addr));
			kbuff_arr[i] = NULL;
		}
	}

	megasas_return_cmd(instance, cmd);
	return error;
}
