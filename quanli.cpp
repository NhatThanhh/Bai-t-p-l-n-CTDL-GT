#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <windows.h>
#include <conio.h>
#include <sstream>
#include <cctype>
#include <ctime>

using namespace std;

struct user{
    string username;
    string password;
};
void SET_COLOR(int color){
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}
bool checkAccount(user account){ // Kiểm tra tài khoản đăng nhập
    fstream fs;
    fs.open("user.txt", ios::in);
    if (!fs.is_open()){
        cout << "Khong the mo file !";
    }else{
        string line;
        while (getline(fs, line)){
            user a;
            stringstream ss(line);
            getline(ss, a.username, ',');
            getline(ss, a.password, ',');

            if (account.username == a.username && account.password == a.password){
                return true;
                fs.close();
            }
        }
    }
    fs.close();
    return false;
}
void login() {
    while (true) {
        SET_COLOR(6);
        cout << setw(53) << " " << "----DANG NHAP----" << endl;
        SET_COLOR(7);
        user a;
        cout << setw(53) << " " << "Username: ";
        getline(cin, a.username);
        cout << setw(53) << " " << "Password: ";
        char ch;
        string password = "";
        while ((ch = _getch()) != 13) {
            if (ch == 8) {
                if (!password.empty()) {
                    cout << "\b \b";
                    password.pop_back();
                }
            } else {
                password.push_back(ch);
                cout << "*";
            }
        }
        a.password = password;
        cout << endl;
        if (checkAccount(a)) {
            cout << setw(54) << " " << "Dang Nhap Thanh Cong !" << endl;
            break;
        } else {
            SET_COLOR(3);
            cout << setw(44) << " " << "Ten Dang Nhap Hoac Mat Khau Khong Dung !" << endl << endl;
            SET_COLOR(7);
        }
    }
}

struct Product{
    string name;
    int price1, price2, price3;
};
struct Node{
    Product data;
    Node *next;
};
struct List{
    Node *head;
    Node *tail;
};
void init(List *l){
    l->head = l->tail = NULL;
}
Node *CreateNode(Product x){
    Node *p = new Node;
    p->data = x;
    p->next = NULL;
    return p;
}
void AddLast(List *l, Node *p){
    if (l->head == NULL){
        l->head = l->tail = p;
    }else{
        l->tail->next = p;
        l->tail = p;
    }
}

bool CheckKiTu(const string &s){
    for (char c : s){
        if (!isdigit(c)){
            return false;
        }
    }
    return true;
}

void Quit(){
    cout << endl;
    cout << "Nhan phim bat ki de tiep tuc...";
    _getch();
    system("cls");
}

void ReadFile(List *l){ // đọc file
    init(l);
    fstream fs;
    fs.open("sanpham.txt", ios::in);
    if (!fs.is_open()){
        cout << "Khong the mo file !" << endl;
    }
    string line;
    while (getline(fs, line)){
        Product a;
        stringstream ss(line);
        string s;
        getline(ss, a.name, ',');
        getline(ss, s, ',');
        a.price1 = stoi(s);
        getline(ss, s, ',');
        a.price2 = stoi(s);
        getline(ss, s, ',');
        a.price3 = stoi(s);
        Node *p = CreateNode(a);
        AddLast(l, p);
    }
    fs.close();
}



void WriteFile(List *l){ // ghi cuối file
    fstream fs;
    fs.open("sanpham.txt", ios::out);
    if (!fs.is_open()){
        cout << "Khong the mo file !" << endl;
    }
    Node *p = new Node;
    p = l->head;
    while (p != NULL){
        fs << p->data.name << "," << p->data.price1 << "," << p->data.price2 << "," << p->data.price3 << endl;
        p = p->next;
    }
    fs.close();
}
void Outputlist(List *l){
    SET_COLOR(6);
    cout << setw(35) << " " << "STT"<< "\t"<< "Ten Nuoc Uong"<< "\t\t\t     "<< " Size / Gia" << endl;
    cout << setw(35) << " " << "\t\t\t\t\t  S"<< "\t"<< "  M"<< "\t"<< "  L" << endl;
    SET_COLOR(7);
    cout << setw(35) << " " <<"----------------------------------------------------------" <<endl;
    int stt = 0;
    for(Node* p = l->head; p!= NULL; p = p->next){
        cout << setw(35) << " " << stt + 1 << "\t";
        stt++;
        Product a = p->data;
        cout << setw(25) << left << a.name << "\t";
        if (a.price1 == 0){
            cout << ""<< "\t";
        }else{
            cout << left << a.price1 << "\t";
        }
        if (a.price2 == 0){
            cout << ""<< "\t";
        }else{
            cout << left << a.price2 << "\t";
        }
        if (a.price3 == 0){
            cout << "" << "\t";
        }else{
            cout << left << a.price3 << "\t";
        }

        cout << endl;
    }
}

void AddProduct(List *l){
    if(l->head == NULL){
        cout << "Danh sach rong, khong the thuc hien chuc nang !" << endl;
        return;
    }
    string _n;
    int n;
    cout << "Nhap so luong san pham muon them: ";
    cin >> _n;
    while(!CheckKiTu(_n)){
        cout<<"So luong khong hop le. Vui long nhap lai: ";
        cin >> _n;
    }
    n = stoi(_n);
    while (n <= 0){
        cout << "So luong khong hop le, vui long nhap lai (so luong phai lon hon 0): ";
        cin >> n;
    }
    for (int i = 0; i < n; i++){
        Product a;
        cin.ignore();
        SET_COLOR(6);
        cout << "San pham thu: " << i + 1 << endl;
        SET_COLOR(7);
        cout << "Ten san pham: ";
        getline(cin, a.name);
        if (!a.name.empty()){
            a.name[0] = toupper(a.name[0]);
        }
        cout << "Gia san pham: " << endl;
        cout << "\t \tS: ";
        cin >> a.price1;
        while (a.price1 < 0){
            cout << "Gia khong hop le, vui long nhap lai: ";
            cout << "\t S: ";
            cin >> a.price1;
        }
        cout << "\t \tM: ";
        cin >> a.price2;
        while (a.price2 < 0){
            cout << "Gia khong hop le, vui long nhap lai: ";
            cout << "\t M: ";
            cin >> a.price2;
        }
        cout << "\t \tL: ";
        cin >> a.price3;
        while (a.price3 < 0){
            cout << "Gia khong hop le, vui long nhap lai: ";
            cout << "\t L: ";
            cin >> a.price3;
        }
        Node *p = new Node;
        p = CreateNode(a);
        AddLast(l, p);
    }
        SET_COLOR(3);
        cout << "***Da them " << n << " san pham vao danh sach***";
        SET_COLOR(7);
        WriteFile(l);
}
void RemoveHead(List *l){
    Node *p = l->head;
    l->head = p->next;
    delete p;
    WriteFile(l);
}
void RemoveTail(List *l){
    if (l->head == NULL){
        return; // Danh sách rỗng
    }
    Node *p = l->head;
    Node *q = NULL;
    while (p != l->tail){
        q = p;
        p = p->next;
    }
    l->tail = q;
    l->tail->next = NULL;
    delete p;
    WriteFile(l);
}
void Remove(List *l, int k){
    if (l->head == NULL){
        return; // Danh sách rỗng
    }
    Node *q = l->head;
    for (int i = 1; i < k - 1 && q->next != NULL; i++){
        q = q->next;
    }
    q->next = q->next->next;
    WriteFile(l);
}

void RemoveProduct(List *l){        //Xoá sản phẩm
    if (l->head == NULL){
        cout << "Danh sach rong, khong the thuc hien chuc nang !" << endl;
        return;
    }
    string name;
    cout << "Nhap ten san pham muon xoa: ";
    cin.ignore();
    bool found = false;
    do{
        getline(cin, name);
        if (!name.empty()){
            name[0] = toupper(name[0]);
        }
        for (Node *p = l->head; p != NULL; p = p->next){
            if (p->data.name.compare(name) == 0){
                found = true;
                break;
            }
        }
        if (!found){
            cout << "San pham khong ton tai. Vui long nhap lai: ";
        }
    } while(!found);
    for (Node *p = l->head; p != NULL; p = p->next){
        if (p->data.name.compare(name) == 0){
            if (p == l->head){
                RemoveHead(l);
                p = l->head;
            }
            else if (p == l->tail){
                RemoveTail(l);
            }
            else{
                int k = 1;
                for(Node* temp = l->head; temp!=p; temp=temp->next){
                    k++;
                }
                Remove(l, k);
                //p = l->head;
            }
        }
    }
    cout << endl;
    SET_COLOR(3);
    cout << "---Da xoa " << name << " khoi danh sach!---";
    SET_COLOR(7);
}
void UpdatePrice(List *l) {
    if (l->head == NULL) {
        cout << "Danh sach rong, khong the thuc hien chuc nang !" << endl;
        return;
    }
    string name;
    cin.ignore();
    cout << "Nhap ten san pham muon cap nhat gia: ";
    Node *p = l->head;
    bool found = false;
    do {
        getline(cin, name);
        if (!name.empty()) {
            name[0] = toupper(name[0]);
        }
        for (Node *p = l->head; p != NULL; p = p->next) {
            if (p->data.name.compare(name) == 0) {
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "San pham khong ton tai. Vui long nhap lai: ";
        }
    } while (!found);
    string _newPrice1, _newPrice2, _newPrice3;
    int newPrice1, newPrice2, newPrice3;
    cout << "Nhap gia moi cho san pham " << name << ": " << endl;
    cout << "\t\tS: ";
    cin >> _newPrice1;
    while (!CheckKiTu(_newPrice1)) {
        cout << "Gia khong hop le. Vui long nhap lai: ";
        cin >> _newPrice1;
    }
    newPrice1 = stoi(_newPrice1);
    cout << "\t\tM: ";
    cin >> _newPrice2;
    while (!CheckKiTu(_newPrice2)) {
        cout << "Gia khong hop le. Vui long nhap lai: ";
        cin >> _newPrice2;
    }
    newPrice2 = stoi(_newPrice2);
    cout << "\t\tL: ";
    cin >> _newPrice3;
    while (!CheckKiTu(_newPrice3)) {
        cout << "Gia khong hop le. Vui long nhap lai: ";
        cin >> _newPrice3;
    }
    newPrice3 = stoi(_newPrice3);
    for (p = l->head; p != NULL; p = p->next) {
        if (p->data.name.compare(name) == 0) {
            p->data.price1 = newPrice1;
            p->data.price2 = newPrice2;
            p->data.price3 = newPrice3;
            SET_COLOR(3);
            cout << "---Cap nhat gia san pham " << name << " thanh cong!---" << endl;
            SET_COLOR(7);
            break;
        }
    }
    WriteFile(l);
}

void Ascending(List *l){ // sắp xếp tăng dần
    for (Node *i = l->head; i != NULL; i = i->next){
        for (Node *j = i->next; j != NULL; j = j->next){
            if (i->data.price2 > j->data.price2){
                swap(i->data, j->data);
            }
        }
    }
}
void Descending(List *l){ // sắp xếp giảm dần
    for (Node *i = l->head; i != NULL; i = i->next){
        for (Node *j = i->next; j != NULL; j = j->next){
            if (i->data.price2 < j->data.price2){
                swap(i->data, j->data);
            }
        }
    }
}
void Sort(List *l){
    if (l->head == NULL){
        cout << "Danh sach rong, khong the thuc hien chuc nang !" << endl;
        return;
    }
    int lchon;
    SET_COLOR(6);
    cout << "------SAP XEP------" << endl;
    SET_COLOR(7);
    cout << "1. Gia thap --> cao." << endl;
    cout << "2. Gia cao --> thap." << endl;
    cout << "3. Thoat." << endl;
    SET_COLOR(3);
    cout << "Nhap lua chon cua ban: ";
    SET_COLOR(7);
    do{
        cin >> lchon;
        switch (lchon){
        case 1:
            system("cls");
            Ascending(l);
            Outputlist(l);
            cout<<endl;
            SET_COLOR(6);
            cout << "------SAP XEP------" << endl;
            SET_COLOR(7);
            cout << "1. Gia thap --> cao." << endl;
            cout << "2. Gia cao --> thap." << endl;
            cout << "3. Thoat." << endl;
            SET_COLOR(3);
            cout << "Nhap lua chon cua ban: ";
            SET_COLOR(7);
            break;
        case 2:
            system("cls");
            Descending(l);
            Outputlist(l);
            cout<<endl;
            SET_COLOR(6);
            cout << "------SAP XEP------" << endl;
            SET_COLOR(7);
            cout << "1. Gia thap --> cao." << endl;
            cout << "2. Gia cao --> thap." << endl;
            cout << "3. Thoat." << endl;
            SET_COLOR(3);
            cout << "Nhap lua chon cua ban: ";
            SET_COLOR(7);
            break;
        case 3:
            system("cls");
            break;
        default:
            SET_COLOR(3);
            cout<<"Lua chon khong hop le. Vui long nhap lai: ";
            SET_COLOR(7);
            }
        }while(lchon!=3);
}
void SearchName(List *l){
    if (l->head == NULL){
        cout << "Danh sach rong, khong the thuc hien chuc nang !" << endl;
        return;
    }
    string name;
    cout << "Nhap ten san pham muon tim: ";
    bool found = false;
    cin.ignore();
    do {
        getline(cin, name);
//        if (!name.empty()) {
//            name[0] = toupper(name[0]);
//        }
        for (Node* i = l->head; i != NULL; i = i->next) {
            if (strstr(i->data.name.c_str(), name.c_str()) != NULL) {
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Khong co " << name << " trong danh sach! Vui long nhap lai: ";
        }
    } while (!found);
    int Count = 0;
    SET_COLOR(6);
    cout << setw(35) << " " << "STT"<< "\t"<< "Ten Nuoc Uong"<< "\t\t\t     "<< " Size / Gia" << endl;
    cout << setw(35) << " " << "\t\t\t\t\t  S"<< "\t"<< "  M"<< "\t"<< "  L" << endl;
    SET_COLOR(7);
    cout << setfill('-');
    cout << "\t\t\t\t   " << setw(58) << "-" << endl;
    cout << setfill(' ');
    for (Node *i = l->head; i != NULL; i = i->next){
        if (strstr(i->data.name.c_str(), name.c_str()) != NULL){
            Count++;
            cout << setw(35) << " " << Count << "\t";
            cout << setw(25) << left  << i->data.name << "\t";
            if (i->data.price1 == 0)
            {
                cout << ""<< "\t";
            }else{
                cout << left << i->data.price1 << "\t";
            }
            if (i->data.price2 == 0){
                cout << ""<< "\t";
            }else{
                cout << left << i->data.price2 << "\t";
            }
            if (i->data.price3 == 0){
                cout << ""<< "\t";
            }else{
                cout << left << i->data.price3 << "\t";
            }

            cout << endl;
        }
    }
}

void SearchPrice(List *l){
    if (l->head == NULL){
        cout << "Danh sach rong, khong the thuc hien chuc nang !" << endl;
        return;
    }
    int Count = 0;
    string cost;
    float price;
    cout << "Nhap gia san pham ban muon tim: ";
    do{
        cin >> cost;
        for (char c : cost){
            if (!isdigit(c)){
                cout << "Gia khong hop le! Vui long nhap lai: ";
                break;
            }else{
                price = stof(cost);
                for (Node *i = l->head; i != NULL; i = i->next) {
                    if (price == i->data.price1 || price == i->data.price2 || price == i->data.price3){
                        Count++;
                    }
                }
                if (Count == 0){
                    cout << "Khong co san pham pham nao co gia " << price << "!"
                         << " Vui long nhap lai gia: ";
                    break;
                }else{
                    break;
                }
            }
        }
    } while (Count == 0);
    Count = 0;
    SET_COLOR(6);
    cout << setw(35) << " " << "STT"<< "\t"<< "Ten Nuoc Uong"<< "\t\t\t     "<< " Size / Gia" << endl;
    cout << setw(35) << " " << "\t\t\t\t\t  S"<< "\t"<< "  M"<< "\t"<< "  L" << endl;
    SET_COLOR(7);
    cout << setfill('-');
    cout << "\t\t\t\t   " << setw(58) << "-" << endl;
    cout << setfill(' ');
    for (Node *i = l->head; i != NULL; i = i->next){
        if (price == i->data.price1 || price == i->data.price2 || price == i->data.price3){
            Count++;
            cout << setw(35) << " " << Count << "\t";
            cout << setw(25) << left  << i->data.name << "\t";
            if (i->data.price1 == 0){
                cout << ""
                     << "\t";
            }else{
                cout << left << i->data.price1 << "\t";
            }
            if (i->data.price2 == 0){
                cout << ""<< "\t";
            }else{
                cout << left << i->data.price2 << "\t";
            }
            if (i->data.price3 == 0)
            {
                cout << ""<< "\t";
            }else{
                cout << left << i->data.price3 << "\t";
            }

            cout << endl;
        }
    }
}

void Search(List* l){       //Tìm kiếm.
    SET_COLOR(6);
    cout << "------Tim  Kiem------" << endl;
    SET_COLOR(7);
    cout << "1. Tim kiem theo ten." << endl;
    cout << "2. Tim kiem theo gia." << endl;
    cout << "3. Thoat." << endl;
    cout << "Nhap lua chon cua ban: ";
    int choice;
    do{
        cin>>choice;
        switch(choice){
            case 1:
                system("cls");
                SearchName(l);
                SET_COLOR(6);
                cout << "------Tim  Kiem------" << endl;
                SET_COLOR(7);
                cout << "1. Tim kiem theo ten." << endl;
                cout << "2. Tim kiem theo gia." << endl;
                cout << "3. Thoat." << endl;
                cout << "Nhap lua chon cua ban: ";
                break;
            case 2:
                system("cls");
                SearchPrice(l);
                SET_COLOR(6);
                cout << "------Tim  Kiem------" << endl;
                SET_COLOR(7);
                cout << "1. Tim kiem theo ten." << endl;
                cout << "2. Tim kiem theo gia." << endl;
                cout << "3. Thoat." << endl;
                cout << "Nhap lua chon cua ban: ";
                break;
            case 3:
                system("cls");
                break;
            default:
            SET_COLOR(3);
            cout<<"Lua chon khong hop le. Vui long nhap lai: ";
            SET_COLOR(7);
            }
        }while(choice!=3);
}

void Sell(List *l){
    Outputlist(l);
    int Count = 0;
    for(Node* p = l->head; p != NULL; p = p->next){
        Count++;
    }
    string _n;
    int n;
    cout << "So loai san pham muon ban: ";
    cin >> _n;
    while (!CheckKiTu(_n)){
        cout << "So nhap vao khong hop le! Vui long nhap lai (0<so<" << Count << "): ";
        cin >> _n;
    }
    n = stoi(_n);
    while (n <= 0 || n > Count){
        cout << "So nhap vao khong hop le! Vui long nhap lai (0<so<" << Count << "): ";
        cin >> n;
    }
    string _STT;
    int STT;
    string ten;
    string _soluong;
    int soluong;
    for (int i = 0; i < n; i++){
        SET_COLOR(6);
        cout << "San pham thu " << i + 1 << endl;
        SET_COLOR(7);
        cout << "Nhap so thu tu san pham muon ban: ";
        cin >> _STT;
        while (!CheckKiTu(_STT)){
            cout << "So thu tu khong hop le! Vui long nhap lai: ";
            cin >> _STT;
        }
        STT = stoi(_STT);
        while (STT <= 0 || STT > Count){
            cout << "So thu tu khong hop le! Vui long nhap lai: ";
            cin >> STT;
        }
        Node* p = l->head;
        for (int i = 1; i < STT; i++){
            p = p->next;
        }
        ten = p->data.name;
        cout << "Ban da chon: " << ten << endl;
        cout << "So luong: ";
        cin >> _soluong;
        while (!CheckKiTu(_soluong)){
            cout << "So luong khong hop le. Vui long nhap lai: ";
            cin >> _soluong;
        }
        soluong = stoi(_soluong);
        while (soluong <= 0){
            cout << "So luong khong hop le. Vui long nhap lai: ";
            cin >> soluong;
        }
        char _size;
        int _price;
        cout << "Size S/M/L: ";
        cin >> _size;
        char Size = toupper(_size);
        while (Size != 'S' && Size != 'M' && Size != 'L'){
            cout << "Size khong hop le! Vui long nhap lai: ";
            cin >> Size;
        }
        if (Size == 'S'){
            _price = p->data.price1;
        }else if (Size == 'M'){
            _price = p->data.price2;
        }else if (Size == 'L'){
            _price = p->data.price3;
        }
        fstream fs;
        fs.open("sanphamdaban.txt", ios::out | ios::app);
        fstream fs2;
        fs2.open("hoadon.txt", ios::out | ios::app);
        if (!(fs.is_open() && fs2.is_open())){
            cout << "Khong the mo file!" << endl;
            return;
        }
        fs << ten << "," << soluong << "," << _price << endl;
        fs2 << ten << "," << soluong << "," << _price << endl;
        fs.close();
    }
}

void XuatBill(){
    fstream fs2;
    fs2.open("hoadon.txt", ios::in);
    if (!fs2.is_open()){
        cout << "Khong the mo file! ";
        return;
    }
    string line;
    string ten;
    int gia;
    int soluong;
    long tong = 0;
    cout << setw(70) << right << "-----DA KAFE N TEA-----" << endl<< endl;
    time_t now = time(0);
    tm *localTime = localtime(&now);
    cout << setw(32) << " "<< "Ngay: " << put_time(localTime, "%d/%m/%Y") << endl;
    cout << setw(32) << " "<< "Gio: " << put_time(localTime, "%H:%M:%S") << endl;
    cout << setw(32) << " " << setw(30) << left << "Ten san pham" << setw(15) << "So luong" << setw(7) << right << "Gia" << endl;
    cout << setfill('-');
    cout << "\t\t\t\t " << setw(53) << "-" << endl;
    cout << setfill(' ');
    while (getline(fs2, line)){
        stringstream ss(line);
        string s;
        getline(ss,ten, ',');
        getline(ss, s, ',');
        soluong = stoi(s);
        getline(ss, s, ',');
        gia = stoi(s);
        cout << setw(32) << " " << setw(30) << left << ten << "   " << setw(15) << soluong << setw(18) << gia * soluong << endl;
        tong += gia * soluong;
    }
    cout << setfill('-');
    cout << "\t\t\t\t" << setw(53) << "-" << endl;
    cout << setfill(' ');
    cout << "\t\t\t\tTong:" << setw(50) << right << tong << endl<< endl;
    cout << setw(74) << "Cam on quy khach. hen gap lai !" << endl;

    fs2.close();
//    fs2.open("hoadon.txt", ios::out | ios::trunc);
//    fs2.close();
}
struct temp {
    string ten;
    int soluong;
    long doanhthu;
    temp* next;
};
void DoanhThu(List* l) {
    fstream fs3;
    fs3.open("sanphamdaban.txt", ios::in);
    if (!fs3.is_open()) {
        cout << "Khong the mo file!" << endl;
        return;
    }
    temp* templist = NULL;

    string line;
    while (getline(fs3, line)) {
        stringstream ss(line);
        string ten;
        int soluong;
        long gia;
        getline(ss, ten, ',');
        getline(ss, line, ',');
        soluong = stoi(line);
        getline(ss, line, ',');
        gia = stoi(line);
        temp* prePro = NULL;
        bool found = false;
        for(temp* curPro = templist; curPro!=NULL; curPro=curPro->next){
            if (curPro->ten == ten) {
                curPro->soluong += soluong;
                curPro->doanhthu += gia * soluong;
                found = true;
                break;
            }
            prePro = curPro;
        }
        // Nếu không tìm thấy sản phẩm, thêm mới vào danh sách tạm thời
        if (!found) {
            temp* newTemp = new temp();
            newTemp->ten = ten;
            newTemp->soluong = soluong;
            newTemp->doanhthu = gia * soluong;
            newTemp->next = NULL;

            // Nếu danh sách tạm thời rỗng, thì gán sản phẩm mới vào đầu
            if (prePro == NULL) {
                templist = newTemp;
            } else {
                prePro->next = newTemp;
            }
        }
    }
    // Sắp xếp theo số lượng sản phẩm
    for (temp* i = templist; i != NULL; i = i->next) {
        for (temp* j = i->next; j != NULL; j = j->next) {
            if (i->soluong < j->soluong) {
                swap(i->soluong, j->soluong);
                swap(i->doanhthu, j->doanhthu);
            }
        }
    }
    SET_COLOR(6);
    cout << setw(30) << " " << "STT" << "\t" << "Ten Nuoc Uong" << "\t\t\t" << "So luong ban" << "\t" << "Doanh Thu" << endl;
    SET_COLOR(7);
    cout << setw(30) << " " << "-------------------------------------------------------------------" << endl;

    int Count = 0;
    unsigned long TongDoanhThu = 0;
    temp* curPro = templist;
    for(temp* curPro = templist; curPro!=NULL; curPro=curPro->next){
        Count++;
        cout << setw(30) << " " " " << Count << setw(9) << " ";
        cout << left << setw(35) << curPro->ten;
        cout << setw(10) << left << curPro->soluong << "\t";
        cout << curPro->doanhthu << "\t";
        cout << endl;

        TongDoanhThu += curPro->doanhthu;
    }
    time_t now = time(0);
    tm* localTime = localtime(&now);
    SET_COLOR(3);
    cout << endl;
    cout << setw(30) << " " << "Tong doanh thu cua ngay hom nay: " << setw(32) << right << TongDoanhThu << endl;
    cout << setw(30) << " " << "Duoc tinh vao ngay: " << put_time(localTime, "%d/%m/%Y") << ", luc " << put_time(localTime, "%H:%M:%S") << endl;
    SET_COLOR(7);
    fs3.close();
    //fs3.open("sanphamdaban.txt", ios::out | ios::trunc);
    //fs3.close();
}

 void Menu(List* l) {
    int choice;
    do{
        SET_COLOR(6);
        cout << setw(55) << " " << "-----MENU-----" << endl;
        SET_COLOR(7);
        cout << setw(50) << " " << "1. Xem danh sach san pham." << endl;
        cout << setw(50) << " " << "2. Them san pham." << endl;
        cout << setw(50) << " " << "3. Xoa san pham." << endl;
        cout << setw(50) << " " << "4. Cap nhat gia san pham." << endl;
        cout << setw(50) << " " << "5. Sap xep danh sach san pham." << endl;
        cout << setw(50) << " " << "6. Tim kiem san pham." << endl;
        cout << setw(50) << " " << "7. Tao hoa don." << endl;
        cout << setw(50) << " " << "8. Doanh thu." << endl;
        cout << setw(50) << " " << "9. Dang xuat." << endl;
        cout << setw(50) << " " << "10. Thoat chuong trinh." << endl << endl;
        SET_COLOR(3);
        cout << setw(50) << " " << "Nhap lua chon cua ban: ";
        SET_COLOR(7);
        cin >> choice;
        switch (choice) {
        case 1:
            system("cls");
            ReadFile(l);
            Outputlist(l);
            Quit();
            break;
        case 2:
            system("cls");
            ReadFile(l);
            Outputlist(l);
            AddProduct(l);
            Quit();
            break;
        case 3:
            system("cls");
            ReadFile(l);
            Outputlist(l);
            RemoveProduct(l);
            Quit();
            break;
        case 4:
            system("cls");
            ReadFile(l);
            Outputlist(l);
            UpdatePrice(l);
            Quit();
            break;
        case 5:
            system("cls");
            ReadFile(l);
            Outputlist(l);
            Sort(l);
            break;
        case 6:
            system("cls");
            ReadFile(l);
            Outputlist(l);
            Search(l);
            break;
        case 7:
            system("cls");
            ReadFile(l);
            cin.ignore();
            Sell(l);
            system("cls");
            XuatBill();
            Quit();
            break;
        case 8:
            system("cls");
            DoanhThu(l);
            Quit();
            break;
        case 9:
            cin.ignore();
            system("cls");
            login();
            system("cls"); // Đăng xuất và quay về phần đăng nhập
            break;
        case 10:
            system("cls");
            exit(0); // Thoát chương trình
            break;
        default:
            system("cls");
            SET_COLOR(3);
            cout <<setw(42) << " " << "Lua chon khong hop le. Vui long nhap lai!" << endl;
            SET_COLOR(7);
        }
    } while (choice != 10);
    cout << endl;
}

int main()
{
    login();
    List* l=new List();
    init(l);
    system("cls");
    Menu(l);
    return 0;
}
