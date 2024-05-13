#include <iostream>
#include <string>
#include <vector>
#include <exception>

#define inherited_execption 0 // 0 -> MyExceptionVector herbt NICHT von der Klasse std::execption
                              // 1 -> MyExceptionVector herbt von der Klasse std::execption

class MyExceptionVector 
#if(inherited_execption == 0)
{
#elif(inherited_execption == 1)
: public std::exception{
#endif

public:
    MyExceptionVector(const char* text, std::size_t size_v, int bad_index) : m_text{text}, m_size{size_v}, m_index{bad_index} {}
#if(inherited_execption == 0)
    const char* what() const throw(){
#elif(inherited_execption == 1)
    virtual const char* what() const throw(){
#endif
    //virtual const char* what() const throw(){
        std::string message {m_text};
        message += "\nSize = " + std::to_string(m_size) + " and out of range index = " + std::to_string(m_index);
        return message.data();
    }

private:
    const char* m_text;
    const std::size_t m_size;
    const int m_index;

};

int main(){
    std::vector<std::string> data;

    try{
        data.push_back("Test");
        data.push_back("Test2");

        if(data.size() < 10){
             //avec cette version pas besoin de const char* dans le declaration du constructeur. Juste char* suffit
            /*char text[] = "Sorry, your array is too short.";
            throw MyExceptionVector{text, data.size(), 10};
            */ 
            
            throw MyExceptionVector{"Sorry, your array is too short.", data.size(), 10};
        }

        std::cout << data.at(10) << std::endl;
        data.push_back("Test3");
        data.push_back("Test5");

    }
    catch(const char *str){
        std::cout << str << std::endl;
        data.push_back("Test after exception thrown with str");
    }
    catch(const MyExceptionVector &e){
        std::cout << e.what() << std::endl;

        data.push_back("Test after MyExceptionVector classe (no exeption classe) thrown");
    }
    catch(const std::exception &e){
        std::cout << e.what() << std::endl;

        data.push_back("Test after exception thrown");
    }
    catch(...){
        std::cout << "Unknown Exception caught!" << std::endl;
    }

    for(const auto &text : data){
        std::cout << text << std::endl;
    }

    return 0;
}
