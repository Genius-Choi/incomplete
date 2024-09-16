void _radius_close(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	radius_descriptor *raddesc = (radius_descriptor *)rsrc->ptr;
	rad_close(raddesc->radh);
	efree(raddesc);
}
