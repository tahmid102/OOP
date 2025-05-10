#include<iostream>
using namespace std;

class Product{
    string productName;
    string productID;
    double price ;
    int stockChanges[100];
    int numStockChanges;
    public:
    Product(){
        productName="";
        productID="";
        price=0;
        numStockChanges=0;
        for(int i=0;i<100;i++){
            stockChanges[i]=0;
        }
    }
    Product(string productName, string productID, double price)
    {
        this->productName=productName;
        this->productID=productID;
        this->price=price;
        numStockChanges=0;
        for(int i=0;i<100;i++){
            stockChanges[i]=0;
        }
    }
    void addStock(int amount){
        stockChanges[numStockChanges]=amount;
        numStockChanges++;
    }
    void reduceStock(int amount){
        int stock=0;
        for(int i=0;i<numStockChanges;i++){
            stock+=stockChanges[i];
        }
        if(stock<amount) return ;
        
        stockChanges[numStockChanges]=-amount;
        numStockChanges++;
    }
    int getCurrentStock(){
        int stock=0;
        for(int i=0;i<numStockChanges;i++){
            stock+=stockChanges[i];
        }
        if(stock<0)return 0;
        return stock;
    }
    string getpid(){
        return productID;
    }
    void display(){
        cout<<productName<<" "<<productID<<" "<<price<<endl;
    }
};


class Inventory{
    Product* products;
    int numProducts;
    int maxProducts;
    public:
    Inventory(){
        products=NULL;
        numProducts=0;
        maxProducts=0;
    }
    Inventory(int maxProducts)
    {
        products= new Product[maxProducts];
    }
    Inventory(Product* products, int numProducts, int maxProducts){
        this->products= new Product[maxProducts];
        this->numProducts=numProducts;
        this->maxProducts=maxProducts;
        for(int i=0;i<numProducts;i++){
            this->products[i]=products[i];
        }
    }
    Inventory(const Inventory&a){
        numProducts=a.numProducts;
        maxProducts=a.maxProducts;
        products= new Product[maxProducts];
        for(int i=0;i<maxProducts;i++){
            products[i]=a.products[i];
        }
    }
    ~Inventory(){
        delete [] products;
    }
        
    void addProduct(Product p){
        if(numProducts+1>maxProducts){
        Product * newproducts= new Product[maxProducts+1];
        int i;
        for( i=0;i<maxProducts;i++){
            newproducts[i]=products[i];
        }
        newproducts[i]=p;
        delete[] products;
        products=newproducts;
        numProducts++;
        maxProducts++;
        }
        else{
            products[numProducts]=p;
            numProducts++;
            maxProducts++;
        }
    }

    void updateProductStock(string productID, int amount){
        int idx=-1;
        for(int i=0;i<numProducts;i++){
            if(products[i].getpid()==productID){
                idx=i;
                break;
            }
        }
        if(idx==-1)return;
        products[idx].addStock(amount);
    }
    void listAllProducts(){
        for(int i=0;i<numProducts;i++){
            products[i].display();
        }
    }
    Product getMostStockedProduct(){
        int max=products[0].getCurrentStock();
        int idx=0;
        for(int i=1;i<numProducts;i++){
            if(max<products[i].getCurrentStock()){
                max=products[i].getCurrentStock();
                idx=i;
            }
        }
        return products[idx];
    }




};



int main()
{
    Inventory inv1(5);
Product p1("Laptop", "P001", 50000);
Product p2("Smartphone", "P002", 30000);
Product p3("Tablet", "P003", 25000);
Product p4("Smartwatch", "P004", 4000);
Product p5("Headphones", "P005", 2000);
Product p6("Charger", "P006", 1000);
inv1.addProduct(p1);
inv1.addProduct(p2);
inv1.addProduct(p3);
inv1.addProduct(p4);
inv1.addProduct(p5);
inv1.addProduct(p6);
inv1.updateProductStock("P001", 50);
inv1.updateProductStock("P001", -10);
inv1.updateProductStock("P003", 70);
inv1.updateProductStock("P002", 70);
inv1.updateProductStock("P002", -5);
inv1.updateProductStock("P003", -10);
cout << "\nProducts in Inventory 1:\n";
inv1.listAllProducts();
cout << "\nMost Stocked Product in Inventory 1:\n";
inv1.getMostStockedProduct().display();
Inventory inv2 = inv1;
inv2.updateProductStock("P003", 10);
inv2.updateProductStock("P002", 10);
inv2.updateProductStock("P002", -5);
cout << "\nProducts in Inventory 2:\n";
inv2.listAllProducts();
cout << "\nMost Stocked Product in Inventory 1:\n";
inv1.getMostStockedProduct().display();
cout << "\nMost Stocked Product in Inventory 2:\n";
inv2.getMostStockedProduct().display();
}