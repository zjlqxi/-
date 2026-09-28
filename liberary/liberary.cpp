#include<iostream>
#include "liberary.hpp"
#include<fstream>
using namespace std;

int main(){
    cout<<"========== 图书管理系统 =========="<<endl;
    cout<<"1. 添加图书"<<endl;
    cout<<"2. 查找图书（按ISBN）"<<endl;
    cout<<"3. 删除图书"<<endl;
    cout<<"4. 显示全部图书"<<endl;
    cout<<"5. 修改图书信息"<<endl;
    cout<<"6. 按书名模糊查找"<<endl;
    cout<<"7. 按价格排序"<<endl;
    cout<<"8. 统计信息"<<endl;
    cout<<"9. 保存到文件"<<endl;
    cout<<"0. 退出系统"<<endl;
    cout<<"==============================="<<endl;
    cout<<"请输入你的选择："<<endl;
    int choice;
    cin>>choice;
     BookList *L=new BookList();
    InitList(L);
    while(choice!=0){
        switch (choice)
        {
        case 1:
            {
                string isbn;
                string title;
                string author;
                float price;
                int stock;
                cout<<"请输入ISBN："<<endl;
                cin>>isbn;
                cout<<"请输入书名："<<endl;
                getline(cin,title);
                cout<<"请输入作者："<<endl;
                cin>>author;
                cout<<"请输入价格："<<endl;
                cin>>price;
                cout<<"请输入库存："<<endl;
                cin>>stock;
                Book b(isbn,title,author,price,stock);
                if(AddBook(L,b)){
                    cout<<"添加成功！"<<endl;
                }else{
                    cout<<"添加失败，图书已存在！"<<endl;
                }
            }
            break;
        case 2:
            {
                string isbn;
                cout<<"请输入ISBN："<<endl;
                cin>>isbn;
                Book *p=FindByIsbn(L,isbn);
                if(p!=nullptr){
                    cout<<"图书信息如下："<<endl;
                    cout<<"ISBN："<<p->isbn<<endl;
                    cout<<"书名："<<p->title<<endl;
                    cout<<"作者："<<p->author<<endl;
                    cout<<"价格："<<p->price<<endl;
                    cout<<"库存："<<p->stock<<endl;
                }else{
                    cout<<"未找到该图书！"<<endl;
                }
            }
            break;
        case 3:
            {
                string isbn;
                cout<<"请输入ISBN："<<endl;
                cin>>isbn;
                if(DeleteBook(L,isbn)){
                    cout<<"删除成功！"<<endl;
                }else{
                    cout<<"删除失败，未找到该图书！"<<endl;
                }
            }
            break;
        case 4:
            {
                cout<<"全部图书信息如下："<<endl;
                ShowAll(L);
            }
            break;
        case 5:
            {
                string isbn;
                cout<<"请输入ISBN："<<endl;
                cin>>isbn;
                Book *p=FindByIsbn(L,isbn);
                if(p!=nullptr){
                    cout<<"图书信息如下："<<endl;
                    cout<<"ISBN："<<p->isbn<<endl;
                    cout<<"书名："<<p->title<<endl;
                    cout<<"作者："<<p->author<<endl;
                    cout<<"价格："<<p->price<<endl;
                    cout<<"库存："<<p->stock<<endl;
                }else{
                    cout<<"未找到该图书！"<<endl;
                }
            }
            break;
        case 6:
            {
                string title;
                cout<<"请输入书名："<<endl;
                getline(cin,title);
                Book *p=L->head->next;
                bool found=false;
                while (p!=nullptr)
                {
                    if(p->title.find(title)!=string::npos){
                        cout<<"图书信息如下："<<endl;
                        cout<<"ISBN："<<p->isbn<<endl;
                        cout<<"书名："<<p->title<<endl;
                        cout<<"作者："<<p->author<<endl;
                        cout<<"价格："<<p->price<<endl;
                        cout<<"库存："<<p->stock<<endl;
                        found=true;
                    }
                    p=p->next;
                }
                if(!found){
                    cout<<"未找到该图书！"<<endl;
                }
            }
            break;
        case 7:
            {
                Book *p=L->head->next;
                if(p==nullptr){
                    cout<<"图书列表为空！"<<endl;
                    break;
                }
                // 冒泡排序
                for(int i=0;i<L->count-1;i++){
                    p=L->head->next;
                    for(int j=0;j<L->count-i-1;j++){
                        if(p->price>p->next->price){
                            // 交换数据
                            swap(p->isbn,p->next->isbn);
                            swap(p->title,p->next->title);
                            swap(p->author,p->next->author);
                            swap(p->price,p->next->price);
                            swap(p->stock,p->next->stock);
                        }
                        p=p->next;
                    }
                }
                cout<<"按价格排序后的图书信息如下："<<endl;
                ShowAll(L);
            }
            break;
        case 8:
            {
                cout<<"图书总数："<<L->count<<endl;
                float totalPrice=0;
                int totalStock=0;
                Book *p=L->head->next;
                while (p!=nullptr)
                {
                    totalPrice+=p->price*p->stock;
                    totalStock+=p->stock;
                    p=p->next;
                }
                cout<<"图书总库存："<<totalStock<<endl;
                cout<<"图书总价值："<<totalPrice<<endl;
            }
            break;
        case 9:
            {
                ofstream outFile("books.txt");
                Book *p=L->head->next;
                while (p!=nullptr)
                {
                    outFile<<p->isbn<<" "<<p->title<<" "<<p->author<<" "<<p->price<<" "<<p->stock<<endl;
                    p=p->next;
                }
                outFile.close();
                cout<<"保存成功！"<<endl;
            }
            break;    
        default:
            cout<<"无效的选择，请重新输入！"<<endl;
            break;
        }
        cout<<"请输入你的选择："<<endl;
        cin>>choice;
    }
    DestroyList(L);  
    delete L;         
    cout<<"退出系统"<<endl;
    return 0;
}