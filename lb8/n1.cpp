#include <iostream>

// interface Product
enum class Article {MILK, BOOK, NUT};
class Product
{
    public:
        Article arcl;
        int cost;
        Product(Article, int); 
        Product(const Product&) = default; 
};

Product::Product(Article ar, int c)
: arcl(ar), cost(c)  
{}

//

class Market 
{
    private:
        Product prdct;
        int     amountProduct;
        int     money;
    
    public:
        Market();
        Market(Product, int, int);
        Market(const Market&) = default;
        ~Market() { prdct.~Product(); printf("\nDestructor called!\n"); };

        void sellProducts(int);
        void encashment(int);
        void addProduct(int);
        void changeProduct(Product);
        // 
        void print() const;
        // setters
        inline void setPrdct(Product p){ prdct = p; }
        inline void setCost(int c){ prdct.cost = c; }
        inline void setAmount(int am){ amountProduct = am; }
        inline void setMoney(int m){ money = m; }
        // getters
        inline Product getPrdct() const { return prdct; }
        inline int getCost() const { return prdct.cost; }
        inline int getAmount() const { return amountProduct; }
        inline int getMoney() const { return money; }
}; 

//
Market::Market() 
: prdct(Article::MILK, 15),
  amountProduct(0),
  money(0) {}

Market::Market(Product pr, int amount = 0, int cash = 0)
: prdct(pr), amountProduct(amount),
  money(cash) {}

inline void Market::sellProducts(int am)
{
    amountProduct -= am;
    money += prdct.cost * am;
}

inline void Market::encashment(int amm)
{
    money -= amm;
}

inline void Market::addProduct(int amp)
{
    amountProduct += amp;
}

inline void Market::changeProduct(Product pr)
{
    prdct = pr;
    amountProduct = 0;
}

void Market::print() const 
{
    printf("\n--- Market");
    printf("\nProduct: ");
    switch (getPrdct().arcl)
    {
    case Article::MILK:
        printf("Milk");
        break;
    
    case Article::BOOK:
        printf("Books");
        break;
        
    case Article::NUT:
        printf("Nuts");
        break;
    }
    printf("\nCost: %d",   getCost());
    printf("\nAmount: %d", getAmount());
    printf("\nMoney: %d",  getMoney());
    
}

int main()
{
    Market a = Market(Product(Article::BOOK, 300), 50, 0);
    Market m = a;
    
    printf("\n\n1) print");
    m.print();
    
    printf("\n\n2) after selling 10 products:");
    m.sellProducts(10);
    m.print();
    
    printf("\n\n3) after encashment (100):");
    m.encashment(100);
    m.print();
    
    printf("\n\n4) after add 200 products:");
    m.addProduct(200);
    m.print();
    
    printf("\n\n5) after change product to nuts:");
    m.changeProduct(Product(Article::NUT, 30));
    m.print();

    printf("\n\n5) after setters:");
    // setters
    m.setPrdct(Product(Article::MILK, 30));
    m.setCost(10);
    m.setAmount(310);
    m.setMoney(0);
    m.print();

    printf("\n");

}