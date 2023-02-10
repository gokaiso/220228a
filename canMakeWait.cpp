int canMakeWait(int puzzle[][3][3],int x, int pNum) {
	int i,j;
	int cnt;
	int totalCnt=0;

    if (x != 1) {
        for (i = 0; i < 3; i++) {
            cnt = 0;
            for (j = 0; j < 3; j++) {
                if (puzzle[x][i][j] == pNum % 2 + 1) break;
                if (puzzle[x][i][j] == pNum) cnt++;
            }
            if (j == 3 && cnt != 0) totalCnt++;
        }

        for (i = 0; i < 3; i++) {
            cnt = 0;
            for (j = 0; j < 3; j++) {
                if (puzzle[x][j][i] == pNum % 2 + 1) break;
                if (puzzle[x][j][i] == pNum) cnt++;
            }
            if (j == 3 && cnt != 0) totalCnt++;
        }

        cnt = 0;
        for (i = 0; i < 3; i++) {
            if (puzzle[x][i][i] == pNum % 2 + 1) break;
            if (puzzle[x][i][i] == pNum) cnt++;
        }
        if (i == 3 && cnt != 0) totalCnt++;

        cnt = 0;
        for (i = 0; i < 3; i++) {
            if (puzzle[x][i][2-i] == pNum % 2 + 1) break;
            if (puzzle[x][i][2-i] == pNum) cnt++;
        }
        if (i == 3 && cnt != 0) totalCnt++;
    }

    return totalCnt;
}
