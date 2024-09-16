print_ticket(gpointer name, gpointer value, gpointer data)
{
    ticket_t *ticket = (ticket_t *) value;

    print_as(" %s\t%s%10s", ticket->id,
             ticket->granted ? "granted":"revoked",
             ticket->standby ? " [standby]":"");
    if (ticket->last_granted > -1) {
        print_as(" last-granted=");
        print_date(ticket->last_granted);
    }
    print_as("\n");

    return;
}
