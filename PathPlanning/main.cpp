#include "main.h"

namespace path_planning {
    
    bool system::update() { return (DxLib::ScreenFlip() != -1 && DxLib::ClearDrawScreen() != -1 && DxLib::ProcessMessage() != -1); }

    void  setCoord(int& x, int& y, const field_array&field) {
        constexpr int min = 0;
        std::random_device rd;
        std::mt19937 eng(rd());
        std::uniform_int_distribution<int> x_rd(min, width - 1);
        std::uniform_int_distribution<int> y_rd(min, height - 1);
        x = x_rd(eng);
        y = y_rd(eng);
        while (field[y * width + x] == 1) {
            x = x_rd(eng);
            y = y_rd(eng);
        }
    }

    void main() {
        //地形の二次元配列
        field_array field = std::make_unique<field_type[]>(width * height);
        //1マスあたりのピクセル数
        constexpr int square_pixel = 10;
        //確率
        std::random_device rd;
        std::mt19937 eng(rd());
        std::bernoulli_distribution uid(0.2);
        //地形の初期化
        for (int y = 0; y < height; ++y)
            for (int x = 0; x < width; ++x) field[y * width + x] = uid(eng) ? 1 : 0;
        //アクターの座標
        int actor_x = 0;
        int actor_y = 0;
        setCoord(actor_x, actor_y, field);
        //目的地の座標
        int distination_x = 0;
        int distination_y = 0;
        setCoord(distination_x, distination_y, field);
        //アクタが目的地にいるときに目的地を変更する
        while (actor_x == distination_x && actor_y == distination_y) setCoord(distination_x, distination_y, field);
        //ノードの配列
        //node_vector node = std::make_unique<std::array<node_array, 72>>();
        std::unique_ptr<Node[]> nodes = std::make_unique<Node[]>(width * height);
        //各ノードのヒューリスティックコストの設定
        for (int y = 0; y < height; y++)
            for (int x = 0; x < width; x++)
                nodes[y*width+x].setHCost(x - distination_x, y - distination_y);
        //アクターの位置のノードをOpenにする
        nodes[actor_y*width+actor_x].setStatus(OpenE);
        //選択されたノードの座標
        int select_node_x = -1;
        int select_node_y = -1;

        //ループ
        while (system::update()) {
            //探索が終了してない場合
            if (!(select_node_x == distination_x) || !(select_node_y == distination_y)) {
                selectNode(nodes, select_node_x, select_node_y);
                mobilizeOpenNode(field, nodes, select_node_x, select_node_y);
                nodes[select_node_y * width + select_node_x].setStatus(ClosedE);
            }

            //一定期間の描画
            for (int i = 0; i < 50; i++) {
                //地形の描画
                for (int y = 0; y < height; y++) {
                    for (int x = 0; x < width; x++) {
                        unsigned int cr = GetColor(0, 0, 0);
                        switch (field[y * width + x])
                        {
                        case 1:
                            cr = GetColor(255, 255, 255);
                            break;
                        case 0:
                            cr = GetColor(0, 0, 0);
                            break;
                        default:
                            break;
                        }
                        DrawBox((int)x * square_pixel, (int)y * square_pixel, int(x + 1) * square_pixel, int(y + 1) * square_pixel, cr, TRUE);
                    }
                }
                //目的地の描画
                DrawBox(distination_x * square_pixel, distination_y * square_pixel, (distination_x + 1) * square_pixel, (distination_y + 1) * square_pixel, GetColor(255, 0, 0), TRUE);
                //選択されているノードの描画
                DrawBox(select_node_x * square_pixel, select_node_y * square_pixel, (select_node_x + 1) * square_pixel, (select_node_y + 1) * square_pixel, GetColor(0, 255, 0), TRUE);
            }
        }

    }
}