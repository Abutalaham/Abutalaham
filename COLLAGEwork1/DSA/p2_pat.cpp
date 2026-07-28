#include <stdio.h>
#include <string.h>

int main() {
    char s[100], p[50], r[50], a[200];
    int i = 0, j = 0, k, found = 0;

    printf("Enter main string: ");
    gets(s);
    printf("Enter pattern: ");
    gets(p);
    printf("Enter replace string: ");
    gets(r);
	while (s[i]) {
        for (k = 0; s[i + k] == p[k] && p[k]; k++);

        if (!p[k]) {
            found = 1;
            for (k = 0; r[k]; k++)
                a[j++] = r[k];
            i += strlen(p);
        } else
            a[j++] = s[i++];
    }

    a[j] = '\0';

    if (found) printf("\nResult: %s", a);
    else printf("\nPattern not found");

    return 0;
}

