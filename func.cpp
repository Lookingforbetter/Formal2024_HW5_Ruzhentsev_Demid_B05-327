#include <iostream>
#include <vector>

const int cBig = 1e9;

struct Node {
    char type;
    int l = -1;
    int r = -1;
};

bool count_t(std::string& s,  std::vector<Node>& t) {
    int n = static_cast<int>(s.size());

    std::vector<int> stack;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'a' || s[i] == 'b' || s[i] == 'c' || s[i] == '1') {
            Node node{s[i]};
            t.push_back(node);
            stack.push_back(static_cast<int>(t.size()) - 1);
        } else if (s[i] == '*') {
            if (static_cast<int>(stack.size()) == 0) {
                return false;
            }

            Node node{s[i], stack[static_cast<int>(stack.size()) - 1]};
            t.push_back(node);
            stack.pop_back();
            stack.push_back(static_cast<int>(t.size()) - 1);
        } else if (s[i] == '+') {
            if (static_cast<int>(stack.size()) < 2) {
                return false;
            }

            Node node{s[i], stack[static_cast<int>(stack.size()) - 2],
                      stack[static_cast<int>(stack.size()) - 1]};

            t.push_back(node);
            stack.pop_back();
            stack.pop_back();
            stack.push_back(static_cast<int>(t.size()) - 1);
        } else if (s[i] == '.') {
            if (static_cast<int>(stack.size()) < 2) {
                return false;
            }

            Node node{s[i], stack[static_cast<int>(stack.size()) - 2],
                      stack[static_cast<int>(stack.size()) - 1]};

            t.push_back(node);
            stack.pop_back();
            stack.pop_back();
            stack.push_back(static_cast<int>(t.size()) - 1);
        }
    }

    if (stack.size() != 1) {
        return false;
    }

    return true;
}

std::pair<int, int> f(int idx, std::vector<Node>& t, char x) {
    if (t[idx].type == '1') {
        return {-1, 0};
    } else if (t[idx].type >= 'a' && t[idx].type <= 'c') {
        if (t[idx].type == x) {
            return {-1, 1};
        } else {
            return {0, -1};
        }
    } else if (t[idx].type == '*') {
        std::pair<int, int> p = f(t[idx].l, t, x);

        if (p.second > 0) {
            return {p.first, cBig};
        }

        return {p.first, p.second};
    } else if (t[idx].type == '+') {
        std::pair<int, int> p1 = f(t[idx].l, t, x);
        std::pair<int, int> p2 = f(t[idx].r, t, x);

        std::pair<int, int> res;
        res.first = std::max(p1.first, p2.first);
        res.second = std::max(p1.second, p2.second);

        return res;
    } else if (t[idx].type == '.') {
        std::pair<int, int> p1 = f(t[idx].l, t, x);
        std::pair<int, int> p2 = f(t[idx].r, t, x);

        std::pair<int, int> res;

        if (p1.second != -1 && p2.second != -1) {
            if (p1.second == cBig || p2.second == cBig) {
                res.second = cBig;
            } else {
                res.second = p1.second + p2.second;
            }
        } else {
            res.second = -1;
        }

        if (p1.first == -1) {
            res.first = p2.first;
        } else {
            if (p2.second != -1) {
                res.first = std::max(p2.first, p1.first + p2.second);
            } else {
                res.first = p2.first;
            }
        }

        return res;
    }
}

void print_answer(std::string& s, char x) {
    std::vector<Node> t;
    bool flag = count_t(s, t);

    if (!flag) {
        std::cout << "Incorrect input!";
        return;
    }

    int root = static_cast<int>(t.size()) - 1;

    std::pair<int, int> p = f(root, t, x);

    int ans = std::max(p.first, p.second);

    if (ans == cBig) {
        std::cout << "INF";
    } else {
        std::cout << ans;
    }
}
