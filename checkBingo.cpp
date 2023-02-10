int checkBingo(int puzzle[3][3][3], int x, int y, int z, int pNum) {
    int i;
    int cnt;   

    cnt = 0;
    for (i = 0; i < 3; i++)
        if (y != i && puzzle[x][i][z] == pNum) cnt++;
    if (cnt == 2) return 2;

    cnt = 0;
    for (i = 0; i < 3; i++)
        if (z != i && puzzle[x][y][i] == pNum) cnt++;
    if (cnt == 2) return 2;

    if (y == z) {
        cnt = 0;
        for (i = 0; i < 3; i++)
            if (y != i && puzzle[x][i][i] == pNum) cnt++;
        if (cnt == 2) return 2;
    }

    if (y + z == 2) {
        cnt = 0;
        for (i = 0; i < 3; i++)
            if (y != i && puzzle[x][i][2 - i] == pNum) cnt++;
        if (cnt == 2) return 2;
    }

    if (y != 1 || z != 1) {
        cnt = 0;
        for (i = 0; i < 3; i++)
            if (x != i && puzzle[i][y][z] == pNum) cnt++;
        if (cnt == 2) return 2;
    }

    if (x == z) {
        cnt = 0;
        for (i = 0; i < 3; i++)
            if (x != i && puzzle[i][y][i] == pNum) cnt++;
        if (cnt == 2) return 2;
    }

    if (x + z == 2) {
        cnt = 0;
        for (i = 0; i < 3; i++)
            if (x != i && puzzle[i][y][2 - i] == pNum) cnt++;
        if (cnt == 2) return 2;
    }

    if (x == y) {
        cnt = 0;
        for (i = 0; i < 3; i++)
            if (x != i && puzzle[i][i][z] == pNum) cnt++;
        if (cnt == 2) return 2;
    }

    if (x + y == 2) {
        cnt = 0;
        for (i = 0; i < 3; i++)
            if (x != i && puzzle[i][2-i][z] == pNum) cnt++;
        if (cnt == 2) return 2;
    }

    return 0;
}