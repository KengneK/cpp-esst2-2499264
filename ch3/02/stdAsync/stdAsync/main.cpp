#include <iostream>
#include <future>
#include <string>

#define with_share_future 1

struct Concurrent {
    void test1(const int i, const std::string& str)
    {
        std::cout << str << ' ' << i << std::endl;
    }
    void test2(const std::string& str)
    {
        std::cout << str << std::endl;
    }
    int operator()(const int i)
    {
        std::cout << i << std::endl;
        return i + 10;
    }
};


int main()
{
    Concurrent conc;

    // Default policy (std::launch::deferred | std::launch::async)// Syteme entscheidet selbst zwischen beiden
    auto a1 = std::async(&Concurrent::test1, &conc, 42, "Hello");

    // Lazy evaluation
    auto a2 = std::async(std::launch::deferred, &Concurrent::test2, conc, "world!");

    // Asynchronous evaluation , ein Thread für die Berabeitung der Aufgabe in a3 wird geöfnet
    auto a3 = std::async(std::launch::async, Concurrent(), 43); // on va appler la methode operator(), afficher 43 et incrementer 43 de ce qui donne 53. 
                                                                // operator() retourne 53 qui qui serra accessible via la methode get() de la std::future renvoyé par async: dans le cas present a3
                                                                // et donc lord de L'appel det get on obtiendra 53 si le contenu de a3 n'a pas été modifié entre temps
    
    if(a3.valid()) {std::cout << "after init a3 ist a3 valid!" <<std::endl;}
    else {std::cout << "after init a3 ist a3 no valid!" <<std::endl;}

    a2.wait(); // We need a2 to be launched, damit bearbeiten wir die ufgabe in a2
    
#if(with_share_future == 0)  
    std::cout << a3.get() << std::endl; // ab hier wird so lange gewartet bis die Aufgabe in a3 fertig ist.
    if(a3.valid()) {std::cout << "after a3.get() ist a3 valid!" <<std::endl;}
    else {std::cout << "after a3.get() ist a3 no valid!" <<std::endl;}
    
    std::cout << a3.get() << std::endl; // ne fonctionne pas, car la lord du tou premier appel de la methode get(), la valeur stockée  dans la future a3 est retourné par st::move et du coup n'est plus accessible. 
                                        // la valeur est retournée par reference si on a un  std::shared_future, et ainsi on peut appeler get plusieur fosi de suite. VOIR l'exemple ci dessous avec shared_future
    if(a3.valid()) {std::cout << "after second a3.get() ist a3 valid!" <<std::endl;}
    else {std::cout << "after second a3.get() ist a3 no valid!" <<std::endl;}

#elif(with_share_future == 1)

    std::shared_future<int> shared_a3 {a3.share()}; // dans la doku au lien : https://en.cppreference.com/w/cpp/thread/shared_future/shared_future, on utilise le contructeur 3. et pour ce con
                                                    // la on parle de transferer une st::future a une std::shared_future et pour transferer un std::future on utilise la methode share() https://en.cppreference.com/w/cpp/thread/future/share.
                                                    // cette methode tranfert un st::future a un std::shared_future et apres ce transfert la st::future passe a un etat invalid

    if(a3.valid()) {std::cout << "after a3.share() to share_future ist a3 valid!" <<std::endl;}
    else {std::cout << "after a3.share() to share_future ist a3 no valid!" <<std::endl;}
    
    std::cout << shared_a3.get() << std::endl;
    std::cout << shared_a3.get() << std::endl;

    int val {shared_a3.get() };
    std::cout << "val = " << val <<std::endl;

    int val2 {shared_a3.get() };
    std::cout << "val2 = " << val2 <<std::endl;
#endif
    // Destructor of a1 will force thread of a1 to be launched at latest here.
}
