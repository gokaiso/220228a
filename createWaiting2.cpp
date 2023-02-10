int createWaiting2(int puzzle[3][3][3], int x, int y, int z, int pNum) {
    int i;
    int totalCnt = 0;
    int cnt;

    if (y != 1 || z != 1) {
        cnt = 0;
        for (i = 0; i < 3; i++) {
            if (puzzle[i][y][z] == pNum % 2 + 1) break;
            if (puzzle[i][y][z] == pNum) cnt++;
        }
        if (i == 3 && cnt == 1) totalCnt++;
    }

    if (x == z) {
        cnt = 0;
        for (i = 0; i < 3; i++) {
            if (puzzle[i][y][i] == pNum % 2 + 1) break;
            if (puzzle[i][y][i] == pNum) cnt++;
        }
        if (i == 3 && cnt == 1) totalCnt++;
    }

    if (x + z == 2) {
        cnt = 0;
        for (i = 0; i < 3; i++) {
            if (puzzle[i][y][2 - i] == pNum % 2 + 1) break;
            if (puzzle[i][y][2 - i] == pNum) cnt++;
        }
        if (i == 3 && cnt == 1) totalCnt++;
    }

    if (x == y) {
        cnt = 0;
        for (i = 0; i < 3; i++) {
            if (puzzle[i][i][z] == pNum % 2 + 1) break;
            if (puzzle[i][i][z] == pNum) cnt++;
        }
        if (i == 3 && cnt == 1) totalCnt++;
    }

    if (x + y == 2) {
        cnt = 0;
        for (i = 0; i < 3; i++) {
            if (puzzle[i][2 - i][z] == pNum % 2 + 1) break;
            if (puzzle[i][2 - i][z] == pNum) cnt++;
        }
        if (i == 3 && cnt == 1) totalCnt++;
    }

    return totalCnt;
}