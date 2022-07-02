#include "main.h"

namespace pathPlanning {
    
    bool system::update() { return (DxLib::ScreenFlip() != -1 && DxLib::ClearDrawScreen() != -1 && DxLib::ProcessMessage() != -1); }

    void  setCoord(int& x, int& y, const field_vector&field) {
        constexpr int MIN = 0;
        constexpr int xMAX = 127;
        constexpr int yMAX = 71;
        std::random_device rd;
        std::mt19937 eng(rd());
        std::uniform_int_distribution<int> x_rd(MIN, xMAX);
        std::uniform_int_distribution<int> y_rd(MIN, yMAX);
        x = x_rd(eng);
        y = y_rd(eng);
        while (( * field)[y][x] == 1) {
            x = x_rd(eng);
            y = y_rd(eng);
        }
    }

    void main() {
        //地形の二次元配列
        field_vector field = std::make_unique<std::array<field_array, 72>>();
        //1マスあたりのピクセル数
        constexpr int square_pixel = 10;
        //確率
        std::random_device rd;
        std::mt19937 eng(rd());
        std::bernoulli_distribution uid(0.2);
        //地形の初期化
        for (auto& f_array : *field)
            for (auto& f : f_array) f = uid(eng) ? 1 : 0;
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
        node_vector node = std::make_unique<std::array<node_array, 72>>();
        //各ノードのヒューリスティックコストの設定
        for (std::size_t y = 0; y < node -> size(); y++)
            for (std::size_t x = 0; x < (*node)[y].size(); x++)
                (*node)[y][x].setHCost(x - distination_x, y - distination_y);
        //アクターの位置のノードをOpenにする
        (*node)[actor_y][actor_x].setStatus(OpenE);
        //選択されたノードの座標
        int select_node_x = -1;
        int select_node_y = -1;

        //ループ
        while (system::update()) {
            //探索が終了してない場合
            if (!(select_node_x == distination_x) || !(select_node_y == distination_y)) {
                selectNode(node, select_node_x, select_node_y);
                mobilizeOpenNode(field, node, select_node_x, select_node_y);
                (*node)[select_node_y][select_node_x].setStatus(ClosedE);
            }

            //一定期間の描画
            for (int i = 0; i < 100; i++) {
                //地形の描画
                for (std::size_t y = 0; y < field -> size(); y++) {
                    for (std::size_t x = 0; x < (*field)[y].size(); x++) {
                        unsigned int cr = GetColor(0, 0, 0);
                        switch ((*field)[y][x])
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
                        DrawBox(x * square_pixel, y * square_pixel, (x + 1) * square_pixel, (y + 1) * square_pixel, cr, TRUE);
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