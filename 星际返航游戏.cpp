#include <graphics.h>
#include <windows.h>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <tchar.h>

// --- 安全宏定义：防止重定义报错 ---
#ifndef ORANGE
#define ORANGE RGB(255, 140, 0)
#endif

#ifndef GOLD
#define GOLD   RGB(255, 215, 0)
#endif

#ifndef CYAN
#define CYAN   RGB(0, 255, 255)
#endif

// --- 游戏配置 ---
#define W 800
#define H 600
#define MAX_STARS 200
#define MAX_ROCKS 7
#define MAX_BULLETS 5
#define GOAL 4000.0f  // 增加目标距离

struct Star { float x, y, z; };
struct Rock { float x, y, z; int active; float radius; };
struct Bullet { float x, y, z; int active; };
struct Planet { float x, y, z; int active; int type; float baseRadius; };

// 绘制驾驶舱：仅保留上下边缘，去掉左右遮挡
void DrawCockpit(int hp, float score, int shakeX, int shakeY) {
    // 1. 顶部窄边框
    setfillcolor(RGB(30, 35, 45));
    solidrectangle(0, 0, W, 25);

    // 2. 底部仪表盘
    setfillcolor(RGB(35, 38, 48));
    solidrectangle(0, H - 130, W, H);

    // 3. 装饰线
    setlinecolor(RGB(0, 150, 255));
    line(0, 25, W, 25);
    line(0, H - 130, W, H - 130);

    // 4. 护盾条 (HP)
    settextcolor(WHITE);
    settextstyle(16, 0, _T("Arial"));
    outtextxy(W / 2 - 40, H - 115, _T("SHIELD HP"));

    setfillcolor(RGB(60, 0, 0)); // 底色
    solidrectangle(W / 2 - 150, H - 90, W / 2 + 150, H - 75);

    COLORREF hpCol = (hp > 3) ? RGB(0, 255, 100) : RGB(255, 50, 0);
    setfillcolor(hpCol);
    if (hp > 0) {
        solidrectangle(W / 2 - 148, H - 88, W / 2 - 148 + (hp * 29), H - 77);
    }

    // 5. 数据面板
    TCHAR s[64];
    _stprintf_s(s, _T("PROGRESS: %.0f / %.0f KM"), score, GOAL);
    settextcolor(GOLD);
    outtextxy(W / 2 - 100, H - 50, s);
}

int main() {
    initgraph(W, H);
    srand((unsigned)time(NULL));

    int hp = 10;
    float score = 0;
    float worldX = 0, worldY = 0;
    int shootTimer = 0;
    int shakeTime = 0;
    int hitFlash = 0;

    Star stars[MAX_STARS];
    for (int i = 0; i < MAX_STARS; i++) {
        stars[i].x = (float)(rand() % 4000 - 2000);
        stars[i].y = (float)(rand() % 4000 - 2000);
        stars[i].z = (float)(rand() % 1000 + 1);
    }

    Rock rocks[MAX_ROCKS];
    for (int i = 0; i < MAX_ROCKS; i++) rocks[i].active = 0;

    Bullet bullets[MAX_BULLETS];
    for (int i = 0; i < MAX_BULLETS; i++) bullets[i].active = 0;

    Planet pla; pla.active = 0;

    while (1) {
        BeginBatchDraw();

        if (hitFlash > 0) {
            setbkcolor(RGB(150, 0, 0)); hitFlash--;
        }
        else {
            setbkcolor(BLACK);
        }
        cleardevice();

        int sx = 0, sy = 0;
        if (shakeTime > 0) {
            sx = rand() % 20 - 10; sy = rand() % 20 - 10;
            shakeTime--;
        }

        // 玩家控制：提速
        if (GetAsyncKeyState('W') & 0x8000) worldY += 10.0f;
        if (GetAsyncKeyState('S') & 0x8000) worldY -= 10.0f;
        if (GetAsyncKeyState('A') & 0x8000) worldX += 10.0f;
        if (GetAsyncKeyState('D') & 0x8000) worldX -= 10.0f;

        // 射击
        if (shootTimer > 0) shootTimer--;
        if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && shootTimer == 0) {
            for (int i = 0; i < MAX_BULLETS; i++) {
                if (!bullets[i].active) {
                    bullets[i].active = 1; bullets[i].z = 50;
                    bullets[i].x = -worldX; bullets[i].y = -worldY;
                    shootTimer = 10; shakeTime = 3; break;
                }
            }
        }

        // 星空：提速 (12.0f)
        for (int i = 0; i < MAX_STARS; i++) {
            stars[i].z -= 12.0f;
            if (stars[i].z <= 1) {
                stars[i].z = 1000.0f;
                stars[i].x = (float)(rand() % 3000 - 1500);
                stars[i].y = (float)(rand() % 3000 - 1500);
            }
            float f = 400.0f / stars[i].z;
            int px = (int)((stars[i].x + worldX) * f + W / 2) + sx;
            int py = (int)((stars[i].y + worldY) * f + H / 2) + sy;
            if (px > 0 && px < W && py > 25 && py < H - 130) {
                int c = (int)(255 * (1 - stars[i].z / 1000.0f));
                putpixel(px, py, RGB(c, c, c));
            }
        }

        // 陨石：提速 (11.0f) + 路径更集中
        for (int i = 0; i < MAX_ROCKS; i++) {
            if (!rocks[i].active) {
                rocks[i].x = (float)(rand() % 600 - 300);
                rocks[i].y = (float)(rand() % 500 - 250);
                rocks[i].z = 1000.0f; rocks[i].radius = (float)(rand() % 20 + 20);
                rocks[i].active = 1;
            }
            rocks[i].z -= 11.0f;
            if (rocks[i].z <= 1) { rocks[i].active = 0; score += 25; continue; }

            float f = 400.0f / rocks[i].z;
            int rx = (int)((rocks[i].x + worldX) * f + W / 2) + sx;
            int ry = (int)((rocks[i].y + worldY) * f + H / 2) + sy;
            int rS = (int)(rocks[i].radius * f);

            if (ry + rS > 25 && ry - rS < H - 130) {
                for (int r = rS; r > 0; r -= 4) {
                    int c = (int)(150 * ((float)r / rS)) + 50;
                    setfillcolor(RGB(c, c - 10, c - 20));
                    fillcircle(rx, ry, r);
                }
            }

            if (rocks[i].z < 60 && rocks[i].z > 5) {
                if (abs(rx - W / 2) < rS + 10 && abs(ry - H / 2) < rS + 10) {
                    hp--; rocks[i].active = 0; shakeTime = 20; hitFlash = 5;
                }
            }
        }

        // 子弹
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (bullets[i].active) {
                bullets[i].z += 40.0f;
                if (bullets[i].z > 1000) bullets[i].active = 0;
                float bf = 400.0f / bullets[i].z;
                int bx = (int)((bullets[i].x + worldX) * bf + W / 2) + sx;
                int by = (int)((bullets[i].y + worldY) * bf + H / 2) + sy;
                setfillcolor(CYAN); solidcircle(bx, by, (int)(10 * bf + 1));

                for (int j = 0; j < MAX_ROCKS; j++) {
                    if (rocks[j].active && abs(rocks[j].z - bullets[i].z) < 150) {
                        float rf = 400.0f / rocks[j].z;
                        int rx = (int)((rocks[j].x + worldX) * rf + W / 2);
                        int ry = (int)((rocks[j].y + worldY) * rf + H / 2);
                        if (abs(rx - bx) < 50 && abs(ry - by) < 50) {
                            rocks[j].active = 0; bullets[i].active = 0; score += 100;
                        }
                    }
                }
            }
        }

        DrawCockpit(hp, score, sx, sy);

        setlinecolor(LIGHTGREEN);
        circle(W / 2 + sx, H / 2 + sy, 10);
        line(W / 2 - 15 + sx, H / 2 + sy, W / 2 + 15 + sx, H / 2 + sy);
        line(W / 2 + sx, H / 2 - 15 + sy, W / 2 + sx, H / 2 + 15 + sy);

        if (hp <= 0) {
            settextcolor(RED); settextstyle(50, 0, _T("Impact"));
            outtextxy(W / 2 - 200, H / 2 - 50, _T("SHIP DESTROYED"));
            FlushBatchDraw(); Sleep(2000); break;
        }
        if (score >= GOAL) {
            settextcolor(GOLD); settextstyle(50, 0, _T("Impact"));
            outtextxy(W / 2 - 200, H / 2 - 50, _T("MISSION SUCCESS"));
            FlushBatchDraw(); Sleep(2000); break;
        }

        FlushBatchDraw();
        Sleep(10);
    }
    closegraph();
    return 0;
}