//
// Created by dfkdream on 23. 1. 17.
//

#include "pico/stdlib.h"
#include "../../key_matrix/KeyMatrix.h"
#include <bitset>

class TestKeyMatrixHandler : public KeyMatrixEventHandler{
private:
   std::bitset<35> values = {false, };
public:
    void onPress(int id) override {
        values[id] = true;
        print();
    }

    void onRelease(int id) override {
        values[id] = false;
        print();
    }

    void print(){
        for (int i=0; i<35; i++){
            if (i%7==0 && i!=0) printf(" ");
            printf("%c ", values[i]?'1':'0');
        }
        printf("\n");
    }
};

int main(){
    stdio_init_all();
    TestKeyMatrixHandler lh;
    KeyMatrix mat({12, 11, 10, 9, 8, 7, 6}, {22, 21, 20, 19, 18}, lh);

    while(1){
        mat.run();
        sleep_ms(10);
    }
}
