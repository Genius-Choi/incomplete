get_stats (struct net_device *dev)
{
	long ioaddr = dev->base_addr;
	struct netdev_private *np = netdev_priv(dev);
#ifdef MEM_MAPPING
	int i;
#endif
	unsigned int stat_reg;

	/* All statistics registers need to be acknowledged,
	   else statistic overflow could cause problems */

	np->stats.rx_packets += readl (ioaddr + FramesRcvOk);
	np->stats.tx_packets += readl (ioaddr + FramesXmtOk);
	np->stats.rx_bytes += readl (ioaddr + OctetRcvOk);
	np->stats.tx_bytes += readl (ioaddr + OctetXmtOk);

	np->stats.multicast = readl (ioaddr + McstFramesRcvdOk);
	np->stats.collisions += readl (ioaddr + SingleColFrames)
			     +  readl (ioaddr + MultiColFrames);

	/* detailed tx errors */
	stat_reg = readw (ioaddr + FramesAbortXSColls);
	np->stats.tx_aborted_errors += stat_reg;
	np->stats.tx_errors += stat_reg;

	stat_reg = readw (ioaddr + CarrierSenseErrors);
	np->stats.tx_carrier_errors += stat_reg;
	np->stats.tx_errors += stat_reg;

	/* Clear all other statistic register. */
	readl (ioaddr + McstOctetXmtOk);
	readw (ioaddr + BcstFramesXmtdOk);
	readl (ioaddr + McstFramesXmtdOk);
	readw (ioaddr + BcstFramesRcvdOk);
	readw (ioaddr + MacControlFramesRcvd);
	readw (ioaddr + FrameTooLongErrors);
	readw (ioaddr + InRangeLengthErrors);
	readw (ioaddr + FramesCheckSeqErrors);
	readw (ioaddr + FramesLostRxErrors);
	readl (ioaddr + McstOctetXmtOk);
	readl (ioaddr + BcstOctetXmtOk);
	readl (ioaddr + McstFramesXmtdOk);
	readl (ioaddr + FramesWDeferredXmt);
	readl (ioaddr + LateCollisions);
	readw (ioaddr + BcstFramesXmtdOk);
	readw (ioaddr + MacControlFramesXmtd);
	readw (ioaddr + FramesWEXDeferal);

#ifdef MEM_MAPPING
	for (i = 0x100; i <= 0x150; i += 4)
		readl (ioaddr + i);
#endif
	readw (ioaddr + TxJumboFrames);
	readw (ioaddr + RxJumboFrames);
	readw (ioaddr + TCPCheckSumErrors);
	readw (ioaddr + UDPCheckSumErrors);
	readw (ioaddr + IPCheckSumErrors);
	return &np->stats;
}
