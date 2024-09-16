uint16_t computeKeyAgreementPrivateValueLength(uint8_t keyAgreementAlgo) {

	uint16_t pvLength = 0;
	switch (keyAgreementAlgo) {
		case ZRTP_KEYAGREEMENT_DH3k	:
			pvLength = 384;
			break;
		case ZRTP_KEYAGREEMENT_DH2k :
			pvLength = 256;
			break;
		case ZRTP_KEYAGREEMENT_EC25	:
			pvLength = 64;
			break;
		case ZRTP_KEYAGREEMENT_EC38	:
			pvLength = 96;
			break;
		case ZRTP_KEYAGREEMENT_EC52 :
			pvLength = 132;
			break;
		default :
			pvLength = 0;
			break;
	}

	return pvLength;
}
