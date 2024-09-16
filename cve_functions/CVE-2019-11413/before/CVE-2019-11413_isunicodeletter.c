static int isunicodeletter(int c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || isalpharune(c);
}
