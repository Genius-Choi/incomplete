static void tcp_reqsk_record_syn(const struct sock *sk,
				 struct request_sock *req,
				 const struct sk_buff *skb)
{
	if (tcp_sk(sk)->save_syn) {
		u32 len = skb_network_header_len(skb) + tcp_hdrlen(skb);
		u32 *copy;

		copy = kmalloc(len + sizeof(u32), GFP_ATOMIC);
		if (copy) {
			copy[0] = len;
			memcpy(&copy[1], skb_network_header(skb), len);
			req->saved_syn = copy;
		}
	}
}
