#include <thread>
#include <atomic>
#include <iostream>

/*
ce code est presque idenique a celui a D:\github_repositories\cpp-esst2-2499264\ch3\04\ThreadMutex\main.cpp
la difference est que ici on n'utilise pas de mutex pour bloquer un thread, mais une variable atomic

* aveec mutex, on bloque le thread jusqu'a ce que le traitement dans le thrad soit terminé
  Le resultat du code a D:\github_repositories\cpp-esst2-2499264\ch3\04\ThreadMutex\main.cpp est:
  1. Lock.
  1. My turn!      
  1. Still my turn!
  1. Release       
  2. Lock
  2. My turn!      
  2. Still my turn!
  2. Release       
 c = 2000000 

* avec atomic, on bloque la variable et ainsi un seul thread a la fois aura acces a la variable et des que le thread aura finit(FETCH, DECODE, EXECUTE, donc la valeur de l'execution a été ecrite dans la variable)
  un autre thread aura acces a la variable meme si la fonction du thread precedent n'a pas été executée au complet.
  Atomar Variablem können nict von 2 CPUs gleichzeitig manipuliert werden
  un Resultat possible du code ci-dessous peut etre:
  1. Lock.
  1. My turn!
  2. Lock
  2. My turn!
  1. Still my turn!
  1. Release
  2. Still my turn!
  2. Release
  c = 2000000



*/

int main()
{
    {
        std::atomic<int> c = {0};

        std::thread t1([&] {
            std::cout << "1. Lock." << std::endl;


            std::cout << "1. My turn!" << std::endl;

            for(int i=0 ; i<20 ; i++)
                c++;
                //{c++; std::cout<< "th1 c = " << c << std::endl;}

            std::cout << "1. Still my turn!" << std::endl;

            std::cout << "1. Release" << std::endl;
        });
        std::thread t2([&] {
            std::cout << "2. Lock" << std::endl;

            std::cout << "2. My turn!" << std::endl;
            for(int i=0 ; i<20 ; i++)
                c++;
                //{c++; std::cout<< "th2 c = " << c << std::endl;}

            std::cout << "2. Still my turn!" << std::endl;

            std::cout << "2. Release" << std::endl;
        });

        t1.join();
        t2.join();

        std::cout << "c = " << c << std::endl;
    }

    return 0;
}
