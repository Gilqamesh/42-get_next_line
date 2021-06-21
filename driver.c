#include <stdio.h>
#include "get_next_line.h"
#define HALF_MARGE_BOTTOM "files/half_marge_bottom"
#define ALPHABET "files/alphabet"
#define EMPTY_LINES "files/empty_lines"
#define FILE_PATH ALPHABET

int main(void)
{
	FILE *fp = fopen(FILE_PATH, "r");
	if (!fp)
	{
		printf("could not open file\n");
		return (-1);
	}
	fp = freopen(FILE_PATH, "r", stdin);
	if (!fp)
	{
		printf("could not reopen file\n");
		return (-1);
	}
	char *str;
	int r;
	while ((r = get_next_line(0, &str)) > 0)
	{
		printf("%s", str);
		free(str); 
		printf("\n");
	}
	printf("r = %d", r);
	if (r < 0)
	{
		return (-1);
	}
	fclose(fp);
}
