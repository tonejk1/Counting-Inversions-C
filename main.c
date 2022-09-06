#include <stdio.h>
#include <stdlib.h>

double inv_mergesort(int a[], int n);
double inv_merge(int a[], int b[], int c[], int na, int nb, int nc);

int main()
{
	FILE *f = fopen("array_file.txt", "r");
	if (f == NULL)
	{
		printf("Error! opening file");

		// Program exits if the file pointer returns NULL.
		exit(1);
	}

	int n = 0, num;
	while (fscanf(f, "%d", &num) != EOF)
		n++;
	int *a = (int*) malloc(n* sizeof(int));
	rewind(f);
	int i = 0;
	while (fscanf(f, "%d", &a[i]) != EOF)
		i++;
	fclose(f);

	double d = inv_mergesort(a, n);
	FILE *f1 = fopen("output.txt", "w");
	if (f1 == NULL)
	{
		printf("Error! opening file");

		// Program exits if the file pointer returns NULL.
		exit(1);

	}

	fprintf(f1, "%.0lf\n", d);
	fclose(f1);
	return 0;

}

double inv_mergesort(int a[], int n)
{
	if (n == 1)
		return 0;
	int l[n / 2];
	int r[n - n / 2];
	for (int i = 0; i < n / 2; i++)
	{
		l[i] = a[i];
		r[i] = a[i + n / 2];
	}

	if ((n - n / 2) > (n / 2))
		r[n / 2] = a[n - 1];
	double e = inv_mergesort(l, n / 2);
	double f = inv_mergesort(r, n - n / 2);
	double g = inv_merge(a, l, r, n, n / 2, n - n / 2);
	return (e + f + g);
}

double inv_merge(int a[], int b[], int c[], int na, int nb, int nc)
{
	int i = 0, j = 0;
	double d = 0;
	for (int k = 0; k < na; k++)
	{
		if (i < nb && j < nc)
		{
			if (b[i] < c[j])
			{
				a[k] = b[i];
				i++;
			}
			else if (c[j] < b[i])
			{
				a[k] = c[j];
				j++;
				d = d + (nb - i);
			}
			else
			{
				a[k] = b[i];
				a[k + 1] = c[j];
				i++;
				j++;
				k++;
			}
		}
		else if (i < nb)
		{
			a[k] = b[i];

			i++;
		}
		else if (j < nc)
		{
			a[k] = c[j];
			j++;
		}
	}

	return d;
}
