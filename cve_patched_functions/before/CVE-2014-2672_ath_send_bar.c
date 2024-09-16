static void ath_send_bar(struct ath_atx_tid *tid, u16 seqno)
{
	if (!tid->an->sta)
		return;

	ieee80211_send_bar(tid->an->vif, tid->an->sta->addr, tid->tidno,
			   seqno << IEEE80211_SEQ_SEQ_SHIFT);
}
