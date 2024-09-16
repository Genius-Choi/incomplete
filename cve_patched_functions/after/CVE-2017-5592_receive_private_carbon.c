receive_private_carbon(void **state)
{
    prof_input("/carbons on");

    prof_connect();
    assert_true(stbbr_received(
        "<iq id='*' type='set'><enable xmlns='urn:xmpp:carbons:2'/></iq>"
    ));

    stbbr_send(
        "<presence to='stabber@localhost' from='buddy1@localhost/mobile'>"
            "<priority>10</priority>"
            "<status>On my mobile</status>"
        "</presence>"
    );
    assert_true(prof_output_exact("Buddy1 (mobile) is online, \"On my mobile\""));
    prof_input("/msg Buddy1");
    assert_true(prof_output_exact("unencrypted"));

    stbbr_send(
        "<message type='chat' to='stabber@localhost/profanity' from='buddy1@localhost/mobile'>"
            "<body>Private carbon</body>"
            "<private xmlns='urn:xmpp:carbons:2'/>"
        "</message>"
    );

    assert_true(prof_output_regex("Buddy1/mobile: .+Private carbon"));
}
