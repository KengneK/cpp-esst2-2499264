#include <iostream>

#include <array>
#include <cassert>

template <typename T1, unsigned int S>
class VectorND {
public:

    VectorND()
    {}

    template<class T, class... A>
    VectorND(const T x, A... args){
        fill(x, args...);
    }

    template<class T>
    VectorND(const T x){
        mData.fill(x);    
    }

    template <typename T2>
    T1 operator*(const VectorND<T2, S> &other){

        // TODO: Skalar-Produkt implementieren
        //static_assert( S == size(), "Error in Operator(*). Lenght of Vector muss be same!");
        assert( S == size());
        /*if(S != size()){
            std::cout << "Error in Operator(*). Lenght of Vector muss be same!" << std::endl;
            return 0;
        }*/

        T1 scalar_product{0};
        for(int i{0}; i<S; i++){
            //scalar_product += (mData.at(i)* other.mData.at(i));

            // avec T1& operator[](const unsigned int idx)
            scalar_product += (this->operator[](i) * other[i]);  // this->operator[](i) ruft die Version der Methode operator[] mit referenz als Rückgabe auf und other[i] die Version ohne
            //scalar_product += (mData.at(i)* other[i]); // other[i] ruft die Version der Methode operator[] OHNE referenz als Rückgabe auf
        }
        return scalar_product;
    }

    void clear(){
        for(auto &val : mData)
            val = 0;
    }

    template <typename T2>
    VectorND<T1, S> operator+(const VectorND<T2, S> &other){
        // TODO: Vektor Addition implementieren
        //static_assert(S == size(), "Error in Operator(+) Lenght of Vector muss be same!");
        assert(S == size());
        /*if(S != size()){
            std::cout << "Error in Operator(+). Lenght of Vector muss be same!" << std::endl;
            return VectorND<T1, S>();
        }*/

        VectorND<T1, S> result{};
        for(int i{0}; i<S; i++){
            //result[i]= (mData.at(i)+ other.mData.at(i)); //Mit VectorND<T1, S> result{}: result[i] ruft die Version der Methode operator[] mit Referenz als Rückgabe auf
            result[i]= (mData.at(i)+ other[i]);          // Mit VectorND<T1, S> result{}: result[i] ruft die Version der Methode operator[] mit referenz als Rückgabe auf und other[i] die Version ohne
        }

        return result;
    }

    T1 operator[](const unsigned int idx) const{
        // TODO: Code für Subscript-Operator implementieren
        std::cout << "[] version without ref\n";
        return mData.at(idx);
    }

    T1& operator[](const unsigned int idx) {
        // TODO: Code für Subscript-Operator implementieren
        //std::cout << "[] version with ref\n";
        return mData.at(idx);
    }

    unsigned int size() const
    {   return S;    }

    void print(){
        for(auto i=0 ; i<mData.size() ; i++){
            std::cout << mData[i] << "  ";
        }
        std::cout <<std::endl;
    }

private:

    // TODO: Implementierung von der fill Methode, die nur vom Konstruktor aufgerufen wird
    void fill(){
        mSizeSentinel=0;
    }

    template<class T, class... A>
    void fill(const T x, A... args){
        mData.at(mSizeSentinel) = x;
        mSizeSentinel++;
        fill(args...);
    }


    std::array<T1, S> mData;
    int mSizeSentinel = 0;
};

int main()
{
    VectorND<int, 3> x1(1,2,3);
    VectorND<int, 3> x2(1,2,3);
    std::cout << "x1 = "; x1.print();
    std::cout << "x2 = "; x2.print();
    std::cout << std::endl;
    

    VectorND<int, 5> y1(1,2,3,4,5);
    VectorND<int, 5> y2(1,2,3,4,5);
    std::cout << "y1 = "; y1.print();
    std::cout << "y2 = "; y2.print();
    std::cout << std::endl;

    auto x3 = x1+x2;
    auto y3 = y1+y2;

    std::cout << "x3 = "; 
    x3.print();
    std::cout << "y3 = ";
    y3.print();
    std::cout << std::endl;

    std::cout << "x1*x2 = ";
    std::cout << x1*x2 << std::endl;
    std::cout << "y1*y2 = ";
    std::cout << y1*y2 << std::endl;

    VectorND<int, 6> z{3};
    std::cout << "z = ";
    z.print();


    return 0;
}