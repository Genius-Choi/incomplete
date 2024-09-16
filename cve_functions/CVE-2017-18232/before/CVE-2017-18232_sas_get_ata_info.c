int sas_get_ata_info(struct domain_device *dev, struct ex_phy *phy)
{
	if (phy->attached_tproto & SAS_PROTOCOL_STP)
		dev->tproto = phy->attached_tproto;
	if (phy->attached_sata_dev)
		dev->tproto |= SAS_SATA_DEV;

	if (phy->attached_dev_type == SAS_SATA_PENDING)
		dev->dev_type = SAS_SATA_PENDING;
	else {
		int res;

		dev->dev_type = SAS_SATA_DEV;
		res = sas_get_report_phy_sata(dev->parent, phy->phy_id,
					      &dev->sata_dev.rps_resp);
		if (res) {
			SAS_DPRINTK("report phy sata to %016llx:0x%x returned "
				    "0x%x\n", SAS_ADDR(dev->parent->sas_addr),
				    phy->phy_id, res);
			return res;
		}
		memcpy(dev->frame_rcvd, &dev->sata_dev.rps_resp.rps.fis,
		       sizeof(struct dev_to_host_fis));
		dev->sata_dev.class = sas_get_ata_command_set(dev);
	}
	return 0;
}
