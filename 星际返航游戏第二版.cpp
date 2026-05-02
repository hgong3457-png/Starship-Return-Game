#include <graphics.h>
#include <windows.h>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <tchar.h>

// --- 高级色彩定义 ---
#define DEEP_SPACE RGB(8, 12, 22)   // 优化背景色，替代原本卡顿的星云绘制
#define HUD_BLUE RGB(0, 150, 255)
#define HUD_CYAN RGB(0, 255, 255)
#define ORANGE RGB(255, 140, 0)
#define GOLD RGB(255, 215, 0)

// --- 游戏硬核配置 ---
#define W 800
#define H 600
#define MAX_STARS 300
#define MAX_ROCKS 7      // 维持低密度
#define MAX_BULLETS 8
#define GOAL_SCORE 1000  // 击碎20个障碍物通关

struct Star { float x, y, z; };
struct Rock {
    float x, y, z;
    int active;
    float radius;
    COLORREF baseColor;
};
struct Bullet { float x, y, z; int active; };

// 绘制拟真机甲风 HUD
void DrawSciFiHUD(int hp, int score) {
    COLORREF panelColor = RGB(18, 20, 25);
    COLORREF edgeColor = RGB(35, 40, 50);

    // --- 1. A柱 与 边框 ---
    POINT leftPillar[] = { {0, 0}, {60, 0}, {30, H}, {0, H} };
    POINT rightPillar[] = { {W, 0}, {W - 60, 0}, {W - 30, H}, {W, H} };
    POINT topRim[] = { {60, 0}, {W - 60, 0}, {W - 100, 30}, {100, 30} };

    setfillcolor(panelColor);
    setlinecolor(edgeColor);
    fillpolygon(leftPillar, 4);
    fillpolygon(rightPillar, 4);
    fillpolygon(topRim, 4);

    // --- 2. 底部高科技操作盘 (保留上一版的精美设计) ---
    POINT baseConsole[] = { {30, H}, {150, H - 120}, {W - 150, H - 120}, {W - 30, H} };
    setfillcolor(RGB(20, 22, 28));
    fillpolygon(baseConsole, 4);

    POINT centerConsole[] = { {W / 2 - 140, H}, {W / 2 - 100, H - 130}, {W / 2 + 100, H - 130}, {W / 2 + 140, H} };
    setfillcolor(RGB(28, 32, 40));
    fillpolygon(centerConsole, 4);

    POINT leftScreen[] = { {W / 2 - 250, H - 20}, {W / 2 - 200, H - 100}, {W / 2 - 110, H - 100}, {W / 2 - 150, H - 20} };
    setfillcolor(RGB(10, 15, 20));
    fillpolygon(leftScreen, 4);
    setlinecolor(HUD_BLUE);
    polygon(leftScreen, 4);

    POINT rightScreen[] = { {W / 2 + 250, H - 20}, {W / 2 + 200, H - 100}, {W / 2 + 110, H - 100}, {W / 2 + 150, H - 20} };
    fillpolygon(rightScreen, 4);
    polygon(rightScreen, 4);

    setfillcolor(HUD_CYAN);
    solidrectangle(W / 2 - 180, H - 40, W / 2 - 165, H - 35);
    solidrectangle(W / 2 - 195, H - 40, W / 2 - 185, H - 35);
    setfillcolor(ORANGE);
    solidrectangle(W / 2 + 165, H - 40, W / 2 + 180, H - 35);
    solidcircle(W / 2 + 190, H - 37, 3);

    setlinecolor(edgeColor);

    // --- 3. 经典UI：左上角进度条 ---
    settextcolor(WHITE);
    settextstyle(16, 0, _T("Consolas"));
    outtextxy(20, 15, _T("SYS_PROGRESS:"));
    setfillcolor(RGB(40, 40, 40));
    solidrectangle(20, 35, 170, 45);
    float progress = (float)score / GOAL_SCORE;
    if (progress > 1.0f) progress = 1.0f;
    setfillcolor(HUD_BLUE);
    solidrectangle(20, 35, (int)(20 + progress * 150), 45);

    // --- 4. 经典UI：右上角护盾系统 ---
    outtextxy(W - 170, 15, _T("DEF_SHIELD:"));
    setfillcolor(RGB(40, 10, 10));
    solidrectangle(W - 170, 35, W - 20, 45);
    COLORREF hpCol = (hp > 3) ? RGB(0, 255, 120) : RGB(255, 0, 0);
    setfillcolor(hpCol);
    if (hp > 0) solidrectangle(W - 170, 35, W - 170 + (hp * 15), 45);

    // --- 5. 底部中央：得分数据 ---
    TCHAR s[64];
    _stprintf_s(s, _T("HOSTILES DESTROYED: %d"), score / 50);
    settextcolor(GOLD);
    outtextxy(W / 2 - 90, H - 40, s);
}

int main() {
    initgraph(W, H);
    srand((unsigned)time(NULL));

    int hp = 10;
    int score = 0;
    float worldX = 0, worldY = 0;
    int shootTimer = 0, shakeTime = 0, hitFlash = 0;

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

    while (1) {
        // 【优化2】删除原本导致严重卡顿的满屏圆绘图，直接用背景色替代
        BeginBatchDraw();
        if (hitFlash > 0) {
            setbkcolor(RGB(80, 0, 0)); hitFlash--;
        }
        else {
            setbkcolor(DEEP_SPACE);
        }
        cleardevice();

        int sx = 0, sy = 0;
        if (shakeTime > 0) { sx = rand() % 12 - 6; sy = rand() % 12 - 6; shakeTime--; }

        // 玩家控制
        if (GetAsyncKeyState('W') & 0x8000) worldY += 8.0f;
        if (GetAsyncKeyState('S') & 0x8000) worldY -= 8.0f;
        if (GetAsyncKeyState('A') & 0x8000) worldX += 8.0f;
        if (GetAsyncKeyState('D') & 0x8000) worldX -= 8.0f;

        // 射击系统
        if (shootTimer > 0) shootTimer--;
        if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && shootTimer == 0) {
            for (int i = 0; i < MAX_BULLETS; i++) {
                if (!bullets[i].active) {
                    bullets[i].active = 1; bullets[i].z = 30;
                    bullets[i].x = -worldX; bullets[i].y = -worldY;
                    shootTimer = 10; break;
                }
            }
        }

        // 星空渲染
        for (int i = 0; i < MAX_STARS; i++) {
            stars[i].z -= 10.0f;
            if (stars[i].z <= 1) {
                stars[i].z = 1000.0f;
                stars[i].x = (float)(rand() % 4000 - 2000);
                stars[i].y = (float)(rand() % 4000 - 2000);
            }
            float f = 400.0f / stars[i].z;
            int px = (int)((stars[i].x + worldX) * f + W / 2) + sx;
            int py = (int)((stars[i].y + worldY) * f + H / 2) + sy;

            if (px > 0 && px < W && py > 0 && py < H) {
                int c = (int)(255 * (1 - stars[i].z / 1000.0f));
                COLORREF starCol = RGB(c, c, c + (int)(stars[i].z / 10));
                putpixel(px, py, starCol);
            }
        }

        // 星球渲染逻辑
        for (int i = 0; i < MAX_ROCKS; i++) {
            if (!rocks[i].active) {
                rocks[i].x = -worldX + (float)(rand() % 1200 - 600);
                rocks[i].y = -worldY + (float)(rand() % 800 - 400);
                rocks[i].z = 1000.0f + (rand() % 800);

                // 【优化3】确保只有“小”星球，大幅降低半径
                rocks[i].radius = (float)(rand() % 10 + 8);

                int colorSet = rand() % 5;
                if (colorSet == 0) rocks[i].baseColor = RGB(30, 80, 180);      // 深蓝
                else if (colorSet == 1) rocks[i].baseColor = RGB(180, 60, 30); // 赤红
                else if (colorSet == 2) rocks[i].baseColor = RGB(120, 130, 140); // 灰白
                else if (colorSet == 3) rocks[i].baseColor = RGB(140, 50, 180); // 紫色
                else rocks[i].baseColor = RGB(50, 160, 90);                  // 翠绿

                rocks[i].active = 1;
            }
            rocks[i].z -= 9.0f;

            if (rocks[i].z <= 1) { rocks[i].active = 0; continue; }

            float f = 400.0f / rocks[i].z;
            int rx = (int)((rocks[i].x + worldX) * f + W / 2) + sx;
            int ry = (int)((rocks[i].y + worldY) * f + H / 2) + sy;
            int rS = (int)(rocks[i].radius * f);

            // 【优化1】彻底重写星球渲染：渐变层叠法代替黑斑阴影
            if (rS > 0 && rx > -rS && rx < W + rS && ry > -rS && ry < H + rS) {
                int r = GetRValue(rocks[i].baseColor);
                int g = GetGValue(rocks[i].baseColor);
                int b = GetBValue(rocks[i].baseColor);

                // 画 4 层同心圆，颜色从暗到亮，圆心向左上角偏移，形成完美立体的球面渐变
                for (int step = 0; step < 4; step++) {
                    float currentR = rS * (1.0f - step * 0.2f);
                    int cx = rx - (int)(rS * step * 0.15f);
                    int cy = ry - (int)(rS * step * 0.15f);

                    int curR = min(255, (int)(r * (0.5f + step * 0.3f)));
                    int curG = min(255, (int)(g * (0.5f + step * 0.3f)));
                    int curB = min(255, (int)(b * (0.5f + step * 0.3f)));

                    setfillcolor(RGB(curR, curG, curB));
                    setlinecolor(RGB(curR, curG, curB)); // 隐藏边框线，过渡更自然
                    if (currentR > 0) fillcircle(cx, cy, (int)currentR);
                }
            }

            // 引力震动
            if (rocks[i].z < 150 && rocks[i].z > 10) {
                float distToCenter = sqrt(pow(rx - W / 2, 2) + pow(ry - H / 2, 2));
                if (distToCenter < rS * 4) {
                    worldX -= (rx - W / 2) * 0.02f;
                    worldY -= (ry - H / 2) * 0.02f;
                    if (rand() % 3 == 0) { sx += rand() % 4 - 2; sy += rand() % 4 - 2; }
                }
            }

            // 碰撞检测
            if (rocks[i].z < 20 && rocks[i].z > 5) {
                if (abs(rx - W / 2) < rS * 0.6 && abs(ry - H / 2) < rS * 0.6) {
                    hp--; rocks[i].active = 0; shakeTime = 15; hitFlash = 4;
                }
            }
        }

        // 子弹系统
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (bullets[i].active) {
                bullets[i].z += 40.0f;
                if (bullets[i].z > 1000) bullets[i].active = 0;
                float bf = 400.0f / bullets[i].z;
                int bx = (int)((bullets[i].x + worldX) * bf + W / 2) + sx;
                int by = (int)((bullets[i].y + worldY) * bf + H / 2) + sy;

                setlinecolor(HUD_BLUE);
                setfillcolor(WHITE);
                fillcircle(bx, by, (int)(8 * bf + 1));

                for (int j = 0; j < MAX_ROCKS; j++) {
                    if (rocks[j].active && abs(rocks[j].z - bullets[i].z) < 100) {
                        float rf = 400.0f / rocks[j].z;
                        int rx = (int)((rocks[j].x + worldX) * rf + W / 2);
                        int ry = (int)((rocks[j].y + worldY) * rf + H / 2);
                        int collisionRadius = (int)(rocks[j].radius * rf * 0.8f);

                        if (abs(rx - bx) < collisionRadius && abs(ry - by) < collisionRadius) {
                            rocks[j].active = 0; bullets[i].active = 0;
                            score += 50;
                        }
                    }
                }
            }
        }

        DrawSciFiHUD(hp, score);

        setlinecolor(HUD_BLUE);
        circle(W / 2 + sx, H / 2 + sy, 12);
        line(W / 2 - 20 + sx, H / 2 + sy, W / 2 - 5 + sx, H / 2 + sy);
        line(W / 2 + 5 + sx, H / 2 + sy, W / 2 + 20 + sx, H / 2 + sy);
        line(W / 2 + sx, H / 2 - 20 + sy, W / 2 + sx, H / 2 - 5 + sy);
        line(W / 2 + sx, H / 2 + 5 + sy, W / 2 + sx, H / 2 + 20 + sy);

        if (hp <= 0) {
            settextcolor(RED); settextstyle(40, 0, _T("Consolas"));
            outtextxy(W / 2 - 260, H / 2, _T("SYSTEM FAILURE: HULL DESTROYED"));
            FlushBatchDraw(); Sleep(3000); break;
        }
        if (score >= GOAL_SCORE) {
            settextcolor(GOLD); settextstyle(40, 0, _T("Consolas"));
            outtextxy(W / 2 - 260, H / 2, _T("OBJECTIVE COMPLETE: WARP READY"));
            FlushBatchDraw(); Sleep(3000); break;
        }

        FlushBatchDraw();
        Sleep(16); // 保证大约 60 FPS 顺滑运行
    }

    closegraph();
    return 0;
}