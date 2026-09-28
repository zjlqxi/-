#include<iostream>
#include <string>
using namespace std;
const int MAX_ISBN=1000;
const int MAX_TITLE=1000;
const int MAX_AUTHOR=1000;

struct Book {
    string isbn;
    string title;
    string author;
    float price;
    int stock;
    Book* next;

    Book() : price(0.0f), stock(0), next(nullptr) {}
    Book(const Book& a)
    : isbn(a.isbn),title(a.title),  author(a.author),price(a.price),stock(a.stock),
      next(nullptr){}
    Book(const string& a, const string& b, const string& c,
         float d, int f)
        : isbn(a), title(b), author(c), price(d), stock(f), next(nullptr) {}
    Book(const string& a, const string& b, const string& c,
         float d, int f, Book* x)
        : isbn(a), title(b), author(c), price(d), stock(f), next(x) {}
};

typedef struct { // 图书链表
    Book *head; // 头结点，不存数据
    int count; // 图书总数
} BookList;

 void InitList(BookList *L){
    L->head=new Book();
    L->count=0;
 }
 Book* FindByIsbn(BookList *L, const string& isbn){
    Book *p=L->head->next;
    while (p!=nullptr)
    {
        if(p->isbn==isbn) return p;
        p=p->next;
    }
    return nullptr;
 }
 int AddBook(BookList *L, Book b){
    if (FindByIsbn(L, b.isbn) != nullptr) return 0;  //已存在
    Book *p=L->head;
    while (p->next!=nullptr)
    {
        p=p->next;
    }
    p->next=new Book(b);
    L->count++;
    return 1;
    
 }
 
 int DeleteBook(BookList *L, const string& isbn){
    Book *p=FindByIsbn(L,isbn);
    if(p==nullptr) return 0;
    else{
        if(p->next==nullptr){
            Book* prev = L->head;
            while (prev->next != p) prev = prev->next;
            prev->next = nullptr;
            delete p;
        }
        else{
            Book* temp = p->next;
            p->isbn   = temp->isbn;
            p->title  = temp->title;
            p->author = temp->author;
            p->price  = temp->price;
            p->stock  = temp->stock;
            p->next   = temp->next;
        delete temp;
        }
        L->count--;
        return 1;
    }
 }
 void ShowAll(BookList *L){

    if (L->head->next == nullptr) {
        cout << "暂无图书！" << endl;
        return;
    }
    
    Book *p=L->head->next;
    while (p!=nullptr)
    {
        cout<<p->isbn<<" "<<p->title<<" "<<p->author<<" "<<p->price<<" "<<p->stock<<endl;
        p=p->next;
    }
 }
 void DestroyList(BookList *L){
    Book *prev=L->head;
    Book *temp=L->head->next;
    delete prev;
    while(temp!=nullptr){
        prev=temp;
        temp=temp->next;
        delete prev;
    }
    L->head=nullptr;
    L->count=0;

    
 }