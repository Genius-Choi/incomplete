wStream* transport_send_stream_init(rdpTransport* transport, int size)
{
	wStream* s;

	s = StreamPool_Take(transport->ReceivePool, size);

	Stream_EnsureCapacity(s, size);
	Stream_SetPosition(s, 0);

	return s;
}
