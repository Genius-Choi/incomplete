authentic_finish(struct sc_card *card)
{
	struct sc_context *ctx = card->ctx;

	LOG_FUNC_CALLED(ctx);

#ifdef ENABLE_SM
	if (card->sm_ctx.ops.close)
		card->sm_ctx.ops.close(card);
#endif

	if (card->drv_data)
		free(card->drv_data);
	card->drv_data = NULL;
	LOG_FUNC_RETURN(ctx, SC_SUCCESS);
}
