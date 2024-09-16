int i2d_PKCS8_bio(BIO *bp, X509_SIG *p8)
	{
	return ASN1_i2d_bio_of(X509_SIG,i2d_X509_SIG,bp,p8);
	}
