ar6000_update_bdaddr(struct ar6_softc *ar)
{

        if (setupbtdev != 0) {
            u32 address;

           if (BMIReadMemory(ar->arHifDevice,
		HOST_INTEREST_ITEM_ADDRESS(ar, hi_board_data), (u8 *)&address, 4) != 0)
           {
    	      	AR_DEBUG_PRINTF(ATH_DEBUG_ERR,("BMIReadMemory for hi_board_data failed\n"));
           	return A_ERROR;
           }

           if (BMIReadMemory(ar->arHifDevice, address + BDATA_BDADDR_OFFSET, (u8 *)ar->bdaddr, 6) != 0)
           {
    	    	AR_DEBUG_PRINTF(ATH_DEBUG_ERR,("BMIReadMemory for BD address failed\n"));
           	return A_ERROR;
           }
	   AR_DEBUG_PRINTF(ATH_DEBUG_ERR,("BDADDR 0x%x:0x%x:0x%x:0x%x:0x%x:0x%x\n", ar->bdaddr[0],
								ar->bdaddr[1], ar->bdaddr[2], ar->bdaddr[3],
								ar->bdaddr[4], ar->bdaddr[5]));
        }

return 0;
}
