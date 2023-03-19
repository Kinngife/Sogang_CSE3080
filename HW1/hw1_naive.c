#include <stdio.h>
#include <string.h>
#define STRSIZE_MAX 10000000+5
#define PATSIZE_MAX 3000+5
char string[STRSIZE_MAX];
char pattern[PATSIZE_MAX];
int matchidx[STRSIZE_MAX];
int naive(char* str, char* pat);

int main()
{
	FILE* sfile = fopen("string.txt", "r");
	FILE* pfile = fopen("pattern.txt", "r");
	if (sfile == NULL || pfile == NULL)
	{
		printf("The string file does not exist.\n");
		return 0;
	}
	while (1)
	{
		char* str = fgets(string, STRSIZE_MAX, sfile);
		if (str == NULL)
			break;
	}
	while (1)
	{
		char* pat = fgets(pattern, PATSIZE_MAX, pfile);
		if (pat == NULL)
			break;
	}
	fclose(sfile), fclose(pfile);

	int cnt = naive(string, pattern);

	FILE* rfile = fopen("result_naive.txt", "w");
	fprintf(rfile, "%d\n", cnt);
	for (int i = 0; i < cnt; i++)
		fprintf(rfile, "%d ", matchidx[i]);
	fclose(rfile);
	return 0;
}

int naive(char* str, char* pat)
{
	int slen = strlen(str), plen = strlen(pat);
	int match = 0, cnt = 0;
	for (int i = 0; i <= slen - plen; i++)
	{
		if (str[i] == pat[0])
		{
			for (int j = i, k = 0; k < plen; j++, k++)
			{
				if (str[j] == pat[k])
					match = 1;
				else
				{
					match = 0;
					break;
				}
			}
			if (match == 1)
				matchidx[cnt++] = i;
		}
	}
	return cnt;
}