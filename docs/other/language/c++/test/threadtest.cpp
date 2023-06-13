#include <thread>
#include <iostream>
#include <condition_variable>
#include  <mutex>

static const int SIZE = 10;
static const int ITEM_SIZE = 30;

std::mutex mtx;

std::condition_variable not_full;
std::condition_variable not_empty;

int items[SIZE];

static std::size_t r_idx = 0;
static std::size_t w_idx = 0;

void produce(int i) {
    std::unique_lock<std::mutex> lck(mtx);
    while((w_idx+ 1) % SIZE == r_idx) {
        std::cout << "队列满了" << std::endl;
        not_full.wait(lck);
    }
    items[w_idx] = i;
    w_idx = (w_idx+ 1) % SIZE;
    not_empty.notify_all();
    lck.unlock();
}

int consume() {
    int data;
    std::unique_lock<std::mutex> lck(mtx);
    while(w_idx == r_idx) {
        std::cout << "队列为空" << std::endl;
        not_empty.wait(lck);
    }
    data = items[r_idx];
    r_idx = (r_idx + 1) % SIZE;
    not_full.notify_all();
    lck.unlock();
    return data;
}

void p_t() {
    for(int i = 0; i < ITEM_SIZE; i++) {
        produce(i);
    }
}

void c_t() {
    static int cnt = 0;
    while(1) {
        int item = consume();
        std::cout << "消费第" << item << "个商品" << std::endl;
        if(++cnt == ITEM_SIZE) {
            break;
        }
    }
}

int main() {
    std::thread producer(p_t);
    std::thread consumer(c_t);
    producer.join();
    consumer.join();
}