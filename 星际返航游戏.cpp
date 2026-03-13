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
struct Rock { float x, y, z; int active; float radius; };
struct Bullet { float x, y, z; int active; };

// 绘制拟真机甲风 HUD
void DrawSciFiHUD(int hp, int score) {
    // 1. 绘制带有科技感的切角边框 (模拟玻璃座舱)
    POINT ptsLeftTop[] = { {0,0}, {250,0}, {180, 60}, {0, 60} };
    POINT ptsRightTop[] = { {W,0}, {W - 250,0}, {W - 180, 60}, {W, 60} };
    POINT ptsBottom[] = { {0, H}, {W, H}, {W - 150, H - 80}, {150, H - 80} };

    setfillcolor(RGB(15, 18, 25)); // 深沉金属色
    solidpolygon(ptsLeftTop, 4);
    solidpolygon(ptsRightTop, 4);
    solidpolygon(ptsBottom, 4);

    setlinecolor(HUD_BLUE);
    polygon(ptsLeftTop, 4);
    polygon(ptsRightTop, 4);
    polygon(ptsBottom, 4);

    // 字体设置
    settextcolor(WHITE);
    settextstyle(16, 0, _T("Consolas"));

    // 2. 左上角：进度系统 (Progress)
    outtextxy(20, 15, _T("SYS_PROGRESS:"));
    setfillcolor(RGB(40, 40, 40));
    solidrectangle(20, 35, 170, 45); // 底槽
    float progress = (float)score / GOAL_SCORE;
    if (progress > 1.0f) progress = 1.0f;
    setfillcolor(HUD_BLUE);
    solidrectangle(20, 35, (int)(20 + progress * 150), 45);

    // 3. 右上角：护盾系统 (Shield)
    outtextxy(W - 170, 15, _T("DEF_SHIELD:"));
    setfillcolor(RGB(40, 10, 10));
    solidrectangle(W - 170, 35, W - 20, 45); // 底槽
    COLORREF hpCol = (hp > 3) ? RGB(0, 255, 120) : RGB(255, 0, 0);
    setfillcolor(hpCol);
    if (hp > 0) solidrectangle(W - 170, 35, W - 170 + (hp * 15), 45);

    // 4. 底部中央：雷达占位与得分数据
    TCHAR s[64];
    _stprintf_s(s, _T("HOSTILES DESTROYED: %d"), score / 50);
    settextcolor(GOLD);
    outtextxy(W / 2 - 90, H - 40, s);
}

// 绘制深空星云背景
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

        // 受伤红屏闪烁
        if (hitFlash > 0) {
            setbkcolor(RGB(80, 0, 0)); hitFlash--;
        }
        else {
            setbkcolor(DEEP_SPACE);
        }
        cleardevice();

        // 绘制星云底色
        if (hitFlash == 0) DrawDeepSpace();

        int sx = 0, sy = 0;
        if (shakeTime > 0) { sx = rand() % 12 - 6; sy = rand() % 12 - 6; shakeTime--; }

        // 玩家控制 (微调灵敏度，配合中等速度)
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
                    shootTimer = 10; break; // 射速适中
                }
            }
        }

        // 星空渲染 (加入距离色彩变化)
        for (int i = 0; i < MAX_STARS; i++) {
            stars[i].z -= 10.0f; // 速度适中
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
                // 远处的星星偏蓝紫，近处偏白
                COLORREF starCol = RGB(c, c, c + (int)(stars[i].z / 10));
                putpixel(px, py, starCol);
            }
        }

        // 障碍物 (陨石) 渲染与引力逻辑
        for (int i = 0; i < MAX_ROCKS; i++) {
            if (!rocks[i].active) {
                rocks[i].x = (float)(rand() % 1000 - 500);
                rocks[i].y = (float)(rand() % 800 - 400);
                rocks[i].z = 1000.0f; rocks[i].radius = (float)(rand() % 25 + 25);
                rocks[i].active = 1;
            }
            rocks[i].z -= 9.0f;

            // 错过障碍物不再加分！只有生存压力
            if (rocks[i].z <= 1) { rocks[i].active = 0; continue; }

            float f = 400.0f / rocks[i].z;
            int rx = (int)((rocks[i].x + worldX) * f + W / 2) + sx;
            int ry = (int)((rocks[i].y + worldY) * f + H / 2) + sy;
            int rS = (int)(rocks[i].radius * f);

            // 绘制障碍物 (增加核心暗面，提升体积感)
            setlinecolor(RGB(80, 80, 90));
            setfillcolor(RGB(40, 40, 45));
            fillcircle(rx, ry, rS);
            setfillcolor(RGB(20, 20, 25)); // 暗面核心
            solidcircle(rx + rS / 4, ry + rS / 4, rS / 2);

            // --- 引力拉扯逻辑 ---
            if (rocks[i].z < 150 && rocks[i].z > 10) {
                float distToCenter = sqrt(pow(rx - W / 2, 2) + pow(ry - H / 2, 2));
                // 如果在雷达附近，产生拉扯感 (改变 worldX/Y)
                if (distToCenter < rS * 4) {
                    worldX -= (rx - W / 2) * 0.02f;
                    worldY -= (ry - H / 2) * 0.02f;
                    // 引力震动
                    if (rand() % 3 == 0) { sx += rand() % 4 - 2; sy += rand() % 4 - 2; }
                }
            }

            // --- 极限闪避与碰撞逻辑 ---
            // 只有当极近 (Z<20) 且绝对正面撞击 (范围缩小到 rS * 0.6) 才扣血
            if (rocks[i].z < 20 && rocks[i].z > 5) {
                if (abs(rx - W / 2) < rS * 0.6 && abs(ry - H / 2) < rS * 0.6) {
                    hp--; rocks[i].active = 0; shakeTime = 15; hitFlash = 4;
                }
            }
        }

        // 子弹系统与击碎加分
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (bullets[i].active) {
                bullets[i].z += 40.0f;
                if (bullets[i].z > 1000) bullets[i].active = 0;
                float bf = 400.0f / bullets[i].z;
                int bx = (int)((bullets[i].x + worldX) * bf + W / 2) + sx;
                int by = (int)((bullets[i].y + worldY) * bf + H / 2) + sy;

                // 激光弹体
                setlinecolor(HUD_BLUE);
                setfillcolor(WHITE);
                fillcircle(bx, by, (int)(8 * bf + 1));

                // 击杀检测
                for (int j = 0; j < MAX_ROCKS; j++) {
                    if (rocks[j].active && abs(rocks[j].z - bullets[i].z) < 100) {
                        float rf = 400.0f / rocks[j].z;
                        int rx = (int)((rocks[j].x + worldX) * rf + W / 2);
                        int ry = (int)((rocks[j].y + worldY) * rf + H / 2);
                        if (abs(rx - bx) < 40 && abs(ry - by) < 40) {
                            rocks[j].active = 0; bullets[i].active = 0;
                            score += 50; // 只有击碎才加分！
                        }
                    }
                }
            }
        }

        // 绘制 UI
        DrawSciFiHUD(hp, score);

        // 高级雷达准星
        setlinecolor(HUD_BLUE);
        circle(W / 2 + sx, H / 2 + sy, 12);
        line(W / 2 - 20 + sx, H / 2 + sy, W / 2 - 5 + sx, H / 2 + sy);
        line(W / 2 + 5 + sx, H / 2 + sy, W / 2 + 20 + sx, H / 2 + sy);
        line(W / 2 + sx, H / 2 - 20 + sy, W / 2 + sx, H / 2 - 5 + sy);
        line(W / 2 + sx, H / 2 + 5 + sy, W / 2 + sx, H / 2 + 20 + sy);

        // 胜负判定
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
        Sleep(15); // 稳定帧率
    }

    closegraph();
    return 0;
}