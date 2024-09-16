static void __free_session(struct nfsd4_session *ses)
{
	free_session_slots(ses);
	kfree(ses);
}
