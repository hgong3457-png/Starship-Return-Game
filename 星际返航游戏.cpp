#include <graphics.h>
#include <windows.h>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <tchar.h>

//高级色彩定义 
#define DEEP_SPACE RGB(5, 5, 15)
#define NEBULA_PURPLE RGB(20, 10, 35)
#define NEBULA_BLUE RGB(10, 20, 40)
#define HUD_BLUE RGB(0, 150, 255)
#define ORANGE RGB(255, 140, 0)
#define GOLD RGB(255, 215, 0)

//游戏参数配置
#define W 800
#define H 600
#define MAX_STARS 300
#define MAX_ROCKS 10
#define MAX_BULLETS 8
#define MAX_PARTICLES 100 
#define GOAL_SCORE 1000  

// ！引力场核心物理参数
#define GRAVITY_DIST_MAX 600.0f         
#define GRAVITY_Z_MAX 800.0f            
#define GRAVITY_RADIUS_THRESHOLD 40.0f  

struct Star { float x, y, z; };
struct Rock { float x, y, z; int active; float radius; int isBlackHole; COLORREF colLine; COLORREF colBase; COLORREF colCore; };
struct Bullet { float x, y, z; int active; };
struct Particle { float x, y, z; float vx, vy, vz; int life; int active; COLORREF col; };

//HUD 绘制
void DrawSciFiHUD(int hp, int score) {
    POINT ptsLeftTop[] = { {0,0}, {250,0}, {180, 60}, {0, 60} };
    POINT ptsRightTop[] = { {W,0}, {W - 250,0}, {W - 180, 60}, {W, 60} };
    POINT ptsBottom[] = { {0, H}, {W, H}, {W - 150, H - 80}, {150, H - 80} };

    setfillcolor(RGB(15, 18, 25));
    solidpolygon(ptsLeftTop, 4); solidpolygon(ptsRightTop, 4); solidpolygon(ptsBottom, 4);
    setlinecolor(HUD_BLUE);
    polygon(ptsLeftTop, 4); polygon(ptsRightTop, 4); polygon(ptsBottom, 4);

    COLORREF btnCol;
    if (hp > 3) btnCol = RGB(0, 200, 80);
    else {
        if ((GetTickCount() / 200) % 2 == 0) btnCol = RGB(255, 40, 40);
        else btnCol = RGB(80, 10, 10);
    }

    for (int i = 0; i < 8; i++) {
        int bx = W / 2 - 180 + i * 46; int by = H - 65;
        setfillcolor(btnCol); solidrectangle(bx, by, bx + 35, by + 12);
        setlinecolor(RGB(30, 50, 70)); rectangle(bx, by, bx + 35, by + 12);
    }

    settextcolor(WHITE); settextstyle(16, 0, _T("Consolas")); outtextxy(20, 15, _T("SYS_PROGRESS:"));
    setfillcolor(RGB(40, 40, 40)); solidrectangle(20, 35, 170, 45);
    float progress = (float)score / GOAL_SCORE; if (progress > 1.0f) progress = 1.0f;
    setfillcolor(HUD_BLUE); solidrectangle(20, 35, (int)(20 + progress * 150), 45);

    outtextxy(W - 170, 15, _T("DEF_SHIELD:"));
    setfillcolor(RGB(40, 10, 10)); solidrectangle(W - 170, 35, W - 20, 45);
    COLORREF hpCol = (hp > 3) ? RGB(0, 255, 120) : RGB(255, 0, 0);
    setfillcolor(hpCol); if (hp > 0) solidrectangle(W - 170, 35, W - 170 + (hp * 15), 45);

    TCHAR s[64]; _stprintf_s(s, _T("HOSTILES DESTROYED: %d"), score / 50);
    settextcolor(GOLD); outtextxy(W / 2 - 90, H - 40, s);
}

//主菜单 UI 

void ShowMenu() {
    IMAGE menu_bg;
    loadimage(&menu_bg, _T("menu_bg.jpg"), W, H);
    bool showIntro = false; ExMessage msg;
    int btnW = 220, btnH = 60;
    int startX = W / 2 - btnW / 2, startY = H / 2 - 10;
    int introX = W / 2 - btnW / 2, introY = H / 2 + 80;
    while (true) {
        BeginBatchDraw();
        putimage(0, 0, &menu_bg);
        if (!showIntro) {
            settextcolor(HUD_BLUE); settextstyle(60, 0, _T("Consolas"), 0, 0, FW_BOLD, false, false, false);
            outtextxy(W / 2 - textwidth(_T("STAR RETURN")) / 2, H / 3 - 60, _T("STAR RETURN"));
            setfillcolor(HUD_BLUE); solidrectangle(startX, startY, startX + btnW, startY + btnH);
            setlinecolor(WHITE); rectangle(startX, startY, startX + btnW, startY + btnH);
            settextcolor(WHITE); settextstyle(28, 0, _T("Consolas"), 0, 0, FW_BOLD, false, false, false);
            outtextxy(startX + (btnW - textwidth(_T("START"))) / 2, startY + (btnH - textheight(_T("START"))) / 2, _T("START"));
            setfillcolor(ORANGE); solidrectangle(introX, introY, introX + btnW, introY + btnH);
            setlinecolor(WHITE); rectangle(introX, introY, introX + btnW, introY + btnH);
            settextcolor(WHITE); settextstyle(28, 0, _T("Consolas"), 0, 0, FW_BOLD, false, false, false);
            outtextxy(introX + (btnW - textwidth(_T("INTRODUCTION"))) / 2, introY + (btnH - textheight(_T("INTRODUCTION"))) / 2, _T("INTRODUCTION"));
        }
        else {
            setfillcolor(RGB(20, 25, 40)); solidrectangle(100, 100, W - 100, H - 100);
            setlinecolor(HUD_BLUE); rectangle(100, 100, W - 100, H - 100);

            settextcolor(GOLD); settextstyle(30, 0, _T("黑体"), 0, 0, FW_BOLD, false, false, false);
            outtextxy(W / 2 - textwidth(_T("游 戏 说 明 ")) / 2, 130, _T("游 戏 说 明 "));

   
            settextcolor(WHITE); settextstyle(18, 0, _T("黑体"));
            RECT textRect = { 130, 190, W - 130, H - 160 };
            drawtext(_T("  “空旅号”勘探舰因一次意外，于宇宙中失联漂泊多年。有一天忽然捕捉到地球的微弱脉冲，于是它调整航向全速返航。沿途各类陨石群，小行星带，大型天体和黑洞引力陷阱接踵而至，你将操控这艘星际飞船精准规划路线，并可借助伽马聚束激光击碎障碍，助它成功回家。                                       该游戏通过WASD操控移动，空格为发射激光的按钮。小型障碍物（随机对应灰色/黄色球体）可以击碎，大型天体（对应蓝/红色）击打无效，且靠近它一定距离范围内会受到万有引力作用导致撞击。黑洞会有更强更广的引力场作用，一旦被吞噬游戏直接结束，返航失败。游戏界面左上方代表返航进程，本游戏通过击碎的小型障碍物数目来量化返航进度，达到20个即视为成功返航。右上方为实时血量（护盾值），共10格。撞击到小型扣除1格，大型扣2格，黑洞则直接清零。"), &textRect, DT_WORDBREAK);

            settextcolor(RGB(150, 150, 150)); settextstyle(18, 0, _T("Consolas"));
            outtextxy(W / 2 - textwidth(_T(">> CLICK ANYWHERE TO CLOSE <<")) / 2, H - 140, _T(">> CLICK ANYWHERE TO CLOSE <<"));
        }
        FlushBatchDraw();
        while (peekmessage(&msg, EM_MOUSE)) {
            if (msg.message == WM_LBUTTONDOWN) {
                if (showIntro) {
                    showIntro = false;
                }
                else {
                    if (msg.x >= startX && msg.x <= startX + btnW && msg.y >= startY && msg.y <= startY + btnH) return;
                    if (msg.x >= introX && msg.x <= introX + btnW && msg.y >= introY && msg.y <= introY + btnH) {
                        showIntro = true;
                    }
                }
            }
        }
        Sleep(20);
    }
}

int main() {
    initgraph(W, H);
    srand((unsigned)time(NULL));

    ShowMenu();

    IMAGE img_bg;
    loadimage(&img_bg, _T("background.jpg"), W, H);

    int hp = 10, score = 0;
    float worldX = 0, worldY = 0;
    int shootTimer = 0, shakeTime = 0, hitFlash = 0;

    Star stars[MAX_STARS];
    for (int i = 0; i < MAX_STARS; i++) {
        stars[i].x = (float)(rand() % 4000 - 2000);
        stars[i].y = (float)(rand() % 4000 - 2000);
        stars[i].z = (float)(rand() % 1200 + 1);
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

        if (GetAsyncKeyState('W') & 0x8000) worldY += 14.0f;
        if (GetAsyncKeyState('S') & 0x8000) worldY -= 14.0f;
        if (GetAsyncKeyState('A') & 0x8000) worldX += 14.0f;
        if (GetAsyncKeyState('D') & 0x8000) worldX -= 14.0f;

        if (shootTimer > 0) shootTimer--;
        if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && shootTimer == 0) {
            for (int i = 0; i < MAX_BULLETS; i++) {
                if (!bullets[i].active) {
                    bullets[i].active = 1; bullets[i].z = 30;
                    bullets[i].x = -worldX; bullets[i].y = -worldY;
                    shootTimer = 8;
                    break;
                }
            }
        }

        for (int i = 0; i < MAX_STARS; i++) {
            stars[i].z -= 18.0f;
            if (stars[i].z <= 1) {
                stars[i].z = 1200.0f + (float)(rand() % 400);
                stars[i].x = (float)(rand() % 4000 - 2000);
                stars[i].y = (float)(rand() % 4000 - 2000);
            }
            float f = 400.0f / stars[i].z;
            int px = (int)((stars[i].x + worldX) * f + W / 2) + sx;
            int py = (int)((stars[i].y + worldY) * f + H / 2) + sy;
            if (px > 0 && px < W && py > 0 && py < H) {
                int c = (int)(255 * (1 - stars[i].z / 1200.0f));
                if (c < 0) c = 0;
                putpixel(px, py, RGB(c, c, c + (int)(stars[i].z / 10)));
            }
        }

        for (int i = 0; i < MAX_ROCKS; i++) {
            if (!rocks[i].active) {
                rocks[i].x = -worldX + (float)(rand() % 2400 - 1200);
                rocks[i].y = -worldY + (float)(rand() % 1800 - 900);
                rocks[i].z = 1500.0f + (float)(rand() % 1000);
                rocks[i].active = 1;

                int typeRand = rand() % 100;

                if (typeRand < 5) {
                    rocks[i].isBlackHole = 1;
                    rocks[i].radius = (float)(rand() % 20 + 60);
                    rocks[i].colLine = RGB(150, 0, 255); rocks[i].colBase = RGB(10, 5, 20); rocks[i].colCore = RGB(0, 0, 0);
                }
                else if (typeRand < 50) {
                    rocks[i].isBlackHole = 0;
                    rocks[i].radius = (float)(rand() % 15 + 40);
                    int cType = rand() % 2;
                    if (cType == 0) { rocks[i].colLine = RGB(255, 100, 50); rocks[i].colBase = RGB(150, 50, 20); rocks[i].colCore = RGB(80, 20, 10); }
                    else { rocks[i].colLine = HUD_BLUE; rocks[i].colBase = RGB(30, 60, 120); rocks[i].colCore = RGB(10, 20, 60); }
                }
                else {
                    rocks[i].isBlackHole = 0;
                    rocks[i].radius = (float)(rand() % 20 + 15);
                    int cType = rand() % 2;
                    if (cType == 0) { rocks[i].colLine = RGB(200, 200, 200); rocks[i].colBase = RGB(100, 100, 100); rocks[i].colCore = RGB(50, 50, 50); }
                    else { rocks[i].colLine = RGB(255, 255, 100); rocks[i].colBase = RGB(180, 180, 30);  rocks[i].colCore = RGB(80, 80, 20); }
                }
            }

            rocks[i].z -= 15.0f;
            if (rocks[i].z <= 1) { rocks[i].active = 0; continue; }

            float f = 400.0f / rocks[i].z;
            int rx = (int)((rocks[i].x + worldX) * f + W / 2) + sx;
            int ry = (int)((rocks[i].y + worldY) * f + H / 2) + sy;
            int rS = (int)(rocks[i].radius * f);

            if (rS > 0) {
                setlinecolor(rocks[i].colLine);
                setfillcolor(rocks[i].colBase);
                fillcircle(rx, ry, rS);

                int offsetX = 0, offsetY = 0;
                int shift = rS / 4;
                switch (i % 5) {
                case 1: offsetX = -shift; offsetY = -shift; break;
                case 2: offsetX = shift;  offsetY = -shift; break;
                case 3: offsetX = -shift; offsetY = shift;  break;
                case 4: offsetX = shift;  offsetY = shift;  break;
                default: offsetX = 0;      offsetY = 0;      break;
                }
                setfillcolor(rocks[i].colCore);
                solidcircle(rx + offsetX, ry + offsetY, rS / 2);
            }

            if (rocks[i].radius >= GRAVITY_RADIUS_THRESHOLD && rocks[i].z < GRAVITY_Z_MAX && rocks[i].z > 10) {
                float dx = rocks[i].x + worldX, dy = rocks[i].y + worldY;
                float dist2D = sqrtf(dx * dx + dy * dy);
                if (dist2D < GRAVITY_DIST_MAX && dist2D > 1.0f) {
                    float pull = (rocks[i].isBlackHole ? 20.0f : 10.0f) * powf(1.0f - rocks[i].z / GRAVITY_Z_MAX, 2.0f) * powf(1.0f - dist2D / GRAVITY_DIST_MAX, 2.0f);
                    worldX -= (dx / dist2D) * pull; worldY -= (dy / dist2D) * pull;
                }
            }

            if (rocks[i].z < 20 && rocks[i].z > 5) {
                if (abs(rx - W / 2) < rS * 0.7f && abs(ry - H / 2) < rS * 0.7f) {
                    if (rocks[i].isBlackHole) hp = 0;
                    else hp -= (rocks[i].radius >= GRAVITY_RADIUS_THRESHOLD ? 2 : 1);
                    rocks[i].active = 0; shakeTime = 20; hitFlash = 5;
                }
            }
        }

        for (int i = 0; i < MAX_BULLETS; i++) {
            if (bullets[i].active) {
                bullets[i].z += 60.0f;
                if (bullets[i].z > 1500) bullets[i].active = 0;
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

                        if (abs(rx - bx) < rS * 0.9f && abs(ry - by) < rS * 0.9f) {
                            bullets[i].active = 0;
                            if (rocks[j].radius < GRAVITY_RADIUS_THRESHOLD) {
                                int pCount = 0;
                                for (int k = 0; k < MAX_PARTICLES && pCount < 15; k++) {
                                    if (!particles[k].active) {
                                        particles[k].active = 1; particles[k].x = rocks[j].x;
                                        particles[k].y = rocks[j].y; particles[k].z = rocks[j].z;
                                        particles[k].vx = (float)(rand() % 40 - 20); particles[k].vy = (float)(rand() % 40 - 20);
                                        particles[k].vz = (float)(rand() % 10 - 5); particles[k].life = 20 + rand() % 10;

                                        // 【修改点】：在这里改回了原版的高温火花颜色逻辑，不管打碎什么颜色的陨石，爆出的都是橙/金交替的高温火花！
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

        for (int i = 0; i < MAX_PARTICLES; i++) {
            if (particles[i].active) {
                particles[i].x += particles[i].vx; particles[i].y += particles[i].vy;
                particles[i].z += particles[i].vz; particles[i].life--;
                float pf = 400.0f / particles[i].z;
                int px = (int)((particles[i].x + worldX) * pf + W / 2) + sx;
                int py = (int)((particles[i].y + worldY) * pf + H / 2) + sy;
                if (particles[i].life > 0 && pf > 0) {
                    setfillcolor(particles[i].col); solidcircle(px, py, (int)(2 * pf + 1));
                }
                else particles[i].active = 0;
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