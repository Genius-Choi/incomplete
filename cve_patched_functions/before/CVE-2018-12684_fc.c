fc(struct mg_context *ctx)
{
	static struct mg_connection fake_connection;
	fake_connection.phys_ctx = ctx;
	fake_connection.dom_ctx = &(ctx->dd);
	return &fake_connection;
}
