dissect_uaprof(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree)
{
	dissect_wbxml_common(tvb, pinfo, tree, &decode_uaprof_wap_248);
}
