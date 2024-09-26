PHP_FUNCTION(imagesetinterpolation)
{
	zval *IM;
	gdImagePtr im;
	long method = GD_BILINEAR_FIXED;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r|l", &IM, &method) == FAILURE)  {
		return;
	}

	ZEND_FETCH_RESOURCE(im, gdImagePtr, &IM, -1, "Image", le_gd);

	if (method == -1) {
		 method = GD_BILINEAR_FIXED;
	}
	RETURN_BOOL(gdImageSetInterpolationMethod(im, (gdInterpolationMethod) method));
}
