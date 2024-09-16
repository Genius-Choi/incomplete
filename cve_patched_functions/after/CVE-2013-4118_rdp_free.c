void rdp_free(rdpRdp* rdp)
{
	if (rdp != NULL)
	{
		crypto_rc4_free(rdp->rc4_decrypt_key);
		crypto_rc4_free(rdp->rc4_encrypt_key);
		crypto_des3_free(rdp->fips_encrypt);
		crypto_des3_free(rdp->fips_decrypt);
		crypto_hmac_free(rdp->fips_hmac);
		freerdp_settings_free(rdp->settings);
		extension_free(rdp->extension);
		transport_free(rdp->transport);
		license_free(rdp->license);
		input_free(rdp->input);
		update_free(rdp->update);
		fastpath_free(rdp->fastpath);
		nego_free(rdp->nego);
		mcs_free(rdp->mcs);
		redirection_free(rdp->redirection);
		mppc_dec_free(rdp->mppc_dec);
		mppc_enc_free(rdp->mppc_enc);
		free(rdp);
	}
}
