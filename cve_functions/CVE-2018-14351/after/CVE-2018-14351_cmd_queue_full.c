static bool cmd_queue_full(struct ImapData *idata)
{
  if ((idata->nextcmd + 1) % idata->cmdslots == idata->lastcmd)
    return true;

  return false;
}
