int i2d_EC_PUBKEY_bio(BIO *bp, EC_KEY *ecdsa)
	{
	return ASN1_i2d_bio_of(EC_KEY,i2d_EC_PUBKEY,bp,ecdsa);
	}
