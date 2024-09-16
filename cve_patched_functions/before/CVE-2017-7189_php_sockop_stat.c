static int php_sockop_stat(php_stream *stream, php_stream_statbuf *ssb)
{
#if ZEND_WIN32
	return 0;
#else
	php_netstream_data_t *sock = (php_netstream_data_t*)stream->abstract;

	return zend_fstat(sock->socket, &ssb->sb);
#endif
}
