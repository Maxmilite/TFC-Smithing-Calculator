#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

#define lint long long
#define rep(_, __, ___) for (int _ = __; _ <= ___; ++_)

/* 如果要启用取最小值模式，取消下一句的注释即可 */
// #define COUNTMIN

const int operation[8] = {-3, -6, -9, -15, 2, 7, 13, 16};
const string optName[8] = {
    "轻击", "击打", "重击", "牵拉",
    "冲压", "弯曲", "镦锻", "收缩"
};
const string String[] = {
    "================ 群峦传说锻造最优解计算器 ================",
    "启用了文件读写模式，正在读取文件 ",
    "结果已保存至 ",
    "启用了控制台读写模式.",
    "请输入测试数据组数: ",
    "请输入目标数值: ",
    "请按照砧界面上所提示的需求步骤从左到右输入对应的 3 个数值: ",
    "提示: "
};
const int maxn = 128;

vector<string> res, cur;
int bestTimes = 114514;
map<int, int> vis;
const string rightArrow = " → ";
 
std::string Utf8ToGbk(std::string src_str) {
	int len = MultiByteToWideChar(CP_UTF8, 0, src_str.c_str(), -1, NULL, 0);
	wchar_t* wszGBK = new wchar_t[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, src_str.c_str(), -1, wszGBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char* szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
	string strTemp(szGBK);
	if (wszGBK) delete[] wszGBK;
	if (szGBK) delete[] szGBK;
	return strTemp;
}
// ————————————————
// 版权声明：本文为CSDN博主「q302989778」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
// 原文链接：https://blog.csdn.net/q302989778/article/details/87792686

void dfs(int x, int now, int times) {
    if (vis[now] <= times)
        return;
    vis[now] = times;
    if (now < 0 || now >= maxn)
        return;
    if (times > bestTimes)
        return;
    if (now == x && times < bestTimes) {
        bestTimes = times;
        res = cur;
        return;
    }
    for (int i = 7; i >= 0; --i) {
        cur.push_back(optName[i]);
        dfs(x, now + operation[i], times + 1);
        cur.pop_back();
    }
}

struct AnsInfo {
    vector<string> res;
    vector<int> requirement;
    int bestTimes;
    AnsInfo() {
        this->bestTimes = 114514;
    }
    AnsInfo(vector<string> res, int bestTimes, vector<int> requirement) {
        this->res = res;
        this->bestTimes = bestTimes;
        this->requirement = requirement;
    }
};

namespace finder {
    string find(int x) {
        rep(i, 0, 7)
            if (operation[i] == x)
                return optName[i];
    }
    int find(string x) {
        rep(i, 0, 7)
            if (optName[i] == x)
                return operation[i];
    }
}

int main(int argc, char* argv[]) {
    
    if (argc != 3 && argc != 1) {
        printf("Usage: Main.exe <Input File> <Output File> / Main.exe\n");
        return 0;
    }

    cout << Utf8ToGbk(String[0]) << endl;

    FILE* fileIn;
    FILE* fileOut;
    if (argc == 1) {
        fileIn = stdin;
        fileOut = stdout;
    } else {
        cout << Utf8ToGbk(String[1]);
        fileIn = fopen(argv[1], "r+");
        fileOut = fopen(argv[2], "w+");
        cout << argv[1] << " ..." << endl;
        if (fileIn == nullptr) {
            cout << Utf8ToGbk("文件打开失败，请检查文件路径是否正确.") << endl;
            system("pause");
            return 0;
        }
    }

    int n, t;
    if (argc == 1)
        cout << Utf8ToGbk(String[3] + '\n' + String[4]);
    cout.flush();
    fscanf(fileIn, "%d", &t);
    vector<AnsInfo> ans;
    ofstream fout;
    if (argc == 3)
        fout.open(argv[2], ios::out | ios::trunc);
    int cas = 0;
    while (t--) {
        bestTimes = 114514;
        cur.clear();
        res.clear();
        vector<int> requirement;
        requirement.clear();
        if (argc == 1)
            cout << Utf8ToGbk(String[5]);
        fscanf(fileIn, "%d", &n);
        if (argc == 1) {
            cout << Utf8ToGbk(String[6]) << endl << Utf8ToGbk(String[7]) << endl;
            rep(i, 0, 1)
                cout << Utf8ToGbk(optName[i] + rightArrow) << operation[i] << ' ';
            cout << ' ';
            rep(i, 4, 5)
                cout << Utf8ToGbk(optName[i] + rightArrow) << operation[i] << "  ";
            cout << endl;
            rep(i, 2, 3)
                cout << Utf8ToGbk(optName[i] + rightArrow) << operation[i] << ' ';
            rep(i, 6, 6)
                cout << Utf8ToGbk(optName[i] + rightArrow) << operation[i] << " ";
            rep(i, 7, 7)
                cout << Utf8ToGbk(optName[i] + rightArrow) << operation[i] << "  ";
            cout << endl;
        }
        rep(i, 1, 3) {
            int var1;
            fscanf(fileIn, "%d", &var1);
            requirement.push_back(var1);
        }

        int x = n;
        for (auto i : requirement)
            x -= i;
        for (int i = -maxn; i <= maxn; ++i)
            vis[i] = 114514;

        dfs(x, 0, 0);

        ans.push_back(AnsInfo(res, bestTimes, requirement));

        #ifndef COUNTMIN
        
        if (argc == 1) {
            cout << Utf8ToGbk("第 ").c_str() << ++cas << Utf8ToGbk(" 组数据: ").c_str() << endl;
            if (bestTimes != 114514) {
                cout << Utf8ToGbk("最优解步数: ").c_str() << bestTimes + 3 << endl;
                for (string i : res)
                // printf("%s → ", i.c_str());
                    cout << Utf8ToGbk(i) << Utf8ToGbk(rightArrow);
                // cout << Utf8ToGbk("最后三步") << endl;
                for (int j = 2; j >= 0; --j) {
                    cout << Utf8ToGbk(finder::find(requirement[j]));
                    if (j)
                        cout << Utf8ToGbk(rightArrow);
                }
                cout << endl << endl;
            } else {
                cout << Utf8ToGbk("输入数据不存在解法.").c_str() << endl << endl;
            }
        } else {
            if (bestTimes != 114514) {
                fout << Utf8ToGbk("第 ").c_str() << ++cas << Utf8ToGbk(" 组数据: ").c_str() << endl;
                fout << Utf8ToGbk("最优解步数: ").c_str() << bestTimes + 3 << endl;
                for (string i : res)
                // printf("%s → ", i.c_str());
                    fout << Utf8ToGbk(i) << Utf8ToGbk(rightArrow);
                // fout << Utf8ToGbk("最后三步") << endl;
                for (int j = 2; j >= 0; --j) {
                    fout << Utf8ToGbk(finder::find(requirement[j]));
                    if (j)
                        fout << Utf8ToGbk(rightArrow);
                }
                fout << endl << endl;
            } else {
                fout << Utf8ToGbk("输入数据不存在解法.").c_str() << endl << endl;
            }
        }
        #endif
    }

    #ifdef COUNTMIN
    sort(ans.begin(), ans.end(), [](AnsInfo x, AnsInfo y) {
        return x.bestTimes < y.bestTimes;
    });
    bestTimes = ans[0].bestTimes;
    res = ans[0].res;
    vector<int> requirement = ans[0].requirement;
    if (argc == 1) {
        if (bestTimes != 114514) {
            cout << Utf8ToGbk("最优解步数: ").c_str() << bestTimes + 3 << endl;
            for (string i : res)
            // printf("%s → ", i.c_str());
                cout << Utf8ToGbk(i) << Utf8ToGbk(rightArrow);
            for (int j = 2; j >= 0; --j) {
                cout << Utf8ToGbk(finder::find(requirement[j]));
                if (j)
                    cout << Utf8ToGbk(rightArrow);
            }
            cout << endl;
        } else {
            cout << Utf8ToGbk("输入数据不存在解法.").c_str() << endl << endl;
        }
        
    } else {
        if (bestTimes != 114514) {
            fout << Utf8ToGbk("最优解步数: ").c_str() << bestTimes + 3 << endl;
            for (string i : res)
            // printf("%s → ", i.c_str());
                fout << Utf8ToGbk(i) << Utf8ToGbk(rightArrow);
            for (int j = 2; j >= 0; --j) {
                fout << Utf8ToGbk(finder::find(requirement[j]));
                if (j)
                    fout << Utf8ToGbk(rightArrow);
            }
            fout << endl;
        } else {
            fout << Utf8ToGbk("输入数据不存在解法.").c_str() << endl << endl;
        }
    }
    #endif

    if (argc == 3)
        cout << Utf8ToGbk(String[2]) << argv[2] << "." << endl;

    cout << Utf8ToGbk("程序已退出.") << endl;
    system("pause");

    return 0;
}
