static void php_image_filter_contrast(INTERNAL_FUNCTION_PARAMETERS)
{
	zval *SIM;
	gdImagePtr im_src;
	long contrast, tmp;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rll", &SIM, &tmp, &contrast) == FAILURE) {
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(im_src, gdImagePtr, &SIM, -1, "Image", le_gd);

	if (im_src == NULL) {
		RETURN_FALSE;
	}

	if (gdImageContrast(im_src, (int)contrast) == 1) {
		RETURN_TRUE;
	}

	RETURN_FALSE;
}
