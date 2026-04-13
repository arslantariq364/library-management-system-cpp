#include<iostream>
using namespace std;

class Book{
public:
    static int total_books;
    string book_id,title,author;
    int copies,available;

    Book(string book_id,string title,string author,int copies){
        this->book_id=book_id;
        this->title=title;
        this->author=author;
        this->copies=copies;
        this->available=copies;
        total_books++;
    }

    virtual void display(){
        cout<<"ID:"<<book_id<<" | "<<title<<" by "<<author<<" | Available:"<<available<<"/"<<copies<<endl;
    }

    bool borrow(){
        if(available>0){available--;return true;}
        return false;
    }

    bool return_book(){
        if(available<copies){available++;return true;}
        return false;
    }

    virtual string get_type(){return "Book";}
    virtual ~Book(){}
};
int Book::total_books=0;

class EBook:public Book{
public:
    float file_size_mb;

    EBook(string book_id,string title,string author,int copies,float file_size_mb)
    :Book(book_id,title,author,copies){
        this->file_size_mb=file_size_mb;
    }

    void display() override{
        Book::display();
        cout<<"   Type:EBook | Size:"<<file_size_mb<<"MB"<<endl;
    }

    string get_type() override{return "EBook";}
};

class AudioBook:public Book{
public:
    float duration_hrs;

    AudioBook(string book_id,string title,string author,int copies,float duration_hrs)
    :Book(book_id,title,author,copies){
        this->duration_hrs=duration_hrs;
    }

    void display() override{
        Book::display();
        cout<<"   Type:AudioBook | Duration:"<<duration_hrs<<"hrs"<<endl;
    }

    string get_type() override{return "AudioBook";}
};

class Member{
public:
    static int total_members;
    string member_id,name,email;
    string borrowed_books[100];
    int borrow_count;

    Member(string member_id,string name,string email){
        this->member_id=member_id;
        this->name=name;
        this->email=email;
        this->borrow_count=0;
        total_members++;
    }

    virtual void display(){
        cout<<"ID:"<<member_id<<" | "<<name<<" | "<<email<<" | Borrowed:"<<borrow_count<<endl;
    }

    void borrow_book(Book* book){
        if(book->borrow()){
            borrowed_books[borrow_count++]=book->book_id;
            cout<<name<<" borrowed '"<<book->title<<"' successfully"<<endl;
        }else{
            cout<<"Sorry '"<<book->title<<"' is not available"<<endl;
        }
    }

    void return_book(Book* book){
        for(int i=0;i<borrow_count;i++){
            if(borrowed_books[i]==book->book_id){
                if(book->return_book()){
                    for(int j=i;j<borrow_count-1;j++)borrowed_books[j]=borrowed_books[j+1];
                    borrow_count--;
                    cout<<name<<" returned '"<<book->title<<"' successfully"<<endl;
                    return;
                }
            }
        }
        cout<<name<<" never borrowed '"<<book->title<<"'"<<endl;
    }

    virtual string get_type(){return "Member";}
    virtual ~Member(){}
};
int Member::total_members=0;

class PremiumMember:public Member{
public:
    int discount;

    PremiumMember(string member_id,string name,string email,int discount)
    :Member(member_id,name,email){
        this->discount=discount;
    }

    void display() override{
        Member::display();
        cout<<"   Type:Premium | Discount:"<<discount<<"%"<<endl;
    }

    void borrow_book(Book* book){
        cout<<"[Premium Member] ";
        Member::borrow_book(book);
    }

    string get_type() override{return "PremiumMember";}
};

class Library{
public:
    string name;
    Book* books[100];
    Member* members[100];
    int book_count,member_count;

    Library(string name){
        this->name=name;
        this->book_count=0;
        this->member_count=0;
    }

    void add_book(Book* book){
        books[book_count++]=book;
        cout<<"  Book '"<<book->title<<"' added successfully"<<endl;
    }

    void add_member(Member* member){
        members[member_count++]=member;
        cout<<"  Member '"<<member->name<<"' registered successfully"<<endl;
    }

    Book* find_book(string book_id){
        for(int i=0;i<book_count;i++)if(books[i]->book_id==book_id)return books[i];
        return nullptr;
    }

    Member* find_member(string member_id){
        for(int i=0;i<member_count;i++)if(members[i]->member_id==member_id)return members[i];
        return nullptr;
    }

    void delete_book(string book_id){
        for(int i=0;i<book_count;i++){
            if(books[i]->book_id==book_id){
                cout<<"  Book '"<<books[i]->title<<"' deleted successfully"<<endl;
                delete books[i];
                for(int j=i;j<book_count-1;j++)books[j]=books[j+1];
                book_count--;
                Book::total_books--;
                return;
            }
        }
        cout<<"  Book not found"<<endl;
    }

    void delete_member(string member_id){
        for(int i=0;i<member_count;i++){
            if(members[i]->member_id==member_id){
                cout<<"  Member '"<<members[i]->name<<"' deleted successfully"<<endl;
                delete members[i];
                for(int j=i;j<member_count-1;j++)members[j]=members[j+1];
                member_count--;
                Member::total_members--;
                return;
            }
        }
        cout<<"  Member not found"<<endl;
    }

    void borrow(string member_id,string book_id){
        Member* m=find_member(member_id);
        Book* b=find_book(book_id);
        if(!m){cout<<"  Member not found"<<endl;return;}
        if(!b){cout<<"  Book not found"<<endl;return;}
        m->borrow_book(b);
    }

    void return_book(string member_id,string book_id){
        Member* m=find_member(member_id);
        Book* b=find_book(book_id);
        if(!m){cout<<"  Member not found"<<endl;return;}
        if(!b){cout<<"  Book not found"<<endl;return;}
        m->return_book(b);
    }

    void search_book(string keyword){
        cout<<"\n  --- Search Results ---"<<endl;
        bool found=false;
        for(int i=0;i<book_count;i++){
            if(books[i]->title.find(keyword)!=string::npos||books[i]->author.find(keyword)!=string::npos){
                books[i]->display();
                found=true;
            }
        }
        if(!found)cout<<"  No book found with keyword: "<<keyword<<endl;
    }

    void show_all_books(){
        cout<<"\n  ================================"<<endl;
        cout<<"       ALL BOOKS IN LIBRARY      "<<endl;
        cout<<"  ================================"<<endl;
        if(book_count==0){cout<<"  No books available"<<endl;return;}
        for(int i=0;i<book_count;i++)books[i]->display();
    }

    void show_all_members(){
        cout<<"\n  ================================"<<endl;
        cout<<"      ALL REGISTERED MEMBERS     "<<endl;
        cout<<"  ================================"<<endl;
        if(member_count==0){cout<<"  No members registered"<<endl;return;}
        for(int i=0;i<member_count;i++)members[i]->display();
    }

    void stats(){
        int total_available=0;
        for(int i=0;i<book_count;i++)total_available+=books[i]->available;
        cout<<"\n  ================================"<<endl;
        cout<<"          LIBRARY STATS          "<<endl;
        cout<<"  ================================"<<endl;
        cout<<"  Total Books     : "<<Book::total_books<<endl;
        cout<<"  Total Members   : "<<Member::total_members<<endl;
        cout<<"  Total Available : "<<total_available<<endl;
        cout<<"  ================================"<<endl;
    }

    ~Library(){
        for(int i=0;i<book_count;i++)delete books[i];
        for(int i=0;i<member_count;i++)delete members[i];
    }
};

bool signin(){
    string password;
    int attempts=3;
    cout<<"\n  ================================"<<endl;
    cout<<"     LIBRARY MANAGEMENT SYSTEM   "<<endl;
    cout<<"  ================================"<<endl;
    cout<<"         ADMIN SIGN IN           "<<endl;
    cout<<"  ================================"<<endl;
    while(attempts>0){
        cout<<"  Enter Password: ";
        cin>>password;
        if(password=="1234"){
            cout<<"  Access Granted! Welcome Admin"<<endl;
            return true;
        }else{
            attempts--;
            if(attempts>0)cout<<"  Wrong Password! Attempts left: "<<attempts<<endl;
        }
    }
    cout<<"  Access Denied! Too many wrong attempts"<<endl;
    return false;
}

void book_menu(Library& lib){
    int choice;
    string id,title,author,keyword;
    int copies;
    float extra;
    cout<<"\n  ================================"<<endl;
    cout<<"           BOOK MENU             "<<endl;
    cout<<"  ================================"<<endl;
    cout<<"  [1] Add Normal Book"<<endl;
    cout<<"  [2] Add EBook"<<endl;
    cout<<"  [3] Add AudioBook"<<endl;
    cout<<"  [4] Delete Book"<<endl;
    cout<<"  [5] Search Book"<<endl;
    cout<<"  [6] Show All Books"<<endl;
    cout<<"  [0] Back"<<endl;
    cout<<"  ================================"<<endl;
    cout<<"  Enter Choice: ";
    cin>>choice;
    if(choice==1){
        cout<<"  Enter ID: ";cin>>id;
        cout<<"  Enter Title: ";cin>>title;
        cout<<"  Enter Author: ";cin>>author;
        cout<<"  Enter Copies: ";cin>>copies;
        lib.add_book(new Book(id,title,author,copies));
    }else if(choice==2){
        cout<<"  Enter ID: ";cin>>id;
        cout<<"  Enter Title: ";cin>>title;
        cout<<"  Enter Author: ";cin>>author;
        cout<<"  Enter Copies: ";cin>>copies;
        cout<<"  Enter File Size (MB): ";cin>>extra;
        lib.add_book(new EBook(id,title,author,copies,extra));
    }else if(choice==3){
        cout<<"  Enter ID: ";cin>>id;
        cout<<"  Enter Title: ";cin>>title;
        cout<<"  Enter Author: ";cin>>author;
        cout<<"  Enter Copies: ";cin>>copies;
        cout<<"  Enter Duration (hrs): ";cin>>extra;
        lib.add_book(new AudioBook(id,title,author,copies,extra));
    }else if(choice==4){
        cout<<"  Enter Book ID to Delete: ";cin>>id;
        lib.delete_book(id);
    }else if(choice==5){
        cout<<"  Enter keyword to search: ";cin>>keyword;
        lib.search_book(keyword);
    }else if(choice==6){
        lib.show_all_books();
    }
}

void member_menu(Library& lib){
    int choice;
    string id,name,email;
    int discount;
    cout<<"\n  ================================"<<endl;
    cout<<"          MEMBER MENU            "<<endl;
    cout<<"  ================================"<<endl;
    cout<<"  [1] Add Normal Member"<<endl;
    cout<<"  [2] Add Premium Member"<<endl;
    cout<<"  [3] Delete Member"<<endl;
    cout<<"  [4] Show All Members"<<endl;
    cout<<"  [0] Back"<<endl;
    cout<<"  ================================"<<endl;
    cout<<"  Enter Choice: ";
    cin>>choice;
    if(choice==1){
        cout<<"  Enter ID: ";cin>>id;
        cout<<"  Enter Name: ";cin>>name;
        cout<<"  Enter Email: ";cin>>email;
        lib.add_member(new Member(id,name,email));
    }else if(choice==2){
        cout<<"  Enter ID: ";cin>>id;
        cout<<"  Enter Name: ";cin>>name;
        cout<<"  Enter Email: ";cin>>email;
        cout<<"  Enter Discount (%): ";cin>>discount;
        lib.add_member(new PremiumMember(id,name,email,discount));
    }else if(choice==3){
        cout<<"  Enter Member ID to Delete: ";cin>>id;
        lib.delete_member(id);
    }else if(choice==4){
        lib.show_all_members();
    }
}

void borrow_menu(Library& lib){
    int choice;
    string mid,bid;
    cout<<"\n  ================================"<<endl;
    cout<<"         BORROW / RETURN         "<<endl;
    cout<<"  ================================"<<endl;
    cout<<"  [1] Borrow Book"<<endl;
    cout<<"  [2] Return Book"<<endl;
    cout<<"  [0] Back"<<endl;
    cout<<"  ================================"<<endl;
    cout<<"  Enter Choice: ";
    cin>>choice;
    if(choice==1){
        cout<<"  Enter Member ID: ";cin>>mid;
        cout<<"  Enter Book ID: ";cin>>bid;
        lib.borrow(mid,bid);
    }else if(choice==2){
        cout<<"  Enter Member ID: ";cin>>mid;
        cout<<"  Enter Book ID: ";cin>>bid;
        lib.return_book(mid,bid);
    }
}

void main_menu(Library& lib){
    int choice;
    while(true){
        cout<<"\n  ================================"<<endl;
        cout<<"     LIBRARY MANAGEMENT SYSTEM   "<<endl;
        cout<<"  ================================"<<endl;
        cout<<"  [1] Book Management"<<endl;
        cout<<"  [2] Member Management"<<endl;
        cout<<"  [3] Borrow / Return"<<endl;
        cout<<"  [4] Library Stats"<<endl;
        cout<<"  [0] Exit"<<endl;
        cout<<"  ================================"<<endl;
        cout<<"  Enter Choice: ";
        cin>>choice;
        if(choice==1)book_menu(lib);
        else if(choice==2)member_menu(lib);
        else if(choice==3)borrow_menu(lib);
        else if(choice==4)lib.stats();
        else if(choice==0){
            cout<<"\n  Thankyou! Exiting System..."<<endl;
            cout<<"  ================================"<<endl;
            break;
        }else{
            cout<<"  Invalid choice try again"<<endl;
        }
    }
}

int main(){
    Library lib("City Library");
    if(!signin())return 0;
    main_menu(lib);
    return 0;
}
