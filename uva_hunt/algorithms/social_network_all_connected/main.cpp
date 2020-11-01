#include <iostream>
#include "../../data_structures/union_find/union_find.h"

using namespace std;

int main()
{
    int members, timestamps;
    int member_a, member_b, timestamp;
    cin >> members >> timestamps;

    UnionFind friend_network(members);

    for (int ts = 1; ts <= timestamps; ts++)
    {
        cin >> timestamp >> member_a >> member_b;
        friend_network.set_union(member_a, member_b);

        // It's impossible to get all members connected if we have made least than m-1 friendships
        if (members - 1 <= ts && friend_network.all_connected())
        {
            cout << "all were friend at " << timestamp << endl;
            return 0;
        }
    }
    return 0;
}
