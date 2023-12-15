#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>

class ScalarProduct
{
public:
    ScalarProduct(const std::vector<int> &vecA, const std::vector<int> &vecB)
        : vecA(vecA), vecB(vecB), result(0), done(false) {}

    void produce()
    {
        for (size_t i = 0; i < vecA.size(); ++i)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::unique_lock<std::mutex> lock(mutex);
            product = vecA[i] * vecB[i];
            std::cout << "Producer ";
            ready = true;
            lock.unlock();
            consumerCond.notify_one();

            lock.lock();
            producerCond.wait(lock, [this]()
                              { return !ready; });
        }

        std::unique_lock<std::mutex> lock(mutex);
        done = true;
        consumerCond.notify_one();
    }

    void consume()
    {
        while (true)
        {
            std::unique_lock<std::mutex> lock(mutex);
            consumerCond.wait(lock, [this]()
                              { return ready || done; });

            if (ready)
            {
                result += product;
                std::cout << "Consumer ";
                ready = false;
                lock.unlock();
                producerCond.notify_one();
            }

            if (done)
            {
                break;
            }
        }
    }

    int getResult() const
    {
        return result;
    }

private:
    const std::vector<int> &vecA;
    const std::vector<int> &vecB;
    int result;
    int product;
    bool done;
    bool ready = false;
    std::mutex mutex;
    std::condition_variable producerCond;
    std::condition_variable consumerCond;
};

int main()
{
    std::vector<int> vecA = {1, 2, 3, 4};
    std::vector<int> vecB = {5, 6, 7, 8};

    ScalarProduct scalarProduct(vecA, vecB);
    std::thread producerThread(&ScalarProduct::produce, &scalarProduct);
    std::thread consumerThread(&ScalarProduct::consume, &scalarProduct);

    producerThread.join();
    consumerThread.join();

    std::cout << "Scalar Product: " << scalarProduct.getResult() << std::endl;

    return 0;
}
