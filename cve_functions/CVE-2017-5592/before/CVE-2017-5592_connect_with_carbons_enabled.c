connect_with_carbons_enabled(void **state)
{
    prof_input("/carbons on");

    prof_connect();

    assert_true(stbbr_received(
        "<iq id='*' type='set'><enable xmlns='urn:xmpp:carbons:2'/></iq>"
    ));
}
