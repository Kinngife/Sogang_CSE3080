#include <stdio.h>
#include <string.h>
#define STRSIZE_MAX 10000000+5
#define PATSIZE_MAX 3000+5
char string[STRSIZE_MAX];
char pattern[PATSIZE_MAX];
int table[PATSIZE_MAX];
int matchidx[STRSIZE_MAX];
void fail(char* pat);
int kmp(char* str, char* pat);

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

	fail(pattern);
	int cnt = kmp(string, pattern);

	FILE* rfile = fopen("result_kmp.txt", "w");
	fprintf(rfile, "%d\n", cnt);
	for (int i = 0; i < cnt; i++)
		fprintf(rfile, "%d ", matchidx[i]);
	fclose(rfile);

	return 0;
}

void fail(char* pat)
{
	int plen = strlen(pat);
	table[0] = 0;
	for (int i = 1, j = 0; i < plen; i++)	
	{
		table[i] = 0;
		while (j > 0 && pat[i] != pat[j])
			j = table[j - 1];
		if (pat[i] == pat[j])
			table[i] = ++j;
	}
}

int kmp(char* str, char* pat)
{
	int slen = strlen(str), plen = strlen(pat);
	int cnt = 0;
	for (int i = 0, j = 0; i < slen; i++)
	{
		while (j > 0 && str[i] != pat[j])
			j = table[j - 1];	
		if (str[i] == pat[j])
		{
			if (j == plen - 1)
			{
				matchidx[cnt++] = i - plen + 1;
				j = table[j];
			}
			else
				j++;
		}
	}
	return cnt;
}