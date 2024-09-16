X509_SIG *d2i_PKCS8_bio(BIO *bp, X509_SIG **p8)
	{
	return ASN1_d2i_bio_of(X509_SIG,X509_SIG_new,d2i_X509_SIG,bp,p8);
	}
