void inet_csk_reqsk_queue_drop_and_put(struct sock *sk, struct request_sock *req)
{
	inet_csk_reqsk_queue_drop(sk, req);
	reqsk_put(req);
}
