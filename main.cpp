#include <bits/stdc++.h>
#include <ncurses.h>
#include <unistd.h>
using namespace std;
random_device rd;
mt19937 rng(rd());
int row, col;
bool vis[1000][1000];
void printcenter(string s, int i, int all) {
    mvprintw((row - all) / 2 + i, (col - s.size()) / 2, "%s", s.c_str());
}
bool food[1000][1000];
void makefood() {
    int i, j;
    do {
        i = rng() % (row - 2) + 1;
        j = rng() % (col - 2) + 1;
    } while (vis[i][j]);
    food[i][j] = true;
    mvprintw(i, j, "*");
}
signed main() {
    initscr();
    cbreak();
    noecho();
    clear();
    keypad(stdscr, true);
    getmaxyx(stdscr, row, col);
    box(stdscr, '|', '-');
    printcenter("Snaking!", 1, row + 2);
    queue<pair<int, int>> q;
    q.push(make_pair(1, 1));
    vis[1][1] = true;
    q.push(make_pair(2, 1));
    vis[2][1] = true;
    q.push(make_pair(3, 1));
    vis[3][1] = true;
    makefood();
    cbreak();
    timeout(0);
    int d = 1;int cnt = 0;
    while (1) {
        int c = getch();
        if (c == KEY_UP && d != 1)
            d = 0;
        if (c == KEY_DOWN && d != 0)
            d = 1;
        if (c == KEY_LEFT && d != 3)
            d = 2;
        if (c == KEY_RIGHT && d != 2)
            d = 3;
        auto [x, y] = q.back();
        if (d == 0) {
            x--;
            if (x == 0) x = row - 2;
        }
        if (d == 1) {
            x++;
            if (x == row - 1) x = 1;
        }
        if (d == 2) {
            y--;
            if (y == 0) y = col - 2;
        }
        if (d == 3) {
            y++;
            if (y == col - 1) y = 1;
        }
        if (vis[x][y]) {
            clear();
            printcenter("You lose!", 1, 1);
            refresh();
            timeout(100000000000);
            getch();
            endwin();
            return 0;
        }
        q.push(make_pair(x, y));
        vis[x][y] = true;
        mvprintw(x, y, "O");
        if (!food[x][y]) {
            mvprintw(q.front().first, q.front().second, " ");
            vis[q.front().first][q.front().second] = false;
            q.pop();
        } else {
            food[x][y] = 0;
            makefood();
        }
        cnt++;
        mvprintw(row - 1, col - to_string(q.size()).size() - 7, "score: %d", q.size());
        usleep(100000);
        refresh();
    }
    endwin();
    return 0;
}
