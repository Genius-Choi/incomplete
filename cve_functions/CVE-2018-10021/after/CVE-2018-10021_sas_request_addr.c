int sas_request_addr(struct Scsi_Host *shost, u8 *addr)
{
	int res;
	const struct firmware *fw;

	res = request_firmware(&fw, "sas_addr", &shost->shost_gendev);
	if (res)
		return res;

	if (fw->size < SAS_STRING_ADDR_SIZE) {
		res = -ENODEV;
		goto out;
	}

	res = hex2bin(addr, fw->data, strnlen(fw->data, SAS_ADDR_SIZE * 2) / 2);
	if (res)
		goto out;

out:
	release_firmware(fw);
	return res;
}
