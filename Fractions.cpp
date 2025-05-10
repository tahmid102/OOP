#include<iostream>
//#include<numeric>

using namespace std;

int gcd(int a, int b);

class Fraction{
    int  numerator;
    int denominator;
    public:
    Fraction(){
        numerator=0;
        denominator=1;
    }
    Fraction(int n){
        numerator=n;
        denominator=1;
    }
    Fraction(int n, int d){
        numerator=n;
        denominator=d;
    }
    /*~Fraction(){
        delete numerator;
        delete denominator; 
    }*/

    //addition of fractions 
    Fraction add(Fraction &f){
        Fraction s;
        s.numerator=numerator*f.denominator+f.numerator*denominator;
        s.denominator=denominator*f.denominator;
        return s;
    }
    Fraction add(int n){
        Fraction s;
        s.numerator=numerator+denominator*n;
        s.denominator=denominator;
        return s;
    }

    //substraction 
    Fraction sub(Fraction &f){
        Fraction s;
        s.numerator=numerator*f.denominator-f.numerator*denominator;
        s.denominator=denominator*f.denominator;
        return s;
    }
    Fraction sub(int n){
        Fraction s;
        s.numerator=numerator-denominator*n;
        s.denominator=denominator;
        return s;
    }

    //multiplication
    Fraction mul(Fraction &f){
        Fraction s;
        s.numerator=numerator*f.numerator;
        s.denominator=denominator*f.denominator;
        return s;
    }
    Fraction mul(int n){
        Fraction s;
        s.numerator=numerator*n;
        s.denominator=denominator;
        return s;
    }

    //division 
    Fraction div(Fraction &f){
        Fraction s;
        s.numerator=numerator*f.denominator;
        s.denominator=denominator*f.numerator;
        return s;
    }
    Fraction div(int n){
        Fraction s;
        s.numerator=numerator;
        s.denominator=denominator*n;
        return s;
    }
    void print(){
        if(denominator==0){
            cout<<"Can not divide by 0 "<<endl;
            return;
        }
        if(gcd(numerator, denominator)!=1){
            int g=gcd(numerator,denominator);
            numerator=numerator/g;
            denominator=denominator/g;
        }
        cout<<numerator<<"/"<<denominator<<endl;

    }

    int getnumerator(){
        return numerator;
    }
    int getdenominator(){
        return denominator;
    }

};


int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}



class FractionCollection{
    Fraction *fractions;
    int maxlength;
    int length;
    public:
    FractionCollection(){
        length=0;
        fractions=new Fraction[10];
    }
    FractionCollection(int n){
        length=0;
        maxlength=n;
        fractions=new Fraction[maxlength];
    }

    ~FractionCollection(){
        delete[] fractions;
    }

    void insert(Fraction f){
        if(length>=maxlength){
            return;
        }     //length soman hoye gele ar insertion hobena
        fractions[length]=f;
        length++;
    }
    void insert(int pos, Fraction f){
        if(pos>=maxlength){
            return;
        }
        Fraction temp= fractions[pos];

        for(int i=pos;i<length;i++){
            Fraction temp2=fractions[i+1];
            fractions[i+1]=temp;
            temp=temp2;
        
        }
        fractions[pos]=f;
        length++;
    }

    void remove(){
        if(length>0) length--;
    }

    void remove(Fraction f)
    {
        for(int i=0;i<length;i++)
        {
            if(fractions[i].getnumerator()==f.getnumerator() && fractions[i].getdenominator()==f.getdenominator()){
                
                for(int j=i;j<length-1;j++)
                {
                    fractions[j]=fractions[j+1];
                }
                length--;
                //i--;
            }
        }
    }

    void remove(int pos){
        if(pos>0 && pos<length){
        for(int i=pos;i<length-1;i++){
            fractions[i]=fractions[i+1];
        }
        length--;
     }
    }
    


    Fraction add(int start , int end){
        Fraction s;
        for(int i=start;i<=end;i++)
        {
            s=s.add(fractions[i]);
        }
        return s;
    }

    Fraction mul(int start, int end){
        Fraction s(1,1);
        for(int i=start;i<=end;i++){
            s=s.mul(fractions[i]);
        }

        return s;

    }

    Fraction sub(int pos1, int pos2){
        Fraction a= fractions[pos1];
        Fraction s=a.sub(fractions[pos2]);
        return s;
    }

    Fraction div(int pos1, int pos2){
        Fraction a=fractions[pos1];
        Fraction s=a.div(fractions[pos2]);
        return s;
    }

    Fraction getmax(){
        Fraction max=fractions[0];
        for(int i=0;i<length;i++){
            if(fractions[i].getnumerator()*max.getdenominator()>max.getnumerator()*fractions[i].getdenominator()){
                max= fractions[i];
            }
        }
        return max;
    }

    Fraction getmin(){
        Fraction min=fractions[0];
        for(int i=0;i<length;i++){
            if(fractions[i].getnumerator()*min.getdenominator()<min.getnumerator()*fractions[i].getdenominator()){
                min= fractions[i];
            }
        }
        return min;
    }
    void print(){
        for(int i=0;i<length;i++){
            cout<<"Fraction "<<i<<": ";
            fractions[i].print();
        }
        cout<<"Max: ";
        getmax().print();
        cout<<"Min: ";
        getmin().print();
        cout<<"Summation: ";
        add(0,length-1).print();
        cout<<"Multiplication: ";
        mul(0,length-1).print();
    }


};



int main(){ 
    //create Fraction with numerator, denominator 
    Fraction a(5,2),b(7,2),c(9,2),d(28,5); 
    cout<<"Fraction"<<endl; 
    cout<<"-------------------------------"<<endl; 
    cout<<"A: "; 
    a.print(); 
    cout<<"B: "; 
    b.print(); 
    cout<<endl; 
 
    cout<<"Add(a,b): "; 
    a.add(b).print(); 
    cout<<"Add(a,2): "; 
    a.add(2).print(); 
     
    cout<<"Sub(a,b) "; 
    a.sub(b).print(); 
    cout<<"Sub(a,2) "; 
    a.sub(2).print(); 
     
    cout<<"Mul(a,b): "; 
    a.mul(b).print(); 
    cout<<"Mul(a,2): "; 
    a.mul(2).print(); 
     
    cout<<"Div(a,b): "; 
    a.div(b).print(); 
    cout<<"Div(a,2): "; 
    a.div(2).print(); 
    cout<<"Div(a,0): "; 
    a.div(0).print(); 
 
    //Collection of Fractions 
    Fraction e,f(5),g(10); 
    FractionCollection fc(10); 
    fc.insert(a); 
    fc.insert(b); 
    fc.insert(c); 
    fc.print(); 
 
    cout<<"Sub(Pos0, Pos1): "; 
    fc.sub(0,1).print(); //subtracts the fraction at pos1 from fraction at pos0 
    cout<<"Div(Pos0, Pos1): "; 
    fc.div(0,1).print(); //divides the fraction at pos0 by the fraction at pos1 
 
    fc.remove(1);  //removed 'b' 
    fc.print();  
 
    fc.remove(a); 
    fc.print();  
 
    fc.insert(d); 
    fc.insert(0,e);  //insert at pos0 
    fc.insert(f); 
    fc.insert(g); 
    fc.print(); 
 
    fc.remove(); //removed the last fraction 
    fc.print();  //notice the output 
         
    return 0; 
} 
