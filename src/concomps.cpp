// Copyright [2019] <Alek Frohlich, Gabriel B. Sant'Anna>
#include "concomps.h"

#include "linked_queue.h"

namespace concomps {

int findgcc(int ** E, int height, int width) {
    struct pixel { int x,y;};

    int R[height][width] = {}; 

    structures::LinkedQueue<pixel> pixelqueue;

    int rotulo = 1;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (R[i][j] == 0) {
                pixelqueue.enqueue(pixel{i,j});
                R[i][j] = rotulo;
            }
            while (!pixelqueue.empty()) {
                pixel p = pixelqueue.dequeue();

                if (p.y - 1 >= 0 && R[p.x][p.y-1] == 0 && E[p.x][p.y-1] == 1) {
                    pixelqueue.enqueue({p.x, p.y-1});
                    R[p.x][p.y-1] = rotulo;
                }
                if (p.x + 1 <= width && R[p.x+1][p.y] == 0 && E[p.x+1][p.y] == 1) {
                    pixelqueue.enqueue({p.x+1, p.y});
                    R[p.x+1][p.y] = rotulo;
                }
                if (p.y + 1 <= height && R[p.x][p.y+1] == 0 && E[p.x][p.y+1] == 1) {
                    pixelqueue.enqueue({p.x, p.y+1});
                    R[p.x][p.y+1] = rotulo;
                }
                if (p.x - 1 >= 0 && R[p.x-1][p.y] == 0 && E[p.x-1][p.y] == 1) {
                    pixelqueue.enqueue({p.x-1, p.y});
                    R[p.x-1][p.y] = rotulo;
                }
                rotulo++;
            }
        }
    }

    return rotulo;
}

}  // namespace concomps 
