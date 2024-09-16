static int micsetup(struct airo_info *ai) {
	int i;

	if (ai->tfm == NULL)
	        ai->tfm = crypto_alloc_cipher("aes", 0, CRYPTO_ALG_ASYNC);

        if (IS_ERR(ai->tfm)) {
                airo_print_err(ai->dev->name, "failed to load transform for AES");
                ai->tfm = NULL;
                return ERROR;
        }

	for (i=0; i < NUM_MODULES; i++) {
		memset(&ai->mod[i].mCtx,0,sizeof(miccntx));
		memset(&ai->mod[i].uCtx,0,sizeof(miccntx));
	}
	return SUCCESS;
}
