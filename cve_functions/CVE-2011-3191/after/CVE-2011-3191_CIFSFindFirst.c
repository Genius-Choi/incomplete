CIFSFindFirst(const int xid, struct cifs_tcon *tcon,
	      const char *searchName,
	      const struct nls_table *nls_codepage,
	      __u16 *pnetfid,
	      struct cifs_search_info *psrch_inf, int remap, const char dirsep)
{
/* level 257 SMB_ */
	TRANSACTION2_FFIRST_REQ *pSMB = NULL;
	TRANSACTION2_FFIRST_RSP *pSMBr = NULL;
	T2_FFIRST_RSP_PARMS *parms;
	int rc = 0;
	int bytes_returned = 0;
	int name_len;
	__u16 params, byte_count;

	cFYI(1, "In FindFirst for %s", searchName);

findFirstRetry:
	rc = smb_init(SMB_COM_TRANSACTION2, 15, tcon, (void **) &pSMB,
		      (void **) &pSMBr);
	if (rc)
		return rc;

	if (pSMB->hdr.Flags2 & SMBFLG2_UNICODE) {
		name_len =
		    cifsConvertToUCS((__le16 *) pSMB->FileName, searchName,
				 PATH_MAX, nls_codepage, remap);
		/* We can not add the asterik earlier in case
		it got remapped to 0xF03A as if it were part of the
		directory name instead of a wildcard */
		name_len *= 2;
		pSMB->FileName[name_len] = dirsep;
		pSMB->FileName[name_len+1] = 0;
		pSMB->FileName[name_len+2] = '*';
		pSMB->FileName[name_len+3] = 0;
		name_len += 4; /* now the trailing null */
		pSMB->FileName[name_len] = 0; /* null terminate just in case */
		pSMB->FileName[name_len+1] = 0;
		name_len += 2;
	} else {	/* BB add check for overrun of SMB buf BB */
		name_len = strnlen(searchName, PATH_MAX);
/* BB fix here and in unicode clause above ie
		if (name_len > buffersize-header)
			free buffer exit; BB */
		strncpy(pSMB->FileName, searchName, name_len);
		pSMB->FileName[name_len] = dirsep;
		pSMB->FileName[name_len+1] = '*';
		pSMB->FileName[name_len+2] = 0;
		name_len += 3;
	}

	params = 12 + name_len /* includes null */ ;
	pSMB->TotalDataCount = 0;	/* no EAs */
	pSMB->MaxParameterCount = cpu_to_le16(10);
	pSMB->MaxDataCount = cpu_to_le16((tcon->ses->server->maxBuf -
					  MAX_CIFS_HDR_SIZE) & 0xFFFFFF00);
	pSMB->MaxSetupCount = 0;
	pSMB->Reserved = 0;
	pSMB->Flags = 0;
	pSMB->Timeout = 0;
	pSMB->Reserved2 = 0;
	byte_count = params + 1 /* pad */ ;
	pSMB->TotalParameterCount = cpu_to_le16(params);
	pSMB->ParameterCount = pSMB->TotalParameterCount;
	pSMB->ParameterOffset = cpu_to_le16(
	      offsetof(struct smb_com_transaction2_ffirst_req, SearchAttributes)
		- 4);
	pSMB->DataCount = 0;
	pSMB->DataOffset = 0;
	pSMB->SetupCount = 1;	/* one byte, no need to make endian neutral */
	pSMB->Reserved3 = 0;
	pSMB->SubCommand = cpu_to_le16(TRANS2_FIND_FIRST);
	pSMB->SearchAttributes =
	    cpu_to_le16(ATTR_READONLY | ATTR_HIDDEN | ATTR_SYSTEM |
			ATTR_DIRECTORY);
	pSMB->SearchCount = cpu_to_le16(CIFSMaxBufSize/sizeof(FILE_UNIX_INFO));
	pSMB->SearchFlags = cpu_to_le16(CIFS_SEARCH_CLOSE_AT_END |
		CIFS_SEARCH_RETURN_RESUME);
	pSMB->InformationLevel = cpu_to_le16(psrch_inf->info_level);

	/* BB what should we set StorageType to? Does it matter? BB */
	pSMB->SearchStorageType = 0;
	inc_rfc1001_len(pSMB, byte_count);
	pSMB->ByteCount = cpu_to_le16(byte_count);

	rc = SendReceive(xid, tcon->ses, (struct smb_hdr *) pSMB,
			 (struct smb_hdr *) pSMBr, &bytes_returned, 0);
	cifs_stats_inc(&tcon->num_ffirst);

	if (rc) {/* BB add logic to retry regular search if Unix search
			rejected unexpectedly by server */
		/* BB Add code to handle unsupported level rc */
		cFYI(1, "Error in FindFirst = %d", rc);

		cifs_buf_release(pSMB);

		/* BB eventually could optimize out free and realloc of buf */
		/*    for this case */
		if (rc == -EAGAIN)
			goto findFirstRetry;
	} else { /* decode response */
		/* BB remember to free buffer if error BB */
		rc = validate_t2((struct smb_t2_rsp *)pSMBr);
		if (rc == 0) {
			unsigned int lnoff;

			if (pSMBr->hdr.Flags2 & SMBFLG2_UNICODE)
				psrch_inf->unicode = true;
			else
				psrch_inf->unicode = false;

			psrch_inf->ntwrk_buf_start = (char *)pSMBr;
			psrch_inf->smallBuf = 0;
			psrch_inf->srch_entries_start =
				(char *) &pSMBr->hdr.Protocol +
					le16_to_cpu(pSMBr->t2.DataOffset);
			parms = (T2_FFIRST_RSP_PARMS *)((char *) &pSMBr->hdr.Protocol +
			       le16_to_cpu(pSMBr->t2.ParameterOffset));

			if (parms->EndofSearch)
				psrch_inf->endOfSearch = true;
			else
				psrch_inf->endOfSearch = false;

			psrch_inf->entries_in_buffer =
					le16_to_cpu(parms->SearchCount);
			psrch_inf->index_of_last_entry = 2 /* skip . and .. */ +
				psrch_inf->entries_in_buffer;
			lnoff = le16_to_cpu(parms->LastNameOffset);
			if (tcon->ses->server->maxBuf - MAX_CIFS_HDR_SIZE <
			      lnoff) {
				cERROR(1, "ignoring corrupt resume name");
				psrch_inf->last_entry = NULL;
				return rc;
			}

			psrch_inf->last_entry = psrch_inf->srch_entries_start +
							lnoff;

			*pnetfid = parms->SearchHandle;
		} else {
			cifs_buf_release(pSMB);
		}
	}

	return rc;
}
