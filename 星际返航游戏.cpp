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
#define MAX_PARTICLES 100 // 最大粒子数
#define GOAL_SCORE 1000  

// --- ★ 引力场核心物理参数 ★ ---
#define GRAVITY_DIST_MAX 600.0f         
#define GRAVITY_Z_MAX 800.0f            
#define GRAVITY_RADIUS_THRESHOLD 40.0f  

struct Star { float x, y, z; };
struct Rock { float x, y, z; int active; float radius; int isBlackHole; COLORREF colLine; COLORREF colBase; COLORREF colCore; };
struct Bullet { float x, y, z; int active; };

// 碎片粒子结构
struct Particle {
    float x, y, z;
    float vx, vy, vz;
    int life;     // 生命周期
    int active;
    COLORREF col;
};

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

    COLORREF btnCol;
    if (hp > 3) btnCol = RGB(0, 200, 80);
    else {
        if ((GetTickCount() / 200) % 2 == 0) btnCol = RGB(255, 40, 40);
        else btnCol = RGB(80, 10, 10);
    }

    for (int i = 0; i < 8; i++) {
        int bx = W / 2 - 180 + i * 46;
        int by = H - 65;
        setfillcolor(btnCol);
        solidrectangle(bx, by, bx + 35, by + 12);
        setlinecolor(RGB(30, 50, 70));
        rectangle(bx, by, bx + 35, by + 12);
    }

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

int main() {
    IMAGE img_bg;
    initgraph(W, H);
    srand((unsigned)time(NULL));
    loadimage(&img_bg, _T("background.jpg"), W, H);

    int hp = 10, score = 0;
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

    Particle particles[MAX_PARTICLES];
    for (int i = 0; i < MAX_PARTICLES; i++) particles[i].active = 0;

    while (1) {
        BeginBatchDraw();
        if (hitFlash > 0) { setbkcolor(RGB(80, 0, 0)); hitFlash--; }
        else { setbkcolor(DEEP_SPACE); }
        cleardevice();

        int sx = 0, sy = 0;
        if (shakeTime > 0) { sx = rand() % 12 - 6; sy = rand() % 12 - 6; shakeTime--; }
        if (hitFlash == 0) putimage(sx, sy, &img_bg);

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

        // 星空背景绘制
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
                putpixel(px, py, RGB(c, c, c + (int)(stars[i].z / 10)));
            }
        }

        // 障碍物与引力系统
        for (int i = 0; i < MAX_ROCKS; i++) {
            if (!rocks[i].active) {
                rocks[i].x = -worldX + (float)(rand() % 1600 - 800);
                rocks[i].y = -worldY + (float)(rand() % 1200 - 600);
                rocks[i].z = 1000.0f + (float)(rand() % 800);
                rocks[i].active = 1;
                int typeRand = rand() % 100;
                if (typeRand < 5) { // 黑洞出现概率 5%
                    rocks[i].isBlackHole = 1; rocks[i].radius = (float)(rand() % 20 + 60);
                    rocks[i].colLine = RGB(150, 0, 255); rocks[i].colBase = RGB(10, 5, 20); rocks[i].colCore = RGB(0, 0, 0);
                }
                else {
                    rocks[i].isBlackHole = 0;
                    rocks[i].radius = (typeRand < 50) ? (float)(rand() % 15 + 40) : (float)(rand() % 20 + 15);
                    int cType = rand() % 4;
                    if (cType == 0) { rocks[i].colLine = RGB(200, 200, 200); rocks[i].colBase = RGB(100, 100, 100); rocks[i].colCore = RGB(50, 50, 50); }
                    else if (cType == 1) { rocks[i].colLine = RGB(255, 100, 50); rocks[i].colBase = RGB(150, 50, 20); rocks[i].colCore = RGB(80, 20, 10); }
                    else { rocks[i].colLine = HUD_BLUE; rocks[i].colBase = RGB(30, 60, 120); rocks[i].colCore = RGB(10, 20, 60); }
                }
            }
            rocks[i].z -= 9.0f;
            if (rocks[i].z <= 1) { rocks[i].active = 0; continue; }

            float f = 400.0f / rocks[i].z;
            int rx = (int)((rocks[i].x + worldX) * f + W / 2) + sx;
            int ry = (int)((rocks[i].y + worldY) * f + H / 2) + sy;
            int rS = (int)(rocks[i].radius * f);

            setlinecolor(rocks[i].colLine); setfillcolor(rocks[i].colBase); fillcircle(rx, ry, rS);
            setfillcolor(rocks[i].colCore); solidcircle(rx + rS / 4, ry + rS / 4, rS / 2);

            // 引力逻辑
            if (rocks[i].radius >= GRAVITY_RADIUS_THRESHOLD && rocks[i].z < GRAVITY_Z_MAX && rocks[i].z > 10) {
                float dx = rocks[i].x + worldX, dy = rocks[i].y + worldY;
                float dist2D = sqrt(dx * dx + dy * dy);
                if (dist2D < GRAVITY_DIST_MAX && dist2D > 1.0f) {
                    float pull = (rocks[i].isBlackHole ? 20.0f : 10.0f) * pow(1.0f - rocks[i].z / GRAVITY_Z_MAX, 2) * pow(1.0f - dist2D / GRAVITY_DIST_MAX, 2);
                    worldX -= (dx / dist2D) * pull; worldY -= (dy / dist2D) * pull;
                }
            }

            // 碰撞扣血逻辑 ★ 已修改：黑洞直接导致 HP 为 0 ★
            if (rocks[i].z < 20 && rocks[i].z > 5) {
                if (abs(rx - W / 2) < rS * 0.7 && abs(ry - H / 2) < rS * 0.7) {
                    if (rocks[i].isBlackHole) {
                        hp = 0; // 触碰黑洞，能量护盾直接崩解
                    }
                    else {
                        hp -= (rocks[i].radius >= GRAVITY_RADIUS_THRESHOLD ? 2 : 1);
                    }
                    rocks[i].active = 0; shakeTime = 20; hitFlash = 5;
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
                setlinecolor(HUD_BLUE); setfillcolor(WHITE); fillcircle(bx, by, (int)(8 * bf + 1));

                for (int j = 0; j < MAX_ROCKS; j++) {
                    if (rocks[j].active && abs(rocks[j].z - bullets[i].z) < 100) {
                        float rf = 400.0f / rocks[j].z;
                        int rx = (int)((rocks[j].x + worldX) * rf + W / 2);
                        int ry = (int)((rocks[j].y + worldY) * rf + H / 2);
                        int rS = (int)(rocks[j].radius * rf);

                        if (abs(rx - bx) < rS * 0.9 && abs(ry - by) < rS * 0.9) {
                            bullets[i].active = 0;
                            if (rocks[j].radius < GRAVITY_RADIUS_THRESHOLD) {
                                int pCount = 0;
                                for (int k = 0; k < MAX_PARTICLES && pCount < 15; k++) {
                                    if (!particles[k].active) {
                                        particles[k].active = 1;
                                        particles[k].x = rocks[j].x;
                                        particles[k].y = rocks[j].y;
                                        particles[k].z = rocks[j].z;
                                        particles[k].vx = (float)(rand() % 40 - 20);
                                        particles[k].vy = (float)(rand() % 40 - 20);
                                        particles[k].vz = (float)(rand() % 10 - 5);
                                        particles[k].life = 20 + rand() % 10;
                                        particles[k].col = (rand() % 2 == 0) ? ORANGE : GOLD;
                                        pCount++;
                                    }
                                }
                                rocks[j].active = 0; score += 50;
                            }
                        }
                    }
                }
            }
        }

        // --- 更新并绘制火花粒子 ---
        for (int i = 0; i < MAX_PARTICLES; i++) {
            if (particles[i].active) {
                particles[i].x += particles[i].vx;
                particles[i].y += particles[i].vy;
                particles[i].z += particles[i].vz;
                particles[i].life--;

                float pf = 400.0f / particles[i].z;
                int px = (int)((particles[i].x + worldX) * pf + W / 2) + sx;
                int py = (int)((particles[i].y + worldY) * pf + H / 2) + sy;

                if (particles[i].life > 0 && pf > 0) {
                    setfillcolor(particles[i].col);
                    solidcircle(px, py, (int)(2 * pf + 1));
                }
                else {
                    particles[i].active = 0;
                }
            }
        }

        DrawSciFiHUD(hp, score);
        setlinecolor(HUD_BLUE); circle(W / 2 + sx, H / 2 + sy, 12);
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