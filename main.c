// This program solves Rose's puzzle. The goal is to turn the snake into a cube.
// Thanks to my friend Robert for bringing the puzzle to my attention.
#include <stdio.h>

#define SIZE (3 * 3 * 3)
int puz[SIZE];
unsigned joints = 0x0157AEDC;
enum Direction {UP, DOWN, LEFT, RIGHT, BACK, FRONT};

void show() {
	for (int z = 0; z < 3; z++) {
		printf("Layer %d\n", z+1);
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				printf("%02d ", puz[z * 9 + y * 3 + x]);
			}
			printf("\n");
		}
	}
	printf("\n");
}

void goFor(int cnt, int x, int y, int z, enum Direction dir) {
	if (cnt >= SIZE) {
		show();
		return;
	}
	if (x < 0 || x > 2 || y < 0 || y > 2 || z < 0 || z > 2) {
		return;
	}
	int *p = &puz[z * 9 + y * 3 + x];
	if (*p) {
		return;
	}
	*p = cnt+1; // mark down
	bool isCorner = (joints & (1 << cnt)) != 0;
	++cnt;
	if (isCorner) {
		switch (dir) {
		case UP: 
		case DOWN: 
			goFor(cnt, x+1, y, z, RIGHT);
			goFor(cnt, x-1, y, z, LEFT);
			goFor(cnt, x, y, z+1, BACK);
			goFor(cnt, x, y, z-1, FRONT);
			break;
		case LEFT:
		case RIGHT:
			goFor(cnt, x, y+1, z, UP);
			goFor(cnt, x, y-1, z, DOWN);
			goFor(cnt, x, y, z+1, BACK);
			goFor(cnt, x, y, z-1, FRONT);
			break;
		case FRONT:
		case BACK:
			goFor(cnt, x+1, y, z, RIGHT);
			goFor(cnt, x-1, y, z, LEFT);
			goFor(cnt, x, y+1, z, UP);
			goFor(cnt, x, y-1, z, DOWN);
			break;
		}
	}
	else {
		switch (dir) {
		case UP: y++; break;
		case DOWN: y--; break;
		case LEFT: x--; break;
		case RIGHT: x++; break;
		case FRONT: z--; break;
		case BACK: z++; break;
		}
		goFor(cnt, x, y, z, dir);
	}
	*p = 0; // clean up
}

int main()
{
	goFor(0,0,0,0, UP);
    return 0;
}

