#include <iostream>
#include <future>
#include <thread>
#include <chrono>

using namespace std;

int main()
{

    //std::mutex mutx{};

    auto promise = std::promise<int>();

    auto producer = std::thread([&]
    {

        for(int i=0; i<=10 ; i++)
        {  
            //std::cout << "In for\n"; 
            std::this_thread::sleep_for(chrono::milliseconds(1000));
            
            promise.set_value(i*i);
            promise = std::promise<int>(); // on prepare la prochaine promesse pour la prochaine operation
           

            // TODO: Folgender Abschnitt gehört in den Consumer-Bereich
            /*std::cout << "Incoming Result: ";
            std::cout << r;
            std::cout << std::endl;*/
        }
    });



 

    auto consumer = std::thread([&]
    {
        int r = 0;  
        while(r < 100)
        {
            // TODO: Consumer Code implementieren, bei dem promises und futures für die
            // Interthread-Kommunikation verwendet werden.

            std::future<int> fut{promise.get_future()};
            r = fut.get(); // The get member function waits (by calling wait()) until the shared state is ready: d''apres la Doku online. Donc ici le thread attend que le resultat soit diponible et donc pas besoin d'appeler la methode wait() pour attendre le resultat

            std::cout << "Incoming Result: ";
            std::cout << r;
            std::cout << std::endl;
        }
      
    });

    producer.join();
    consumer.join();
    return 0;
}
