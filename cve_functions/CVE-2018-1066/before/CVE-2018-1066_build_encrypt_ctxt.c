build_encrypt_ctxt(struct smb2_encryption_neg_context *pneg_ctxt)
{
	pneg_ctxt->ContextType = SMB2_ENCRYPTION_CAPABILITIES;
	pneg_ctxt->DataLength = cpu_to_le16(6);
	pneg_ctxt->CipherCount = cpu_to_le16(2);
	pneg_ctxt->Ciphers[0] = SMB2_ENCRYPTION_AES128_GCM;
	pneg_ctxt->Ciphers[1] = SMB2_ENCRYPTION_AES128_CCM;
}
