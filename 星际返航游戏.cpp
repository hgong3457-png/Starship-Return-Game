#include <graphics.h>
#include <windows.h>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <tchar.h>

// --- 高级色彩定义 ---
#define DEEP_SPACE RGB(5, 5, 15)
#define NEBULA_PURPLE RGB(20, 10, 35)
#define NEBULA_BLUE RGB(10, 20, 40)
#define HUD_BLUE RGB(0, 150, 255)
#define ORANGE RGB(255, 140, 0)
#define GOLD RGB(255, 215, 0)

// --- 游戏硬核配置 ---
#define W 800
#define H 600
#define MAX_STARS 300
#define MAX_ROCKS 10
#define MAX_BULLETS 8
#define GOAL_SCORE 1000  // 击碎20个障碍物通关

struct Star { float x, y, z; };
// 增加 isMassive 属性，标记是否为不可摧毁的引力黑洞/巨型行星
struct Rock { float x, y, z; int active; float radius; int isMassive; COLORREF colLine; COLORREF colBase; COLORREF colCore; };
struct Bullet { float x, y, z; int active; };

// 绘制拟真机甲风 HUD
void DrawSciFiHUD(int hp, int score) {
    POINT ptsLeftTop[] = { {0,0}, {250,0}, {180, 60}, {0, 60} };
    POINT ptsRightTop[] = { {W,0}, {W - 250,0}, {W - 180, 60}, {W, 60} };
    POINT ptsBottom[] = { {0, H}, {W, H}, {W - 150, H - 80}, {150, H - 80} };

    setfillcolor(RGB(15, 18, 25));
    solidpolygon(ptsLeftTop, 4);
    solidpolygon(ptsRightTop, 4);
    solidpolygon(ptsBottom, 4);

    setlinecolor(HUD_BLUE);
    polygon(ptsLeftTop, 4);
    polygon(ptsRightTop, 4);
    polygon(ptsBottom, 4);

    settextcolor(WHITE);
    settextstyle(16, 0, _T("Consolas"));

    outtextxy(20, 15, _T("SYS_PROGRESS:"));
    setfillcolor(RGB(40, 40, 40));
    solidrectangle(20, 35, 170, 45);
    float progress = (float)score / GOAL_SCORE;
    if (progress > 1.0f) progress = 1.0f;
    setfillcolor(HUD_BLUE);
    solidrectangle(20, 35, (int)(20 + progress * 150), 45);

    outtextxy(W - 170, 15, _T("DEF_SHIELD:"));
    setfillcolor(RGB(40, 10, 10));
    solidrectangle(W - 170, 35, W - 20, 45);
    COLORREF hpCol = (hp > 3) ? RGB(0, 255, 120) : RGB(255, 0, 0);
    setfillcolor(hpCol);
    if (hp > 0) solidrectangle(W - 170, 35, W - 170 + (hp * 15), 45);

    TCHAR s[64];
    _stprintf_s(s, _T("HOSTILES DESTROYED: %d"), score / 50);
    settextcolor(GOLD);
    outtextxy(W / 2 - 90, H - 40, s);
}

void DrawDeepSpace() {
    setfillcolor(NEBULA_PURPLE);
    solidcircle(150, 150, 300);
    setfillcolor(NEBULA_BLUE);
    solidcircle(W - 100, H - 100, 400);
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
        BeginBatchDraw();

        if (hitFlash > 0) {
            setbkcolor(RGB(80, 0, 0)); hitFlash--;
        }
        else {
            setbkcolor(DEEP_SPACE);
        }
        cleardevice();
        if (hitFlash == 0) DrawDeepSpace();

        int sx = 0, sy = 0;
        if (shakeTime > 0) { sx = rand() % 12 - 6; sy = rand() % 12 - 6; shakeTime--; }

        if (GetAsyncKeyState('W') & 0x8000) worldY += 8.0f;
        if (GetAsyncKeyState('S') & 0x8000) worldY -= 8.0f;
        if (GetAsyncKeyState('A') & 0x8000) worldX += 8.0f;
        if (GetAsyncKeyState('D') & 0x8000) worldX -= 8.0f;

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

        // --- 障碍物与引力系统 ---
        for (int i = 0; i < MAX_ROCKS; i++) {
            if (!rocks[i].active) {
                // 【修复点1】优化防堆叠：不仅扩大 XY 生成范围，还随机打乱初始 Z 轴深度 (1000~1800)
                if (rand() % 100 < 30) { // 降低正前方出现率至 30%，扩大散布防止过于密集
                    rocks[i].x = -worldX + (float)(rand() % 600 - 300);
                    rocks[i].y = -worldY + (float)(rand() % 400 - 200);
                }
                else {
                    rocks[i].x = -worldX + (float)(rand() % 1600 - 800);
                    rocks[i].y = -worldY + (float)(rand() % 1200 - 600);
                }
                rocks[i].z = 1000.0f + (float)(rand() % 800);
                rocks[i].active = 1;

                // 【修复点2】大星球/黑洞定义：15%概率生成巨大星体，无法摧毁
                if (rand() % 100 < 15) {
                    rocks[i].isMassive = 1;
                    rocks[i].radius = (float)(rand() % 25 + 50); // 半径极大
                    rocks[i].colLine = RGB(150, 0, 255); // 危险的深紫轮廓
                    rocks[i].colBase = RGB(10, 5, 20);   // 吸光材质
                    rocks[i].colCore = RGB(0, 0, 0);     // 纯黑核心
                }
                else {
                    rocks[i].isMassive = 0;
                    rocks[i].radius = (float)(rand() % 15 + 15); // 普通星球变小，对比更明显
                    int cType = rand() % 4;
                    if (cType == 0) {
                        rocks[i].colLine = RGB(80, 80, 90); rocks[i].colBase = RGB(40, 40, 45); rocks[i].colCore = RGB(20, 20, 25);
                    }
                    else if (cType == 1) {
                        rocks[i].colLine = RGB(90, 50, 50); rocks[i].colBase = RGB(50, 25, 25); rocks[i].colCore = RGB(25, 10, 10);
                    }
                    else if (cType == 2) {
                        rocks[i].colLine = RGB(50, 70, 100); rocks[i].colBase = RGB(25, 35, 55); rocks[i].colCore = RGB(10, 15, 30);
                    }
                    else {
                        rocks[i].colLine = RGB(60, 90, 60); rocks[i].colBase = RGB(30, 45, 30); rocks[i].colCore = RGB(15, 25, 15);
                    }
                }
            }
            rocks[i].z -= 9.0f;

            if (rocks[i].z <= 1) { rocks[i].active = 0; continue; }

            float f = 400.0f / rocks[i].z;
            int rx = (int)((rocks[i].x + worldX) * f + W / 2) + sx;
            int ry = (int)((rocks[i].y + worldY) * f + H / 2) + sy;
            int rS = (int)(rocks[i].radius * f);

            setlinecolor(rocks[i].colLine);
            setfillcolor(rocks[i].colBase);
            fillcircle(rx, ry, rS);
            setfillcolor(rocks[i].colCore);
            solidcircle(rx + rS / 4, ry + rS / 4, rS / 2);

            // 【修复点3】丝滑的世界坐标引力系统 (仅针对不可摧毁的大星球)
            if (rocks[i].isMassive && rocks[i].z < 400 && rocks[i].z > 10) {
                // 计算玩家(对应-worldX)到星球(x)的世界坐标物理距离
                float dx = rocks[i].x + worldX;
                float dy = rocks[i].y + worldY;
                float dist2D = sqrt(dx * dx + dy * dy);

                // 如果进入世界坐标系中的引力范围
                if (dist2D < 450.0f) {
                    float pullForce = 200.0f / (rocks[i].z + 30.0f); // 距离越近拉扯越强
                    worldX -= dx * pullForce * 0.002f;
                    worldY -= dy * pullForce * 0.002f;
                    // 引力场震动反馈
                    if (rand() % 4 == 0) { sx += rand() % 4 - 2; sy += rand() % 4 - 2; }
                }
            }

            // 碰撞检测
            if (rocks[i].z < 20 && rocks[i].z > 5) {
                if (abs(rx - W / 2) < rS * 0.7 && abs(ry - H / 2) < rS * 0.7) {
                    hp -= rocks[i].isMassive ? 2 : 1; // 撞黑洞扣双倍血
                    rocks[i].active = 0; shakeTime = 15; hitFlash = 4;
                }
            }
        }

        // --- 子弹与击碎逻辑 ---
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
                        int rS = (int)(rocks[j].radius * rf); // 获取实时的体积判定

                        // 使用动态体积 rS 进行碰撞判定
                        if (abs(rx - bx) < rS * 0.9 && abs(ry - by) < rS * 0.9) {
                            bullets[i].active = 0; // 子弹必定被消耗
                            // 【大星球不可击碎】
                            if (!rocks[j].isMassive) {
                                rocks[j].active = 0;
                                score += 50;
                            }
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
            outtextxy(W / 2 - 160, H / 2, _T("SYSTEM FAILURE: DESTROYED"));
            FlushBatchDraw(); Sleep(3000); break;
        }
        if (score >= GOAL_SCORE) {
            settextcolor(GOLD); settextstyle(40, 0, _T("Consolas"));
            outtextxy(W / 2 - 160, H / 2, _T("OBJECTIVE COMPLETE: WARPING"));
            FlushBatchDraw(); Sleep(3000); break;
        }

        FlushBatchDraw();
        Sleep(15);
    }

    closegraph();
    return 0;
}