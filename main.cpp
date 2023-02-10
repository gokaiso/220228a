//変更
#include <DxLib.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fill(int,int,int,int);
void changeTable(int puzzle[][3][3], int x,int y,int z,int pNum,int flag);
int checkBingo(int puzzle[][3][3], int x, int y, int z,int pNum);
int createWaiting1(int puzzle[][3][3], int x, int y, int z,int pNum);
int createWaiting2(int puzzle[][3][3], int x, int y, int z, int pNum);
int canMakeWait(int puzzle[][3][3],int x, int pNum);
void search(int order, int puzzle[][3][3], int* x, int* y, int* z, int pNum);
int normalBifurcation(int order,int puzzle[][3][3], int x, int y, int z, int pNum);
int hardBifurcation(int order, int puzzle[][3][3], int x, int y, int z, int pNum);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    int puzzle[3][3][3] = { {{-1,-1,-1},{-1,-1,-1},{-1,-1,-1}}, {{-1,-1,-1},{-1,-1,-1},{-1,-1,-1}}, {{0,0,0},{0,0,0},{0,0,0}} };
    float line[8][4] = { {387,110,252,200},{387,110,567,155},{252,200,432,245},{432,245,567,155},{297,170,477,215},{342,140,522,185},{312,215,447,125},{372,230,507,140} };
    char menu[2][9] = { "New Game" ,"  Exit  " };
    char dif[2][3][18] = { {"image/normal0.png","image/normal1.png","image/normal2.png"},{"image/hard0.png","image/hard1.png","image/hard2.png"}};
    char order[2][3][18] = { {"image/first0.png","image/first1.png","image/first2.png"},{"image/second0.png","image/second1.png","image/second2.png"} };
    char think[4][12] = { "thinking","thinking.","thinking..","thinking..." };
    int pNum = 1; //playerNumber
    int diNum = 2;
    int pOrder=1; //playerの順番　1：先行　2：後攻
    int pFlag=0, cFlag=0;
    int num;
    int i,j;
    int x, y, z;
    int mouseX, mouseY;
    int Cr;
    int GrHandle,pHandle, textHandle,barHandle;

    //*************************************
    //グラフィック設定
    //*************************************
    SetBackgroundColor(241,237, 238);
    SetGraphMode(800, 600, 32);
    ChangeWindowMode(TRUE);
    SetDrawScreen(DX_SCREEN_BACK);
   
    if (DxLib_Init() < 0) return -1;

    textHandle = CreateFontToHandle("Lucida Console", 60, 3);
    //************************************************
    //スタート画面
    //************************************************
    barHandle = CreateFontToHandle("Lucida Console", 30, 3);
    textHandle = CreateFontToHandle("Lucida Console", 60, 3);
    GrHandle = LoadGraph("image/title.png");
    DrawGraph(0,125,GrHandle,TRUE);
    DeleteGraph(GrHandle);
    Cr = GetColor(209, 204, 220);
    DrawLineAA(0.0f, 40.0f, 800.0f, 40.0f, Cr);
    DrawLineAA(0.0f,459.0f,800.0f,459.0f,Cr);
    DrawLineAA(0.0f, 530.0f, 800.0f, 530.0f, Cr);
    Cr = GetColor(61, 84, 103);
    DrawStringToHandle(760, 5, "×", Cr,barHandle);
    DrawStringToHandle(256,465,menu[0], Cr, textHandle);
    DrawStringToHandle(256, 536, menu[1], Cr, textHandle);
    ScreenFlip();

    while (1) {
        GetMousePoint(&mouseX, &mouseY);
        if (735 < mouseX && mouseX < 800 && 0 < mouseY && mouseY < 40) {
            Cr = GetColor(209, 204, 220);
            DrawBoxAA(735.0f, 0.0f, 800.0f, 39.0f, Cr, TRUE);
            Cr = GetColor(61, 84, 103);
            DrawStringToHandle(760, 5, "×", Cr, barHandle);
            ScreenFlip();
            while (735 < mouseX && mouseX < 800 && 0 < mouseY && mouseY < 40) {
                if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 1) break;
                GetMousePoint(&mouseX, &mouseY);
            }
            if (735 < mouseX && mouseX<800 && 0<mouseY && mouseY < 40) {
                while (GetMouseInput() == 1);
                i = 1;
                break;
            }
            else {
                Cr = GetColor(241, 237, 238);
                DrawBoxAA(735.0f, 0.0f, 800.0f, 39.0f, Cr, TRUE);
                Cr = GetColor(61, 84, 103);
                DrawStringToHandle(760, 5, "×", Cr, barHandle);
                ScreenFlip();
            }
        }
        else {
            for (i = 0; i < 2; i++)
                if (459 + 71 * i < mouseY && mouseY < 530 + 70 * i) break;
            if (i != 2) {
                Cr = GetColor(209, 204, 220);
                DrawBoxAA(0.0f, (float)(460 + 71 * i), 800.0f, (float)(530 + 70 * i), Cr, TRUE);
                Cr = GetColor(61, 84, 103);
                DrawStringToHandle(256, 465 + 71 * i, menu[i], Cr, textHandle);
                ScreenFlip();
                while (459 + 71 * i < mouseY && mouseY < 530 + 70 * i) {
                    if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 1) break;
                    GetMousePoint(&mouseX, &mouseY);
                }
                if (459 + 71 * i < mouseY && mouseY < 530 + 70 * i) {
                    while (GetMouseInput() == 1);
                    break;
                }
                else {
                    Cr = GetColor(241, 237, 238);
                    DrawBoxAA(0.0f, (float)(460 + 71 * i), 800.0f, (float)(530 + 70 * i), Cr, TRUE);
                    Cr = GetColor(61, 84, 103);
                    DrawStringToHandle(256, 465 + 71 * i, menu[i], Cr, textHandle);
                    ScreenFlip();
                }
            }
        }
    }
    
    if (i == 0) {
        //************************************************
        //選択画面
        //************************************************
        ClearDrawScreen();
        Cr = GetColor(209, 204, 220);
        DrawLineAA(0.0f, 40.0f, 800.0f, 40.0f, Cr);
        DrawLineAA(0.0f, 530.0f, 800.0f, 530.0f, Cr);
        GrHandle = LoadGraph("image/difficulty.png");
        DrawGraph(0, 41, GrHandle, TRUE);
        GrHandle = LoadGraph("image/order.png");
        DrawGraph(0, 286, GrHandle, TRUE);
        DeleteGraph(GrHandle);
        Cr = GetColor(61, 84, 103);
        DrawStringToHandle(256, 536, "  Start", Cr, textHandle);
        for (i = 0; i < 2; i++) {
            if(i== diNum - 1) GrHandle = LoadGraph(dif[i][2]);
            else GrHandle = LoadGraph(dif[i][0]);
            DrawExtendGraph(191+210*i, 165,360+210*i,264, GrHandle, TRUE);
        }
        for (i = 0; i < 2; i++) {
            if (i == pOrder-1) GrHandle = LoadGraph(order[i][2]);
            else GrHandle = LoadGraph(order[i][0]);
            DrawExtendGraph(191 + 210 * i, 410, 360 + 210 * i, 509, GrHandle, TRUE);
        }
        DeleteGraph(GrHandle);
        ScreenFlip();
        while (1) {
            GetMousePoint(&mouseX, &mouseY);
            if (536<mouseY) {
                Cr = GetColor(209, 204, 220);
                DrawBoxAA(0.0f, 531.0f, 800.0f, 600.0f, Cr, TRUE);
                Cr = GetColor(61, 84, 103);
                DrawStringToHandle(256, 536, "  Start", Cr, textHandle);
                ScreenFlip();
                while (536<mouseY) {
                    if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 1) break;
                    GetMousePoint(&mouseX, &mouseY);
                }
                if (536<mouseY) {
                    while (GetMouseInput() == 1);
                    break;
                }
                else {
                    Cr = GetColor(241, 237, 238);
                    DrawBoxAA(0.0f, 531.0f, 800.0f, 600.0f, Cr, TRUE);
                    Cr = GetColor(61, 84, 103);
                    DrawStringToHandle(256, 536, "  Start", Cr, textHandle);
                    ScreenFlip();
                }
            }
            else {
                for (i = 0; i < 2; i++) {
                    if (191 + 210 * i < mouseX && mouseX < 360 + 210 * i && 165 < mouseY && mouseY < 264) break;
                }
                if (i != 2) {
                    if (i != diNum - 1) {
                        GrHandle = LoadGraph(dif[i][1]);
                        DrawExtendGraph(191 + 210 * i, 165, 360 + 210 * i, 264, GrHandle, TRUE);
                        ScreenFlip();
                        while (191 + 210 * i < mouseX && mouseX < 360 + 210 * i && 165 < mouseY && mouseY < 264) {
                            if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 1) break;
                            GetMousePoint(&mouseX, &mouseY);
                        }
                        if (191 + 210 * i < mouseX && mouseX < 360 + 210 * i && 165 < mouseY && mouseY < 264) {
                            Cr = GetColor(241, 237, 238);
                            DrawBoxAA((float)191 + 210 * i, 165.0f, (float)360 + 210 * i, 264.0f, Cr, TRUE);
                            GrHandle = LoadGraph(dif[i][1]);
                            DrawExtendGraph(196 + 210 * i, 170, 355 + 210 * i, 259, GrHandle, TRUE);
                            ScreenFlip();
                            while (GetMouseInput() == 1);
                            GrHandle = LoadGraph(dif[i][2]);
                            DrawExtendGraph(191 + 210 * i, 165, 360 + 210 * i, 264, GrHandle, TRUE);
                            GrHandle = LoadGraph(dif[(i + 1) % 2][0]);
                            DrawExtendGraph(191 + 210 * ((i + 1) % 2), 165, 360 + 210 * ((i + 1) % 2), 264, GrHandle, TRUE);
                            ScreenFlip();
                            diNum = i + 1;
                        }
                        else {
                            GrHandle = LoadGraph(dif[i][0]);
                            DrawExtendGraph(191 + 210 * i, 165, 360 + 210 * i, 264, GrHandle, TRUE);
                            ScreenFlip();
                        }
                        DeleteGraph(GrHandle);
                    }
                }
                else {
                    for (i = 0; i < 2; i++) {
                        if (191 + 210 * i < mouseX && mouseX < 360 + 210 * i && 410 < mouseY && mouseY < 509) break;
                    }
                    if (i != 2 && i != pOrder - 1) {
                        GrHandle = LoadGraph(order[i][1]);
                        DrawExtendGraph(191 + 210 * i, 410, 360 + 210 * i, 509, GrHandle, TRUE);
                        ScreenFlip();
                        while (191 + 210 * i < mouseX && mouseX < 360 + 210 * i && 410 < mouseY && mouseY < 509) {
                            if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 1) break;
                            GetMousePoint(&mouseX, &mouseY);
                        }
                        if (191 + 210 * i < mouseX && mouseX < 360 + 210 * i && 410 < mouseY && mouseY <509) {
                            Cr = GetColor(241, 237, 238);
                            DrawBoxAA((float)191 + 210 * i, 410.0f, (float)360 + 210 * i, 509.0f, Cr, TRUE);
                            GrHandle = LoadGraph(order[i][1]);
                            DrawExtendGraph(196 + 210 * i, 415, 355 + 210 * i, 504, GrHandle, TRUE);
                            ScreenFlip();
                            while (GetMouseInput() == 1);
                            GrHandle = LoadGraph(order[i][2]);
                            DrawExtendGraph(191 + 210 * i, 410, 360 + 210 * i, 509, GrHandle, TRUE);
                            GrHandle = LoadGraph(order[(i + 1) % 2][0]);
                            DrawExtendGraph(191 + 210 * ((i + 1) % 2), 410, 360 + 210 * ((i + 1) % 2), 509, GrHandle, TRUE);
                            ScreenFlip();
                            pOrder = i + 1;
                        }
                        else {
                            GrHandle = LoadGraph(order[i][0]);
                            DrawExtendGraph(191 + 210 * i, 410, 360 + 210 * i, 509, GrHandle, TRUE);
                            ScreenFlip();
                        }
                        DeleteGraph(GrHandle);
                    }
                }
            }
        }

        //************************************************
        //ゲーム画面
        //************************************************
        ClearDrawScreen();
        Cr = GetColor(209, 204, 220);
        DrawLineAA(0.0f, 40.0f, 800.0f, 40.0f, Cr);
        pHandle = CreateFontToHandle(NULL, 80, 3);
        textHandle = CreateFontToHandle(NULL, 30, 3);
        Cr = GetColor(61, 84, 103);
        for (x = 0; x < 3; x++) {
            for (y = 0; y < 8; y++) {
                DrawLineAA(line[y][0], (float)(line[y][1] + 150 * x), line[y][2], (float)(line[y][3] + 150 * x), Cr);
            }
        }
        ScreenFlip();

        while (1) {
            //************************************************
            //Playerの操作
            //************************************************
            if (pNum == pOrder) {
                Cr = GetColor(241, 237, 238);
                DrawStringToHandle(25, 45, "Computer", Cr, pHandle);
                Cr = GetColor(219, 84, 67);
                DrawStringToHandle(25, 45, "You", Cr, pHandle);
                ScreenFlip();
                while (1) {
                    GetMousePoint(&mouseX, &mouseY);
                    for (x = 0; x < 3; x++) {
                        for (y = 0; y < 3; y++) {
                            for (z = 0; z < 3; z++)
                                if (puzzle[x][y][z] == 0 && 3 * mouseY > -2 * mouseX + 1104 + 450 * x + 165 * z && 4 * mouseY > mouseX + 53 + 600 * x + 165 * y
                                    && 3 * mouseY < -2 * mouseX + 1269 + 450 * x + 165 * z && 4 * mouseY < mouseX + 218 + 600 * x + 165 * y) break;
                            if (z != 3) break;
                        }
                        if (y != 3) break;
                    }
                    if (x != 3) {
                        fill(x, y, z, 3);
                        ScreenFlip();
                        while (3 * mouseY > -2 * mouseX + 1104 + 450 * x + 165 * z && 4 * mouseY > mouseX + 53 + 600 * x + 165 * y
                            && 3 * mouseY < -2 * mouseX + 1269 + 450 * x + 165 * z && 4 * mouseY < mouseX + 218 + 600 * x + 165 * y) {
                            GetMousePoint(&mouseX, &mouseY);
                            if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 1) break;
                        }
                        if (3 * mouseY > -2 * mouseX + 1104 + 450 * x + 165 * z && 4 * mouseY > mouseX + 53 + 600 * x + 165 * y
                            && 3 * mouseY < -2 * mouseX + 1269 + 450 * x + 165 * z && 4 * mouseY < mouseX + 218 + 600 * x + 165 * y)
                            break;
                        else {
                            fill(x, y, z, 4);
                            ScreenFlip();
                        }
                    }
                }
                while (GetMouseInput() == 1);
                if (pFlag == 0) pFlag = 1;
                fill(x, y, z, 1);
            }
            //************************************************
            //computerの操作
            //************************************************
            else {
                Cr = GetColor(241, 237, 238);
                DrawStringToHandle(25, 45, "You", Cr, pHandle);
                Cr = GetColor(72, 169, 166);
                DrawStringToHandle(25, 45, "Computer", Cr, pHandle);
                ScreenFlip();
                if (cFlag==0) {
                    if (pFlag==0) {
                        x = 2;
                        y = 1;
                        z = 1;
                    }
                    else if (puzzle[2][1][1] == 0) {
                        x = 2;
                        y = 1;
                        z = 1;
                    }
                    else {
                        x = 2;
                        y = 0;
                        z = 0;
                    }
                    cFlag = 1;
                }
                else{
                    num = 1;
                    while (1) {
                        search(num, puzzle, &x, &y, &z, pNum);
                        if (x != 3) break;
                        num++;
                    }
                }
                for (i = 0; i < 2; i++) {
                    for (j = 0; j < 4; j++) {
                        Cr = GetColor(72, 169, 166);
                        DrawStringToHandle(30, 120, think[j], Cr, textHandle);
                        ScreenFlip();
                        WaitTimer(250);
                        Cr = GetColor(241, 237, 238);
                        DrawStringToHandle(30, 120, think[j], Cr, textHandle);
                    }
                }
                fill(x, y, z, 2);
            }

            ScreenFlip();
            changeTable(puzzle, x, y, z, pNum, 0);

            num = checkBingo(puzzle, x, y, z, pNum);
            if (num == 2) break;


            pNum = pNum % 2 + 1;
            WaitTimer(500);
        }
        WaitTimer(5000);
        ClearDrawScreen();
        if (pNum == pOrder) {
            Cr = GetColor(219, 84, 67);
            DrawStringToHandle(230, 260, "YOU WIN", Cr, pHandle);
            ScreenFlip();
        }
        else {
            Cr = GetColor(72, 169, 166);
            DrawStringToHandle(200, 260, "YOU LOSE...", Cr, pHandle);
            ScreenFlip();
        }
        WaitKey();
    }
    
    DxLib_End();            // ＤＸライブラリ使用の終了処理
    return 0;            // ソフトの終了
}

void search(int order,int puzzle[][3][3], int* x, int* y, int* z, int pNum) {
    int i, j, k;
    int flag;

    for (i = 0; i <3; i++) {
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++) {
                if (puzzle[i][j][k] == 0) {
                    if (order == 14) break;
                    else {
                        flag = hardBifurcation(order, puzzle, i, j, k, pNum);
                        if (flag == 1) break;
                    }
                }
            }
            if (k != 3) break;
        }
        if (j != 3) break;
    }

    *x = i;
    *y = j;
    *z = k;
}

int hardBifurcation(int order, int puzzle[][3][3], int x, int y, int z, int pNum) {
    int cnt = 0;
    int flag = 0;
    int i, j, k;

    if (order == 1 || order == 2) {
        if (order == 1) cnt = checkBingo(puzzle, x, y, z, pNum);
        else            cnt = checkBingo(puzzle, x, y, z, pNum % 2 + 1);
        if (cnt == 2) return 1;
        else return 0;
    }
    else if (3<=order && order <= 13) {
        cnt = createWaiting1(puzzle, x, y, z, pNum) + createWaiting2(puzzle, x, y, z, pNum);
        if (cnt != 0 && order != 9) {
            changeTable(puzzle, x, y, z, pNum, 0);
            search(1, puzzle, &i, &j, &k, pNum);
            if (i != 3) {
                if (order == 3 && cnt == 2) flag = 1;
                else if (order == 4 && x==1&& y!= 1 && z!= 1) {
                    for (i = 0; i < 3; i++)
                        if (puzzle[2][y][i] == 0) break;
                    if (i == 3) flag = 1;
                    else {
                        for (i = 0; i < 3; i++)
                            if (puzzle[2][i][z] == 0) break;
                        if (i == 3) flag = 1;
                    }
                }
                else if (5<=order && order<=8 && i==x) {
                    cnt = canMakeWait(puzzle,x, pNum % 2 + 1);
                    if (cnt<2) {
                        cnt = createWaiting1(puzzle, i, j, k, pNum % 2 + 1) + createWaiting2(puzzle, i, j, k, pNum % 2 + 1);
                        if (cnt == 0) {
                            if (order == 5 && y != 1 && z != 1) flag = 1;
                            if (order == 6) flag = 1;
                        }
                        else if (order == 7 && y != 1 && z != 1)flag = 1;
                        else if (order == 8) flag = 1;
                    }
                }
                else if (10 <= order && order <= 13) {
                    cnt = createWaiting1(puzzle, i, j, k, pNum % 2 + 1) + createWaiting2(puzzle, i, j, k, pNum % 2 + 1);
                    if (cnt == 0) {
                        if (order == 10 && y != 1 && z != 1) flag = 1;
                        if (order == 11) flag = 1;
                    }
                    else if (order == 12 && y != 1 && z != 1)flag = 1;
                    else if (order == 13) flag = 1;
                }
            }
            changeTable(puzzle, x, y, z, 0, -1);
        }
        else if (cnt == 0 && order == 9) {
            changeTable(puzzle, x, y, z, pNum, 0);
            cnt = canMakeWait(puzzle, x, pNum % 2 + 1);
            if (cnt <= 2&&x==2) flag = 1;
            changeTable(puzzle, x, y, z, 0, -1);
        }
    }

    return flag;
}

int nomalBifurcation(int order, int puzzle[][3][3], int x, int y, int z, int pNum) {
    int cnt=0;
    int flag=0;
    int i, j, k;

    if (order==1 || order == 2) {
        if (order == 1) cnt = checkBingo(puzzle, x, y, z, pNum);
        else            cnt = checkBingo(puzzle, x, y, z, pNum % 2 + 1);
        if (cnt == 2) return 1;
        else return 0;
    }
    else if(order<8) {
        cnt = createWaiting1(puzzle, x, y, z, pNum);
        if (cnt != 0) {
            changeTable(puzzle, x, y, z, pNum, 0);
            search(1, puzzle, &i, &j, &k, pNum);
            if (i != 3) {
                if (order == 3 && cnt == 2) flag = 1;
                else if (order == 4 && i==x && y != 1 && z != 1) flag = 1;
                else if (order == 5 || order == 7) {
                    cnt = createWaiting1(puzzle, i, j, k, pNum % 2 + 1);
                    if (cnt == 0) {
                        if (order == 5 && i == x) flag = 1;
                        else if (order == 7) flag = 1;
                    }
                }
                else if (order == 6 && i == x) flag = 1;
            }
            changeTable(puzzle, x, y, z, 0, -1);
        }
    }
    

    return flag;
}
