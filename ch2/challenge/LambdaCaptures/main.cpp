#include <iostream>

using namespace std;

void displayUpper(const char ch)
{
    if(ch >= 'a' && ch <= 'z')
        std::cout << char((ch-32));
    else
        std::cout << ch;
}

void displayNormal(const char ch)
{
    if(ch >= 'A' && ch <= 'Z')
        std::cout << char((ch+32));
    else
        std::cout << ch;
}


int main()
{
    int resources = 1000;
    int amtToProduce = 10;

    // TODO: consume beim Aufruf reduziert resources nicht. Lambda Notation muss verändert werden.
    auto consume = [&resources]() mutable { // mutable ist durch die Referenz redondant geworden und kann entfernt werden
        resources--;
    };

    //consume();
    //std::cout << resources << std::endl;



    // TODO: produce beim Aufruf erhöht resources nicht. Lambda Notation muss verändert werden.
    auto produce = [&]() mutable { // mutable ist durch die Referenz redondant geworden und kann entfernt werden
        resources += amtToProduce;
    };

    //produce();
    //std::cout << resources << std::endl;


    // TODO: Zeigt es die richtigen resources an? Irgendwie bleibt der Wert doch bei 1000.
    // Herausfinden, was hier nicht stimmt.
    auto display = [&resources]()  {
        std::cout << "Resources left: " << resources << std::endl;
    };
    auto display_2 = []( int &resources)  {
        cout << "In display_2 Resources left: " << resources << endl;
    };

    consume();
    produce();
    display();
    display_2(resources);

    bool dispUpper = true;

    std::string text= "Hello World!\n";

    // TODO: Folgende Zeilen Code wiederholen sich sehr oft.
    // Finden Sie einen Weg die gleiche Logik beizubehalten, aber folgenden Code mit Hilfe eines Lambdas zu reduzieren.

    auto disUpperLambda = [&text] (const bool &dispUpper_var) -> void {
                                                                    if(dispUpper_var){
																    	for(int i=0 ; i<text.size() ; i++)
																    		displayUpper(text.at(i));
																    }
																    else{
																    	for(int i=0 ; i<text.size() ; i++)
																    		displayNormal(text.at(i));
																    }

    };

    disUpperLambda(true);
    disUpperLambda(false);


    return 0;
}
