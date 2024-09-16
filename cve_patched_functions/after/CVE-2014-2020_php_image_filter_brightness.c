static void php_image_filter_brightness(INTERNAL_FUNCTION_PARAMETERS)
{
	zval *SIM;
	gdImagePtr im_src;
	long brightness, tmp;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zll", &SIM, &tmp, &brightness) == FAILURE) {
		RETURN_FALSE;
	}

	ZEND_FETCH_RESOURCE(im_src, gdImagePtr, &SIM, -1, "Image", le_gd);

	if (im_src == NULL) {
		RETURN_FALSE;
	}

	if (gdImageBrightness(im_src, (int)brightness) == 1) {
		RETURN_TRUE;
	}

	RETURN_FALSE;
}
