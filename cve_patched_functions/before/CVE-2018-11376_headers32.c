static void headers32(RBinFile *bf) {
#define p bf->rbin->cb_printf
	const ut8 *buf = r_buf_get_at (bf->buf, 0, NULL);
	p ("0x00000000  ELF MAGIC   0x%08x\n", r_read_le32 (buf));
	p ("0x00000004  Type        0x%04x\n", r_read_le16 (buf + 4));
	p ("0x00000006  Machine     0x%04x\n", r_read_le16 (buf + 6));
	p ("0x00000008  Version     0x%08x\n", r_read_le32 (buf + 8));
	p ("0x0000000c  Entrypoint  0x%08x\n", r_read_le32 (buf + 12));
	p ("0x00000010  PhOff       0x%08x\n", r_read_le32 (buf + 16));
	p ("0x00000014  ShOff       0x%08x\n", r_read_le32 (buf + 20));
}
