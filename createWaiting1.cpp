int createWaiting1(int puzzle[3][3][3],int x, int y,int z,int pNum) {
    int i;
    int totalCnt = 0;
	int cnt;

    

    if (x != 1 || z != 1) {
        cnt = 0;
        for (i = 0; i < 3; i++) {
            if (puzzle[x][i][z] == pNum % 2 + 1) break;
            if (puzzle[x][i][z] == pNum) cnt++;
        }
        if (i == 3 && cnt == 1) totalCnt++;
    }

    if (x != 1 || z != 1) {
        cnt = 0;
        for (i = 0; i < 3; i++) {
            if (puzzle[x][y][i] == pNum % 2 + 1) break;
            if (puzzle[x][y][i] == pNum) cnt++;
        }
        if (i == 3 && cnt == 1) totalCnt++;
    }
    
    if (y == z && x != 1) {
        cnt = 0;
        for (i = 0; i < 3; i++) {
            if (y != i && puzzle[x][i][i] == pNum % 2 + 1) break;
            if (puzzle[x][i][i] == pNum) cnt++;
        }
        if (i == 3 && cnt == 1) totalCnt++;
    }

    cnt = 0;
    if (y + z == 2 && x != 1) {
        for (i = 0; i < 3; i++) {
            if (puzzle[x][i][2 - i] == pNum % 2 + 1) break;
            if (puzzle[x][i][2-i] == pNum) cnt++;
        }
        if (i == 3 && cnt == 1) totalCnt++;
    }

	return totalCnt;
}