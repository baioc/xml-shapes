// Copyright [2019] <Alek Frohlich, Gabriel B. Sant'Anna>
#include "concomps.h"

#include "linked_queue.h"

//danger zone
#include <iostream>

namespace concomps {

struct pixel {
    int x,y;
};

int count_shapes(int ** E, int height, int width) {

    int R[height][width] = {}; 

    structures::LinkedQueue<pixel> pixelqueue;

    int assigned_label = 0;
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int label = 1;
            if (R[i][j] == 0 && E[i][j] == 1) {
                pixelqueue.enqueue(pixel{i,j});
                R[i][j] = label;
            }
            while (!pixelqueue.empty()) {
                auto p = pixelqueue.dequeue();

                if (p.y - 1 >= 0 && R[p.x][p.y-1] == 0 && E[p.x][p.y-1] == 1) {
                    pixelqueue.enqueue(pixel{p.x, p.y-1});
                    R[p.x][p.y-1] = label;
                }
                if (p.x + 1 < width && R[p.x+1][p.y] == 0 && E[p.x+1][p.y] == 1) {
                    pixelqueue.enqueue(pixel{p.x+1, p.y});
                    R[p.x+1][p.y] = label;
                }
                if (p.y + 1 < height && R[p.x][p.y+1] == 0 && E[p.x][p.y+1] == 1) {
                    pixelqueue.enqueue(pixel{p.x, p.y+1});
                    R[p.x][p.y+1] = label;
                }
                if (p.x - 1 >= 0 && R[p.x-1][p.y] == 0 && E[p.x-1][p.y] == 1) {
                    pixelqueue.enqueue(pixel{p.x-1, p.y});
                    R[p.x-1][p.y] = label;
                }
                label++;
            }
            if (label > assigned_label)
                assigned_label = label;
        }
    }

    return assigned_label;
}

}  // namespace concomps 
