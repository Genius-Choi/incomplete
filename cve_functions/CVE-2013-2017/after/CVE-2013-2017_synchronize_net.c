void synchronize_net(void)
{
	might_sleep();
	synchronize_rcu();
}
