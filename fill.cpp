#include <DxLib.h>

void fill(int i, int j, int k, int player) {
	int Cr= Cr = GetColor(0, 0, 0);

	switch (player) {
	case 1:
		Cr = GetColor(219,84,67);
		break;
	case 2:
		Cr = GetColor(72,169,166);
		break;
	case 3:
		Cr = GetColor(209,204,220);
		break;
	case 4:
		Cr = GetColor(241,237,238);
		break;
	case 5:
		Cr = GetColor(61,84,103);
	}

	DrawTriangleAA((float)(388 - 45 * j + 60 * k), (float)(113 + 150 * i+30*j+15*k), (float)(349 - 45 * j + 60 * k), 
		(float)(139+150*i+30*j+15*k), (float)(401 - 45 * j + 60 * k), (float)(152 + 150 * i + 30 * j + 15 * k), Cr, TRUE);
	DrawTriangleAA((float)(388 - 45 * j + 60 * k), (float)(113 + 150 * i + 30 * j + 15 * k), (float)(440 - 45 * j + 60 * k),
		(float)(126 + 150 * i + 30 * j + 15 * k), (float)(401 - 45 * j + 60 * k), (float)(152 + 150 * i + 30 * j + 15 * k), Cr, TRUE);
}