/*
BTL MMT&IoT 2022.2
*/

#include<stdio.h>
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<stdlib.h>
#define X first
#define Y second

using namespace std;

const int oo = 1000111000;
typedef pair<int, int> ii;

int fl;
int choice; //Lựa chọn của người dùng
bool typo = 0; //Lựa chọn không hợp lệ
int direct = 0;
int n, m; //Đồ thị n đỉnh (nút), m cạnh
int start, dest; //Tìm đường đi từ start tới dest
int d[160102];
int pre[160102];
bool inqueue[160102];
vector<ii> a[160102];
vector<int> path; //Lưu lại đường đi 

void clrscr(){
    cout << "\033[2J\033[1;1H";
}

void welcome(){
    clrscr();
    printf("PHAN MEM MO PHONG THUAT TOAN TIM DUONG DI NGAN NHAT\n");
    printf("---------------------------------------------------\n\n");
        printf("MOI BAN CHON THUAT TOAN DE SU DUNG:\n");
        printf("  1. Dijkstra.\n");
        printf("  2. Bellman-Ford.\n");

        printf("\n");
        printf("  0. Thoat chuong trinh.\n");
        if (!typo) printf("Moi ban nhap: "); else printf("Lua chon ban nhap khong hop le, vui long nhap lai: ");
        scanf("%d", &choice);
    if (choice != 0 && choice != 1 && choice != 2){
        typo = 1;
        welcome();
    }
    typo = 0;
}

void oup(){
    if (fl) freopen("output.out", "w", stdout);
    if (d[dest] == oo){
        printf("Khong tim duoc duong.");
    } else {
        printf("Do dai quang duong ngan nhat: %d\n", d[dest]);
        for(int i = dest; i != start;  i = pre[i]) path.push_back(i);
        path.push_back(start);
        reverse(path.begin(), path.end());
        printf("Lộ trình: ");
        for(int i = 0; i < path.size(); i++){
            if(i == path.size() - 1){
                printf("%d", dest);
                break;
            }
            printf("%d -> ",path[i]);
        }
        printf("\n");
    }
    path.clear();
    a->clear();
    if (fl) fclose(stdout);
}

void dijkstra(int start) {
    priority_queue<ii, vector<ii>, greater<ii> > pq;
    for (int i = 1; i <= n; i++)
        d[i] = oo;
    d[start] = 0;
    pq.push(ii(0, start));
    inqueue[start] = true;
    while (pq.size()) {
        int u = pq.top().Y;
        int du = pq.top().X;
        inqueue[pq.top().Y] = false;
        pq.pop();
        if (du != d[u])
            continue;
        for (int i = 0; i < a[u].size(); i++) {
            int v = a[u][i].Y;
            int uv = a[u][i].X;
            if (d[v] > du + uv) {
                d[v] = du + uv;
                pre[v] = u;
                if (!inqueue[v]){
                    pq.push(ii(d[v], v));
                    inqueue[v] = true;
                }
            }
        }
    }
}

void bellman(int u) {
    queue<int> qu;
    for (int i = 1; i <= n; i++) d[i] = oo;
    d[u] = 0;
    qu.push(u); //push u vào queue
    inqueue[u] = true; //Đánh dấu đỉnh u đã trong queue
    while (qu.size()) {
        u = qu.front(); //Lấy giá trị đầu của queue
        inqueue[u] = false; //Đánh dấu là đỉnh u đã pop ra khỏi queue (hay không còn trong queue)
        qu.pop(); // pop đỉnh u ra khỏi queue
        for (int i = 0; i < a[u].size(); i++) { // Duyệt các đỉnh kề u
            int v = a[u][i].Y;
            int uv = a[u][i].X;
            if (d[v] > d[u] + uv) {
                d[v] = d[u] + uv;
                pre[v] = u;
                if (!inqueue[v]) { // Nếu đỉnh v chưa trong queue
                    qu.push(v); // Cho v vào queue
                    inqueue[v] = true; // Đánh dấu là đỉnh v đã trong queue
                }
            }
        }
    }
}

void inp(){
    clrscr();
    printf("Thuat toan ban da lua chon: ");
    if (choice == 1) printf("Dijkstra.\n"); else if (choice == 2) printf("Bellman-Ford.\n");

    printf("Ban muon nhap vao do thi co huong hay vo huong? (1:co huong/0:vo huong): ");
    scanf("%d", &direct);

    printf("\nBan muon nhap vao do thi tu file (input.inp) hay ban phim?");
    printf("\nMoi ban nhap (1:file/0:ban phim): ");
    scanf("%d", &fl);
    //printf("%d", fl);
    //cin.tie();
    //cin.clear();
    if (fl) freopen("input.inp", "r", stdin);
    //if (fl) freopen("output.out", "w", stdout);
    //printf("Hello");
    printf("Ban hay nhap 4 so tiep theo theo dinh dang: [so nut]_[so canh]_[dinh bat dau]_[dinh ket thuc]\n");
    scanf("%d %d %d %d", &n, &m, &start, &dest);
    while (m) {
        int p, q, w;
        printf("\nBan hay nhap %d canh con lai theo dinh dang: [dinh dau]_[dinh cuoi]_[quang duong(trong so)]\n", m--);
        scanf("%d %d %d", &p, &q, &w);
        if (choice == 1 && w < 0 && !fl){
            printf("Dijkstra khong the xu ly canh co trong so am!\n");
            typo = 1;
            return;
        }
        a[p].push_back(ii(w, q));
        if (!direct) a[q].push_back(ii(w, p));
    }
    if (fl) fclose(stdin);
    if (fl){
        printf("\nDoc du lieu tu file input.inp thanh cong! Ban hay kiem tra ket qua trong file output.out\n");
    }
    //if (fl) fclose(stdout);
    if (choice == 1){
        dijkstra(start);
    } else {
        bellman(start);
    }
}

int main(){
    //ios::sync_with_stdio(false);
    do{
        clrscr();
        welcome();
        if (choice == 0) return 0; 
        inp();
        if (!typo) oup();
        typo = 0;
        char chk;
        printf("\nBan co muon mo phong do thi khac khong? (Y/N)\n");
        printf("Moi ban nhap: ");
        cin >> chk;
        if (chk == 'Y' || chk == 'y' || chk == '1'){
            continue;
        } else if (chk == 'N' || chk == 'n' || chk == '0'){
            return 0;
        }
    } while (choice);
    return 0;
}