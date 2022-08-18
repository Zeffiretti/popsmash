#include <raylib.h>
#include <time.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
int main() {
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Test");
  SetTraceLogLevel(LOG_WARNING);
  SetTargetFPS(60);
  SetRandomSeed(time(NULL));  //用当前时间初始化随机数种子。

  //创建一个和屏幕同高同宽透明背景的图片
  Image img = GenImageColor(WINDOW_WIDTH, WINDOW_HEIGHT, BLANK);

  int x = 0;
  int y = 0;
  int hue = 0;
  while (!WindowShouldClose()) {
    //更新圆的位置（texture显示的位置）
    x += 5;
    if (x > WINDOW_WIDTH - 40) {
      y += 40;
      x = 0;
      if (y > WINDOW_HEIGHT - 40) {
        y = 0;
      }
    }
    //更新颜色
    hue = (hue + 1) % 360;
    Color color = ColorFromHSV(hue, 0.9, 0.5);
    //重新绘制圆
    ImageClearBackground(&img, BLANK);
    for (int i = 0; i < 20; i++) {
      ImageDrawCircle(&img, x + 20, y + 20, i, color);
    }
    Texture texture = LoadTextureFromImage(img);
    //绘制帧
    BeginDrawing();
    ClearBackground(WHITE);
    DrawTexture(texture, 0, 0, WHITE);
    EndDrawing();
    UnloadTexture(texture);  //释放texture对象
  }
  UnloadImage(img);  //不再需要使用img，释放掉
  CloseWindow();
}