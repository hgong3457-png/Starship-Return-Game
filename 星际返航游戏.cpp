#include<graphics.h>
#include <windows.h>
#include <cstdio>
#include <ctime>
#include <cmath>

// 基础配置
#define W 800
#define H 600
#define MAX_STARS 100
#define MAX_ROCKS 6
#define MAX_BULLETS 5   // 五连发
#define GOAL 1000       // 飞行目标距离

// 1. 定义物体结构体（简单好懂）
struct Star { float x, y, z; };
struct Rock { float x, y, z; int active; };
struct Bullet { float x, y, z; int active; };
struct Planet { float x, y, z; int active; int type; }; // type: 0地球, 1火星
struct BlackHole { float x, y, z; int active; };

int main() {
    initgraph(W, H);
    srand((unsigned)time(NULL));

    // --- 游戏数据初始化 ---
    int hp = 10;
    float score = 0;
    float worldX = 0, worldY = 0; // 视角偏移（模拟飞船转向）
    int shootTimer = 0;           // 射击冷却计时器

    // 初始化星星
    Star stars[MAX_STARS];
    for (int i = 0; i < MAX_STARS; i++) {
        stars[i].x = (float)(rand() % 4000 - 2000);
        stars[i].y = (float)(rand() % 4000 - 2000);
        stars[i].z = (float)(rand() % 1000 + 1);
    }

    // 初始化陨石
    Rock rocks[MAX_ROCKS];
    for (int i = 0; i < MAX_ROCKS; i++) rocks[i].active = 0;

    // 初始化子弹数组（实现连发）
    Bullet bullets[MAX_BULLETS];
    for (int i = 0; i < MAX_BULLETS; i++) bullets[i].active = 0;

    // 初始化星球和黑洞
    Planet pla; pla.active = 0;
    BlackHole bh; bh.active = 0;

    // --- 游戏主循环 ---
    while (1) {
        BeginBatchDraw(); // 开启双缓冲，绘图不闪烁
        cleardevice();

        // 【1】 玩家控制 (WASD转向)
        if (GetAsyncKeyState('W') & 0x8000) worldY += 8;
        if (GetAsyncKeyState('S') & 0x8000) worldY -= 8;
        if (GetAsyncKeyState('A') & 0x8000) worldX += 8;
        if (GetAsyncKeyState('D') & 0x8000) worldX -= 8;

        // 【2】 射击逻辑 (空格连发)
        if (shootTimer > 0) shootTimer--;
        if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && shootTimer == 0) {
            for (int i = 0; i < MAX_BULLETS; i++) {
                if (bullets[i].active == 0) { // 找一颗空闲的子弹
                    bullets[i].active = 1;
                    bullets[i].z = 60;
                    bullets[i].x = -worldX; // 子弹朝着当前准星的方向飞
                    bullets[i].y = -worldY;
                    shootTimer = 10; // 射击间隔
                    break;
                }
            }
        }

        // 【3】 绘制星空（纵深感）
        for (int i = 0; i < MAX_STARS; i++) {
            stars[i].z -= 8;
            if (stars[i].z <= 1) stars[i].z = 1000;
            float f = 400 / stars[i].z;
            int sx = (int)((stars[i].x + worldX) * f + W / 2);
            int sy = (int)((stars[i].y + worldY) * f + H / 2);
            if (sx >= 0 && sx < W && sy >= 0 && sy < H) putpixel(sx, sy, WHITE);
        }

        // 【4】 陨石逻辑（移动、碰撞、被击中）
        for (int i = 0; i < MAX_ROCKS; i++) {
            if (!rocks[i].active) {
                rocks[i].x = (float)(rand() % 2000 - 1000);
                rocks[i].y = (float)(rand() % 2000 - 1000);
                rocks[i].z = 1000; rocks[i].active = 1;
            }
            rocks[i].z -= 10;
            float f = 400 / rocks[i].z;
            int rx = (int)((rocks[i].x + worldX) * f + W / 2);
            int ry = (int)((rocks[i].y + worldY) * f + H / 2);
            int rSize = (int)(25 * f);

            if (rocks[i].z > 1) {
                setfillcolor(LIGHTGRAY);
                solidcircle(rx, ry, rSize);
                // 玩家撞击判定
                if (rocks[i].z < 40 && abs(rx - W / 2) < rSize && abs(ry - H / 2) < rSize) {
                    hp--; rocks[i].active = 0; // 撞到了
                }
            }
            else { rocks[i].active = 0; score += 5; }
        }

        // 【5】 子弹逻辑（移动、击中陨石）
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (bullets[i].active) {
                bullets[i].z += 30;
                if (bullets[i].z > 1000) { bullets[i].active = 0; continue; }

                float bf = 400 / bullets[i].z;
                int bx = (int)((bullets[i].x + worldX) * bf + W / 2);
                int by = (int)((bullets[i].y + worldY) * bf + H / 2);
                setfillcolor(RED);
                solidcircle(bx, by, (int)(8 * bf));

                // 检查是否击中陨石
                for (int j = 0; j < MAX_ROCKS; j++) {
                    if (rocks[j].active && abs(rocks[j].z - bullets[i].z) < 60) {
                        float rf = 400 / rocks[j].z;
                        int rx = (int)((rocks[j].x + worldX) * rf + W / 2);
                        int ry = (int)((rocks[j].y + worldY) * rf + H / 2);
                        if (abs(rx - bx) < 40 && abs(ry - by) < 40) {
                            rocks[j].active = 0; bullets[i].active = 0;
                            score += 20;
                            setfillcolor(YELLOW); // 爆炸特效闪烁
                            solidcircle(rx, ry, (int)(50 * rf));
                        }
                    }
                }
            }
        }

        // 【6】 大型天体逻辑（星球与黑洞）
        // 星球生成与引力
        if (!pla.active && rand() % 300 == 1) {
            pla.z = 1000; pla.x = (float)(rand() % 1600 - 800);
            pla.y = (float)(rand() % 1200 - 600); pla.active = 1; pla.type = rand() % 2;
        }
        if (pla.active) {
            pla.z -= 4;
            float pf = 400 / pla.z;
            int px = (int)((pla.x + worldX) * pf + W / 2);
            int py = (int)((pla.y + worldY) * pf + H / 2);
            int pSize = (int)(150 * pf);
            setfillcolor(pla.type == 0 ? BLUE : RGB(200, 100, 50));
            solidcircle(px, py, pSize);
            // 引力拉扯
            if (pla.z < 600) {
                worldX += (px > W / 2) ? -2 : 2;
                worldY += (py > H / 2) ? -2 : 2;
                setcolor(YELLOW); outtextxy(W / 2 - 50, H - 180, "警告：进入行星引力场");
            }
            if (pla.z <= 1) { pla.active = 0; if (abs(px - W / 2) < pSize) hp -= 3; }
        }

        // 黑洞生成
        if (!bh.active && rand() % 500 == 1) {
            bh.z = 1000; bh.x = (float)(rand() % 1000 - 500);
            bh.y = (float)(rand() % 800 - 400); bh.active = 1;
        }
        if (bh.active) {
            bh.z -= 6;
            float bpf = 400 / bh.z;
            int bpx = (int)((bh.x + worldX) * bpf + W / 2);
            int bpy = (int)((bh.y + worldY) * bpf + H / 2);
            setfillcolor(BLACK); setlinecolor(PURPLE);
            fillcircle(bpx, bpy, (int)(80 * bpf));
            circle(bpx, bpy, (int)(90 * bpf));
            // 强引力
            if (bh.z < 700) {
                worldX += (bpx > W / 2) ? -5 : 5;
                worldY += (bpy > H / 2) ? -5 : 5;
                setcolor(MAGENTA); outtextxy(W / 2 - 60, H - 200, "危险：黑洞强引力！！");
            }
            if (bh.z <= 1) { bh.active = 0; if (abs(bpx - W / 2) < 80 * bpf) hp = 0; }
        }

        // 【7】 绘制驾驶舱 UI (HUD)
        // 侧边框
        setfillcolor(RGB(30, 30, 40));
        solidrectangle(0, 0, 40, H);
        solidrectangle(W - 40, 0, W, H);
        solidrectangle(0, H - 100, W, H);

        // 左上角显示屏：路线进度
        setfillcolor(RGB(10, 20, 10));
        fillrectangle(50, 20, 250, 100);
        setcolor(GREEN);
        outtextxy(60, 30, "航线进度:");
        line(60, 80, 240, 80); // 进度条底线
        fillrectangle(60, 75, 60 + (int)((score / GOAL) * 180), 85); // 进度条

        // 右上角：血条仪表
        setcolor(WHITE); outtextxy(W - 180, 30, "飞船护盾状态:");
        for (int i = 0; i < hp; i++) {
            setfillcolor(i < 3 ? RED : GREEN);
            solidrectangle(W - 180 + i * 12, 55, W - 170 + i * 12, 75);
        }

        // 中心准星
        setcolor(LIGHTGREEN);
        circle(W / 2, H / 2, 12);
        line(W / 2 - 25, H / 2, W / 2 + 25, H / 2);
        line(W / 2, H / 2 - 25, W / 2, H / 2 + 25);

        // 胜负判定
        if (hp <= 0) { settextstyle(40, 0, "黑体"); outtextxy(W / 2 - 100, H / 2, "飞船坠毁"); FlushBatchDraw(); Sleep(3000); break; }
        if (score >= GOAL) { settextstyle(40, 0, "黑体"); outtextxy(W / 2 - 100, H / 2, "成功抵达地球"); FlushBatchDraw(); Sleep(3000); break; }

        FlushBatchDraw();
        Sleep(20);
    }

    closegraph();
    return 0;
}
