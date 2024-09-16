static void qeth_core_complete(struct ccwgroup_device *gdev)
{
	struct qeth_card *card = dev_get_drvdata(&gdev->dev);
	if (card->discipline && card->discipline->complete)
		card->discipline->complete(gdev);
}
