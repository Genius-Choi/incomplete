static bool qeth_is_recovery_task(const struct qeth_card *card)
{
	return card->recovery_task == current;
}
