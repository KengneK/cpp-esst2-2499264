#include <thread>
#include <mutex>
#include <iostream>

int main()
{
    // Race condition
    {
        std::mutex mutex;

        int c=0;

        std::thread t1([&] {
            //mutex.lock();
            std::cout << "1. Lock." << std::endl;


            std::cout << "1. My turn!" << std::endl;

            for(int i=0 ; i<1000000 ; i++)
            {
                c++;
            }

            std::cout << "1. Still my turn!" << std::endl;

            std::cout << "1. Release" << std::endl;
            //mutex.unlock();
        });
        std::thread t2([&] {
            //mutex.lock();
            std::cout << "2. Lock" << std::endl;

            std::cout << "2. My turn!" << std::endl;
            for(int i=0 ; i<1000000 ; i++)
            {
                c++;
            }
            std::cout << "2. Still my turn!" << std::endl;

            std::cout << "2. Release" << std::endl;
            //mutex.unlock();
        });



        t1.join();
        t2.join();

        std::cout << "c = " << c << std::endl;
    }

   // return 0;

    // Deadlock : Programm endet nie, weil die beide Threads sich gegenseitig blokieren
    {
    std::mutex m1, m2;

    std::thread t1([&] {
        std::cout << "1. Acquiring m1." << std::endl;
        m1.lock();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        std::cout << "1. Acquiring m2" << std::endl;
        m2.lock();
    });
    std::thread t2([&] {
        std::cout << "2. Acquiring m2" << std::endl;
        m2.lock();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        std::cout << "2. Acquiring m1" << std::endl;
        m1.lock();
    });

    t1.join();
    t2.join();
    }

    std::cout << "Ende" <<std::endl;

    return 0;
}
