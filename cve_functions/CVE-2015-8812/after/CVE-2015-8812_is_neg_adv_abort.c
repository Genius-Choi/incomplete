static int is_neg_adv_abort(unsigned int status)
{
	return status == CPL_ERR_RTX_NEG_ADVICE ||
	       status == CPL_ERR_PERSIST_NEG_ADVICE;
}
