#include <iostream>
#include <thread>
#include <atomic>
#include <condition_variable>
#include "CommonObject.h"
#include "DrawThread.h"
#include "DownloadThread.h"
#include "ParseThread.h"

int main(){
    CommonObjects common;
    DrawThread draw;
    DownloadThread down;
    ParseThread parse;

    std::jthread draw_th([&] { draw(common); });
    std::jthread down_th([&] { down(common); });
    std::jthread parse_th([&] { parse(common); });


    std::cout << "Running Book Manager...\n";

    down_th.join();
    parse_th.join();
    draw_th.join();
}
