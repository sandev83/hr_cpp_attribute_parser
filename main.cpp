#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <iterator>

using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    map<string, string> tag_list;
    string currentTag = "";
    for (int i = 0; i <= n; i++) {
        string buf;
        getline(cin, buf);
        if (!buf.empty()) {
            if (buf.find("</" + currentTag.substr(currentTag.find_last_of('.')+1) + ">") != string::npos) currentTag = currentTag.substr(0, currentTag.find_last_of('.'));
            else {
                currentTag += "." + buf.substr(buf.find('<')+1, (buf.find(' ')!=string::npos?buf.find(' ')-1:buf.find('>')-1));
                tag_list.insert(pair<string, string>(currentTag.substr(1), buf));
                if (buf.find("/>") != string::npos) currentTag = currentTag.substr(0, currentTag.find_last_of('.'));
            }
        }
    }
    for (int i = 0; i <= q; i++) {
        string que;
        getline(cin, que);
        size_t pos = que.find('~');
        string attr_name = "";
        string tags = "";
        if (pos != string::npos) {
            attr_name = " " + que.substr(pos+1);
            tags = que.substr(0, pos);
        }
        auto it = tag_list.find(tags);
        if (it != tag_list.end()) {
            string val = it->second;
            if (val.find(attr_name) != string::npos) {
                val = val.substr(val.find(attr_name) + attr_name.length());
                val = val.substr(val.find('"')+1);
                val = val.substr(0, val.find('"'));
            } else val = "Not Found!";
            cout << val << endl;
        } else cout << "Not Found!" << endl;
    }

    return 0;
}

/*
 * Test case:
 * 10 10
<a value = "GoodVal">
<b value = "BadVal" size = "10">
</b>
<c height = "auto">
<d size = "3">
<e strength = "2">
</e>
</d>
</c>
</a>
a~value
b~value
a.b~size
a.b~value
a.b.c~height
a.c~height
a.d.e~strength
a.c.d.e~strength
d~sze
a.c.d~size

Expected output:
GoodVal
Not Found!
10
BadVal
Not Found!
auto
Not Found!
2
Not Found!
3
*/
