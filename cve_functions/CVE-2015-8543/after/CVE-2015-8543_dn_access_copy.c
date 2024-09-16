static void dn_access_copy(struct sk_buff *skb, struct accessdata_dn *acc)
{
	unsigned char *ptr = skb->data;

	acc->acc_userl = *ptr++;
	memcpy(&acc->acc_user, ptr, acc->acc_userl);
	ptr += acc->acc_userl;

	acc->acc_passl = *ptr++;
	memcpy(&acc->acc_pass, ptr, acc->acc_passl);
	ptr += acc->acc_passl;

	acc->acc_accl = *ptr++;
	memcpy(&acc->acc_acc, ptr, acc->acc_accl);

	skb_pull(skb, acc->acc_accl + acc->acc_passl + acc->acc_userl + 3);

}
