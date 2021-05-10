#include <stdio.h>

#define ROWS 100

void main() {
	int triangle[ROWS][ROWS];
	int path[ROWS][ROWS], duppath[ROWS][ROWS], sums[ROWS], dupsums[ROWS], maxsum, maxsumpos;
	int i, j, k;

	// read the array
	for(i = 0; i < ROWS; i++)
		for(j = 0; j <= i; j++)
			scanf("%d", &triangle[i][j]);

	// print the array
	for(i = 0; i < ROWS; i++) {
		for(j = 0; j <= i; j++)
			printf("%d ", triangle[i][j]);
		printf("\n");
	}

	// reset path sums to 0
	for(k = 0; k < ROWS; k++)
		sums[k] = 0;
	maxsumpos = 0;

	// initialize starting condition for the top element
	path[0][0] = duppath[0][0] = sums[0] = dupsums[0] = maxsum = triangle[0][0];

	for(i = 1; i < ROWS; i++) {
		// left corner element has only one choice for reachability
		duppath[i][0] = triangle[i][0];
		dupsums[0] = sums[0] + triangle[i][0];

		// find the best choice for the rest of the elements
		for(j = 1; j < i; j++) {
			if(sums[j - 1] > sums[j]) {
				// if left path is greater then copy the history
				for(k = i-1; k >=0; k--)
					duppath[k][j] = path[k][j-1];
				dupsums[j] = sums[j-1] + triangle[i][j];
			}
			else {
				dupsums[j] = sums[j] + triangle[i][j];
			}
			duppath[i][j] = triangle[i][j];
		}

		// right corner element has only one choice for reachability
		for(k = i-1; k >= 0; k--)
			duppath[k][i] = path[k][i-1];
		duppath[i][i] = triangle[i][i];
		dupsums[i] = sums[i-1] + triangle[i][i];

		// copy the duplicate arrays to the original, for the next iteration
		printf("with row %d\n", i);
		for(j = 0; j <= i; j++) {
			printf("    ");
			for(k = 0; k <= i; k++) {
				path[j][k] = duppath[j][k];
				printf("%d ", path[j][k]);
			}
			sums[j] = dupsums[j];
			printf("\n");
			if(sums[j] > maxsum) {
				maxsum = sums[j];
				maxsumpos = j;
			}
		}
		printf("    sums: ");
		for(j = 0; j <= i; j++)
			printf("%d ", sums[j]);
		printf(": maxsum = %d maxsumpos = %d\n", maxsum, maxsumpos);
	}
}
