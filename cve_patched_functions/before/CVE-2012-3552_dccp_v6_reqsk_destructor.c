static void dccp_v6_reqsk_destructor(struct request_sock *req)
{
	dccp_feat_list_purge(&dccp_rsk(req)->dreq_featneg);
	if (inet6_rsk(req)->pktopts != NULL)
		kfree_skb(inet6_rsk(req)->pktopts);
}
