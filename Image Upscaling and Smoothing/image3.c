#include <stdio.h>

/* Map number to character accordingly */
char get_character(int levels, int level) {
	int last = levels - 1;

	if(level > last)
		return -1;

	if(level == 0)
		return '#';
	else if(level == last)
		return ' ';
	else if(level == 1) {
		if(levels == 3)
			return '.';
		else
			return ':';
	}
	else if(level == 2)
		return '.';

	return -1;
}

int main(int argc, char *argv[]) {
	int  grey_levels, level, times, width, height, i, j, k;
	char character;
	int pixels[100][80], pixels_double[200][160], smoothed[200][160];

	scanf("%d %d %d", &width, &height, &grey_levels);
 	if(width>=80 || height >=100)
 		return -1;

 	grey_levels = 4;

	/* Store the initial numbers altering level 1 to 3 */
 	i=0;
 	j=0;
	while(1) {
		if(scanf("%d %d", &level, &times) == EOF)
			break;
		
		if(level==1)
			level=3;
		
		for(k=0; k<times; k++) {
			pixels[i][j] = level;
			j += 1;
			if(j == width) {
				i += 1;
				j=0;
			}
		}
	}

	/* Calculate Double Image */
	for(i=0; i < height; i++) {
		for(j=0; j < width; j++) {
			pixels_double[2*i][2*j] = pixels[i][j];
			pixels_double[2*i][2*j+1] = (pixels[i][j] + pixels[i][j+1])/2;
			pixels_double[2*i+1][2*j] = (pixels[i][j] + pixels[i+1][j])/2;
			pixels_double[2*i+1][2*j+1] = (pixels[i][j]
				+ pixels[i][j+1] + pixels[i+1][j] + pixels[i+1][j+1] + 1)/4;
		}
	}

	/* Apply Smoothness */
	for(k=0; k<3; k++) {
		for(i=0; i < 2 * height - 1; i++) {
			for(j=0; j < 2 * width - 1; j++) {
				if(i!=0 && i!=2 * height - 2 && j!=0 && j!= 2 * width - 2)
					smoothed[i][j] = (pixels_double[i-1][j-1] +
						2 * pixels_double[i-1][j] + pixels_double[i-1][j+1] +
						2 * pixels_double[i][j-1] + 4 * pixels_double[i][j] +
						2 * pixels_double[i][j+1] + pixels_double[i+1][j-1] +
						2 * pixels_double[i+1][j] + pixels_double[i+1][j+1] + 7)/16;
				else
					smoothed[i][j] = pixels_double[i][j];
			}
		}

		/* Copy smoothed back finishing the iteration */
		for(i=0; i < 2 * height - 1; i++)
			for(j=0; j < 2 * width - 1; j++)
				pixels_double[i][j] = smoothed[i][j];
	}


	/* Print the mapped characters */
	for(i=0; i < 2 * height - 1; i++) {
		for(j=0; j < 2 * width - 1; j++) {
			character = get_character(grey_levels, pixels_double[i][j]);
			if(character == -1)
				return -1;
			printf("%c", character);
		}
		printf("\n");
	}

	return 0;
}