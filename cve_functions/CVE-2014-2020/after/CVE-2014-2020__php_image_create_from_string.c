gdImagePtr _php_image_create_from_string(zval **data, char *tn, gdImagePtr (*ioctx_func_p)() TSRMLS_DC)
{
	gdImagePtr im;
	gdIOCtx *io_ctx;

	io_ctx = gdNewDynamicCtxEx(Z_STRLEN_PP(data), Z_STRVAL_PP(data), 0);

	if (!io_ctx) {
		return NULL;
	}

	im = (*ioctx_func_p)(io_ctx);
	if (!im) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Passed data is not in '%s' format", tn);
		io_ctx->gd_free(io_ctx);
		return NULL;
	}

	io_ctx->gd_free(io_ctx);

	return im;
}
