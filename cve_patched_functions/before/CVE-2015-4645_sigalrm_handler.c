void sigalrm_handler()
{
	rotate = (rotate + 1) % 4;
}
