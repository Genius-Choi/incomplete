void test_stateMachine() {
	int retval;
	my_Context_t aliceClientData, bobClientData;
	uint64_t initialTime;
	uint8_t pingPacketString[ZRTP_PACKET_OVERHEAD+ZRTP_PINGMESSAGE_FIXED_LENGTH]; /* there is no builder for ping packet and it is 24 bytes long(12 bytes of message header, 12 of data + packet overhead*/
	uint32_t CRC;
	uint8_t *CRCbuffer;
	my_Context_t aliceSecondChannelClientData, bobSecondChannelClientData;
	bzrtpCallbacks_t cbs={0} ;

	/* Create zrtp Context */
	bzrtpContext_t *contextAlice = bzrtp_createBzrtpContext(0x12345678); /* Alice's SSRC of main channel is 12345678 */
	bzrtpContext_t *contextBob = bzrtp_createBzrtpContext(0x87654321); /* Bob's SSRC of main channel is 87654321 */

	/* set the cache related callback functions */
	cbs.bzrtp_loadCache=floadAlice;
	cbs.bzrtp_writeCache=fwriteAlice;
	cbs.bzrtp_sendData=bzrtp_sendData;
	bzrtp_setCallbacks(contextAlice, &cbs);

	cbs.bzrtp_loadCache=floadBob;
	cbs.bzrtp_writeCache=fwriteBob;
	cbs.bzrtp_sendData=bzrtp_sendData;
	bzrtp_setCallbacks(contextBob, &cbs);

	/* create the client Data and associate them to the channel contexts */
	memcpy(aliceClientData.nom, "Alice", 6);
	memcpy(bobClientData.nom, "Bob", 4);
	aliceClientData.peerContext = contextBob;
	aliceClientData.peerChannelContext = contextBob->channelContext[0];
	bobClientData.peerContext = contextAlice;
	bobClientData.peerChannelContext = contextAlice->channelContext[0];
	strcpy(aliceClientData.zidFilename, "./ZIDAlice.txt");
	strcpy(bobClientData.zidFilename, "./ZIDBob.txt");


	retval = bzrtp_setClientData(contextAlice, 0x12345678, (void *)&aliceClientData);
	retval += bzrtp_setClientData(contextBob, 0x87654321, (void *)&bobClientData);
	bzrtp_message("Set client data return %x\n", retval);

	/* run the init */
	bzrtp_initBzrtpContext(contextAlice);
	bzrtp_initBzrtpContext(contextBob);

	/* now start the engine */
	initialTime = getCurrentTimeInMs();
	retval = bzrtp_startChannelEngine(contextAlice, 0x12345678);
	bzrtp_message ("Alice starts return %x\n", retval);
	retval = bzrtp_startChannelEngine(contextBob, 0x87654321);
	bzrtp_message ("Bob starts return %x\n", retval);

	/* now start infinite loop until we reach secure state */
	while ((contextAlice->isSecure == 0 || contextBob->isSecure == 0) && (getCurrentTimeInMs()-initialTime<5000)){
		int i;
		/* first check the message queue */
		for (i=0; i<aliceQueueIndex; i++) {
			bzrtp_message("Process a message for Alice\n");
			retval = bzrtp_processMessage(contextAlice, 0x12345678, aliceQueue[i].packetString, aliceQueue[i].packetLength);
			bzrtp_message("Alice processed message %.8s of %d bytes and return %04x\n\n", aliceQueue[i].packetString+16, aliceQueue[i].packetLength, retval);
			memset(aliceQueue[i].packetString, 0, 1000); /* destroy the packet after sending it to the ZRTP engine */
		}
		aliceQueueIndex = 0;

		for (i=0; i<bobQueueIndex; i++) {
			bzrtp_message("Process a message for Bob\n");
			retval = bzrtp_processMessage(contextBob, 0x87654321, bobQueue[i].packetString, bobQueue[i].packetLength);
			bzrtp_message("Bob processed message %.8s of %d bytes and return %04x\n\n", bobQueue[i].packetString+16, bobQueue[i].packetLength, retval);
			memset(bobQueue[i].packetString, 0, 1000); /* destroy the packet after sending it to the ZRTP engine */
		}
		bobQueueIndex = 0;


		/* send the actual time to the zrtpContext */
		bzrtp_iterate(contextAlice, 0x12345678, getCurrentTimeInMs());
		bzrtp_iterate(contextBob, 0x87654321, getCurrentTimeInMs());

		/* sleep for 10 ms */
		sleepMs(10);
	}

	/* compare SAS and check we are in secure mode */
	if ((contextAlice->isSecure == 1) && (contextBob->isSecure == 1)) { /* don't compare sas if we're not secure at we may not have it */
		CU_ASSERT_TRUE((memcmp(contextAlice->channelContext[0]->srtpSecrets.sas, contextBob->channelContext[0]->srtpSecrets.sas, 4) == 0));
		/* call the set verified Sas function */
		bzrtp_SASVerified(contextAlice);
		bzrtp_SASVerified(contextBob);
	} else {
		CU_FAIL("Unable to reach secure state");
	}

	/*** Send alice a ping message from Bob ***/
	/* set packet header and CRC */
	/* preambule */
	pingPacketString[0] = 0x10;
	pingPacketString[1] = 0x00;
	/* Sequence number */
	pingPacketString[2] = (uint8_t)((contextBob->channelContext[0]->selfSequenceNumber>>8)&0x00FF);
	pingPacketString[3] = (uint8_t)(contextBob->channelContext[0]->selfSequenceNumber&0x00FF);
	/* ZRTP magic cookie */
	pingPacketString[4] = (uint8_t)((ZRTP_MAGIC_COOKIE>>24)&0xFF);
	pingPacketString[5] = (uint8_t)((ZRTP_MAGIC_COOKIE>>16)&0xFF);
	pingPacketString[6] = (uint8_t)((ZRTP_MAGIC_COOKIE>>8)&0xFF);
	pingPacketString[7] = (uint8_t)(ZRTP_MAGIC_COOKIE&0xFF);
	/* Source Identifier : insert bob's one: 0x87654321 */
	pingPacketString[8] = 0x87;
	pingPacketString[9] = 0x65;
	pingPacketString[10] = 0x43;
	pingPacketString[11] = 0x21;

	/* message header */
	pingPacketString[12] = 0x50;
	pingPacketString[13] = 0x5a;

	/* length in 32 bits words */
	pingPacketString[14] = 0x00;
	pingPacketString[15] = 0x06;

	/* message type "Ping    " */
	memcpy(pingPacketString+16, "Ping    ",8);

	/* Version on 4 bytes is "1.10" */
	memcpy(pingPacketString+24, "1.10", 4);

	/* a endPointHash, use the first 8 bytes of Bob's ZID */
	memcpy(pingPacketString+28, contextBob->selfZID, 8);

	/* CRC */
	CRC = bzrtp_CRC32(pingPacketString, ZRTP_PINGMESSAGE_FIXED_LENGTH+ZRTP_PACKET_HEADER_LENGTH);
	CRCbuffer = pingPacketString+ZRTP_PINGMESSAGE_FIXED_LENGTH+ZRTP_PACKET_HEADER_LENGTH;
	*CRCbuffer = (uint8_t)((CRC>>24)&0xFF);
	CRCbuffer++;
	*CRCbuffer = (uint8_t)((CRC>>16)&0xFF);
	CRCbuffer++;
	*CRCbuffer = (uint8_t)((CRC>>8)&0xFF);
	CRCbuffer++;
	*CRCbuffer = (uint8_t)(CRC&0xFF);

	bzrtp_message("Process a PING message for Alice\n");
	retval = bzrtp_processMessage(contextAlice, 0x12345678, pingPacketString, ZRTP_PACKET_OVERHEAD+ZRTP_PINGMESSAGE_FIXED_LENGTH);
	bzrtp_message("Alice processed PING message and return %04x\n\n", retval);


	/*** now add a second channel ***/
	retval = bzrtp_addChannel(contextAlice, 0x34567890);
	bzrtp_message("Add a channel to Alice context, return %x\n", retval);
	retval = bzrtp_addChannel(contextBob, 0x09876543);
	bzrtp_message("Add a channel to Bob context, return %x\n", retval);

	/* create the client Data and associate them to the channel contexts */
	memcpy(aliceSecondChannelClientData.nom, "Alice", 6);
	memcpy(bobSecondChannelClientData.nom, "Bob", 4);
	aliceSecondChannelClientData.peerContext = contextBob;
	aliceSecondChannelClientData.peerChannelContext = contextBob->channelContext[1];
	bobSecondChannelClientData.peerContext = contextAlice;
	bobSecondChannelClientData.peerChannelContext = contextAlice->channelContext[1];

	retval = bzrtp_setClientData(contextAlice, 0x34567890, (void *)&aliceSecondChannelClientData);
	retval += bzrtp_setClientData(contextBob, 0x09876543, (void *)&bobSecondChannelClientData);
	bzrtp_message("Set client data return %x\n", retval);

	/* start the channels */
	retval = bzrtp_startChannelEngine(contextAlice, 0x34567890);
	bzrtp_message ("Alice starts return %x\n", retval);
	retval = bzrtp_startChannelEngine(contextBob, 0x09876543);
	bzrtp_message ("Bob starts return %x\n", retval);

	/* now start infinite loop until we reach secure state */
	while ((getCurrentTimeInMs()-initialTime<2000)){
		int i;
		/* first check the message queue */
		for (i=0; i<aliceQueueIndex; i++) {
			bzrtp_message("Process a message for Alice\n");
			retval = bzrtp_processMessage(contextAlice, 0x34567890, aliceQueue[i].packetString, aliceQueue[i].packetLength);
			bzrtp_message("Alice processed message %.8s of %d bytes and return %04x\n\n", aliceQueue[i].packetString+16, aliceQueue[i].packetLength, retval);
			memset(aliceQueue[i].packetString, 0, 1000); /* destroy the packet after sending it to the ZRTP engine */
		}
		aliceQueueIndex = 0;

		for (i=0; i<bobQueueIndex; i++) {
			bzrtp_message("Process a message for Bob\n");
			retval = bzrtp_processMessage(contextBob, 0x09876543, bobQueue[i].packetString, bobQueue[i].packetLength);
			bzrtp_message("Bob processed message %.8s  of %d bytes and return %04x\n\n", bobQueue[i].packetString+16, bobQueue[i].packetLength, retval);
			memset(bobQueue[i].packetString, 0, 1000); /* destroy the packet after sending it to the ZRTP engine */
		}
		bobQueueIndex = 0;


		/* send the actual time to the zrtpContext */
		bzrtp_iterate(contextAlice, 0x34567890, getCurrentTimeInMs());
		bzrtp_iterate(contextBob, 0x09876543, getCurrentTimeInMs());


		/* sleep for 10 ms */
		sleepMs(10);
	}


	CU_ASSERT_TRUE((memcmp(contextAlice->channelContext[1]->srtpSecrets.selfSrtpKey, contextBob->channelContext[1]->srtpSecrets.peerSrtpKey, 16) == 0) && (contextAlice->isSecure == 1) && (contextBob->isSecure == 1));

	dumpContext("\nAlice", contextAlice);
	dumpContext("\nBob", contextBob);



	bzrtp_message("Destroy the contexts\n");
	/* destroy the context */
	bzrtp_destroyBzrtpContext(contextAlice, 0x34567890);
	bzrtp_destroyBzrtpContext(contextBob, 0x09876543);
	bzrtp_message("Destroy the contexts last channel\n");
	bzrtp_destroyBzrtpContext(contextBob, 0x87654321);
	bzrtp_destroyBzrtpContext(contextAlice, 0x12345678);


}
