#include <iostream>
#include <string>
#include <vector>
#include <exception>

class MyExceptionVector : public std::exception{

public:
    MyExceptionVector(char* text, std::size_t size_v, int bad_index) : m_text{text}, m_size{size_v}, m_index{bad_index} {}
    virtual const char* what() const throw(){
        std::string message {m_text};
        message += "\nSize = " + std::to_string(m_size) + " and out of range index = " + std::to_string(m_index);
        return message.data();
    }

private:
    char* m_text;
    std::size_t m_size;
    int m_index;

};

int main()
{
    std::vector<std::string> data;

    try
    {
        data.push_back("Test");
        data.push_back("Test2");

        if(data.size() < 10)
        {
        	// TODO: Folgenden throw in eine eigene Fehlerklasse integrieren, damit über what() die Ursache abgefragt werden kann.
        	// Dieses what() soll dann im Block zu catch(const std::exception &e) aufgerufen werden.
        	// Erweitere auch die Fehlermeldung so, dass die Größe des Vectors und welcher Wert vom Entwickler:in kam, 
        	// mit in der Exception auftauchen.

            char* text = "Sorry, your array is too short.";
            throw MyExceptionVector{text, data.size(), 10};
            
            //hrow MyExceptionVector{"Sorry, your array is too short.", data.size(), 10};
        }

        std::cout << data.at(10) << std::endl;

        data.push_back("Test3");

        data.push_back("Test5");

    }
    catch(const char *str)
    {
        std::cout << str << std::endl;
        data.push_back("Test after exception thrown with str");
    }
    catch(const std::exception &e)
    {
        std::cout << e.what() << std::endl;

        data.push_back("Test after exception thrown");
    }
    catch(...)
    {
        std::cout << "Unknown Exception caught!" << std::endl;
    }

    for(const auto &text : data)
    {
        std::cout << text << std::endl;
    }

    return 0;
}
