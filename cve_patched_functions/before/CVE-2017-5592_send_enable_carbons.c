send_enable_carbons(void **state)
{
    prof_connect();

    prof_input("/carbons on");

    assert_true(stbbr_received(
        "<iq id='*' type='set'><enable xmlns='urn:xmpp:carbons:2'/></iq>"
    ));
}
