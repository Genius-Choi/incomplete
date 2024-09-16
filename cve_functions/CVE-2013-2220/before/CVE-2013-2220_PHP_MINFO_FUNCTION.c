PHP_MINFO_FUNCTION(radius)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "radius support", "enabled");
	php_info_print_table_row(2, "version", PHP_RADIUS_VERSION);
	php_info_print_table_end();
}
